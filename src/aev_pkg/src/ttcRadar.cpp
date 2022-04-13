#include "ttcRadar_Cfg.h"

#define DataPort_EN

ttcRAdarObj ttcRadarObj;
ros::Publisher ttcRadar_pub;
aev_pkg::radar_msg ttcRadar_output_msg;

void timer_uart_Callback(const ros::TimerEvent& )
{
    static uint32_t msg_counter = 0;
    std_msgs::UInt8MultiArray raw_data;
    uint16_t dataLen = ttcRadarObj.ser_Data_Port.available();
    ttcRadarObj.ser_Data_Port.read(raw_data.data, dataLen);

    ROS_INFO("Read: %u byte -----------------------------,", dataLen);
    if (!dataLen) return;

    // Processing the raw_data
    if (!ttcRadarObj.data_handler(raw_data, dataLen)) return;
    switch (modeRadar) {
        case ENABLE_RADAR_TTC: {
            msg_counter++;
            ttcRadarObj.clear_msg(ttcRadar_output_msg);
            if (!ttcRadarObj.Output.numObj) ttcRadar_output_msg.isObject = false;
            for (auto i = 0; i < ttcRadarObj.Output.numObj; i++) {
                ttcRadar_output_msg.numObj = ttcRadarObj.Output.numObj;
                ttcRadar_output_msg.IdObj.push_back(ttcRadarObj.Output.IdObj[i]);
                ttcRadar_output_msg.isApproach.push_back(ttcRadarObj.Output.isApproach[i]);
                ttcRadar_output_msg.alpha.push_back(ttcRadarObj.Output.alpha[i]);
                ttcRadar_output_msg.posX.push_back(ttcRadarObj.ptTargets.posX[i]);
                ttcRadar_output_msg.posY.push_back(ttcRadarObj.ptTargets.posY[i]);
                ttcRadar_output_msg.dis.push_back(ttcRadarObj.Output.dis[i]);
                ttcRadar_output_msg.vel.push_back(ttcRadarObj.Output.vel[i]);
                ttcRadar_output_msg.ttc.push_back(ttcRadarObj.Output.ttc[i]);

                ttcRadar_output_msg.msg_counter = msg_counter;
                ttcRadar_output_msg.isObject = ttcRadarObj.Output.isObject;

                sort(ttcRadarObj.Output.dis.begin(), ttcRadarObj.Output.dis.end());
                ttcRadar_output_msg.distance = ttcRadarObj.Output.dis[0];
            }
            ttcRadar_pub.publish(ttcRadar_output_msg);
            ROS_INFO("isObject: %d ", ttcRadar_output_msg.isObject);
            ROS_INFO("Public message ok (TTC) \r\n");
        }
        break;

        case ENABLE_RADAR_MPC: {
            msg_counter++;
            ttcRadarObj.clear_msg(ttcRadar_output_msg);
            ttcRadar_output_msg.msg_counter = msg_counter;
            ttcRadar_output_msg.isObject = ttcRadarObj.Output.isObject;
            ttcRadar_output_msg.distance = ttcRadarObj.Output.dis[0];
            ttcRadar_pub.publish(ttcRadar_output_msg);
            ROS_INFO("Public message ok (MPC) \r\n");
        }
        break;

        default:
        break;
    }
}

int main (int argc, char** argv)
{
    ros::init(argc, argv, "ttcRadar");
    ros::NodeHandle n;
    ttcRadar_pub = n.advertise<aev_pkg::radar_msg>("Radar_Data", 1000);
    
    // Timer to receive data from Radar
    ros::Timer timer_uart = n.createTimer(ros::Duration(0.05), timer_uart_Callback);

    // Connect to COM port of Radar 
    if (!ttcRadarObj.init_cfg_port()) return -1;
    
    #ifdef DataPort_EN
    if (!ttcRadarObj.init_data_port()) return -1;
    // {
    // }
    #endif
    
    ttcRadarObj.start_radar();

    // While loop do nothing, data received by interrupt
    while(ros::ok()) {
        ros::spinOnce();
    }   
}
