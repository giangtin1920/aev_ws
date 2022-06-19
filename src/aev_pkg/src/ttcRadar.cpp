#include "ttcRadar_Cfg.h"

#define DataPort_EN

ttcRAdarObj ttcRadarObj;
ros::Publisher ttcRadar_pub;
aev_pkg::radar_msg ttcRadar_output_msg;

void readRadarData(uint16_t &dataLen, std_msgs::UInt8MultiArray &raw_data)
{
  usleep(5000);
  while(ttcRadarObj.ser_Data_Port.available()) {
    uint16_t tmp = ttcRadarObj.ser_Data_Port.available();
    dataLen +=  tmp;
    ttcRadarObj.ser_Data_Port.read(raw_data.data, tmp);
    usleep(5000);
  }
}

void autoDrive()
{
  vector<string> state_description;
  vector<string> state_key;
  vector<float> speed_tmp;
  string key = " ";
  static float speed = 2.0;
  static float steering = 0.0;
  float ratioSpeed = 0.0;

  // param TTCController
  float speed_max = 15;
  float speed_min = 1;
  float speed_Nor = 2.0;
  float speed_turn = 5.0;
  float steering_turn = 0.05;
//  float ratioSlowdown = 20; // ~15 cnt giam 1 lan - khoang cach cang gan cang nho #5 #6
  float ratioSpeedup = 1.2;
  float X_max = 1.2;
  float X_min = -1.2;
  float ttc_min = 3; // s
  float dis_min = 60; // m

//  float duty = 0;
  static float x = 1;
  static float th = 1;
  static uint32_t cnt = 0, cnt1 = 0, cnt2 = 0, cnt3 = 0, numframeFilter = 60;

  cnt++;

  // stop in 4s numframeFilter = 800
  if (speed < speed_min) {
    cnt1++;
    if (cnt1 == numframeFilter+20) {
      cnt1 = 0;
      speed_tmp.push_back(speed_Nor);
      x = ratioSpeedup; th = 0;
    }
    else {state_description.push_back("stop"); state_key.push_back("k"); x = 0; th = 0;}
  }

  // tracking and warning dangerous objects.
  if (!ttcRadar_output_msg.numObj) {
    cnt3++;
    ROS_INFO("%u", cnt3);
    if (cnt3 == numframeFilter) {
      cnt3 = 0;
      state_description.push_back("no obstacle");
      state_key.push_back("i");
      steering = 0;
      x = ratioSpeedup; th = 0;
    }
    else {state_description.push_back("no obstacle"); state_key.push_back("i");}
  }
  else {

    // get state_description and state_key for controller
    for (uint8_t i = 0; i < ttcRadar_output_msg.numObj; i++) {

      if (ttcRadar_output_msg.safetyZone[i] == "carAccidence" || ttcRadar_output_msg.safetyZone[i] == "carWarning") {

        // 6m
//        ratioSpeed = (-0.814 + 0.179*ttcRadar_output_msg.dis[i] + -0.00662*pow(ttcRadar_output_msg.dis[i], 2)
//                      + 0.000107*pow(ttcRadar_output_msg.dis[i],3) + -0.000000624*pow(ttcRadar_output_msg.dis[i],4));

        // 10m
//        ratioSpeed = (-1.98 + 0.281*ttcRadar_output_msg.dis[i] + -9.68E-03*pow(ttcRadar_output_msg.dis[i], 2)
//                      + 1.44E-04*pow(ttcRadar_output_msg.dis[i],3) + -7.82E-07*pow(ttcRadar_output_msg.dis[i],4));

        // 20m
        ratioSpeed = (-0.498 + 0.0367*ttcRadar_output_msg.dis[i] + 4.25E-03*pow(ttcRadar_output_msg.dis[i],2) + -4.75E-04*pow(ttcRadar_output_msg.dis[i],3) + 1.79E-05*pow(ttcRadar_output_msg.dis[i],4) + -2.85E-07*pow(ttcRadar_output_msg.dis[i],5) + 1.62E-09*pow(ttcRadar_output_msg.dis[i],6));

        if (ratioSpeed > 1) ratioSpeed = 1;
        if (ratioSpeed < 0) ratioSpeed = 0;

        if (ttcRadar_output_msg.posX[i] > X_min && ttcRadar_output_msg.posX[i] < X_max) {
          state_description.push_back("front");
          if (ttcRadar_output_msg.dis[i] < dis_min) {
            speed_tmp.push_back(speed_max*ratioSpeed);
            state_key.push_back("x");
          }
          else state_key.push_back("i");
        }
        else if (ttcRadar_output_msg.posX[i] >= X_max) {
          state_description.push_back("right");
          if (ttcRadar_output_msg.ttc[i] < ttc_min) {
            state_key.push_back("u");
            speed_tmp.push_back(speed_turn);
            steering = steering_turn;
          }
          else state_key.push_back("i");
        }
        else if (ttcRadar_output_msg.posX[i] <= X_min) {
          state_description.push_back("left");
          if (ttcRadar_output_msg.ttc[i] < ttc_min) {
            state_key.push_back("o");
            speed_tmp.push_back(speed_turn);
            steering = steering_turn;
          }
          else state_key.push_back("i");
        }
        else state_description.push_back("unknown state_description");
      }
      else {
        // filter for lost frame
        cnt2++;
        if (cnt2 == 20) {
          cnt2 = 0;
          state_description.push_back("no obstacle");
          state_key.push_back("i");
          steering = 0;
          x = ratioSpeedup; th = 0;
        }
        else {state_description.push_back("previous state"); state_key.push_back("none");}
      }
    }
  }

  // assign control command character (key), x is moveBindings


  sort(speed_tmp.begin(), speed_tmp.end());
  sort(state_key.begin(), state_key.end());
  for (int i = 0; i < state_key.size(); ) {
      if (state_key[i] == state_key[i+1]) {
          state_key.erase(state_key.begin() + i);
      }
      else i++;
  }

  static vector<string> key_i{"i"};
  static vector<string> key_k{"k"};
  static vector<string> key_o{"o"};
  static vector<string> key_u{"u"};
  static vector<string> key_x{"x"};
  static vector<string> key_io{"i", "o"};
  static vector<string> key_iu{"i", "u"};
  static vector<string> key_ix{"i", "x"};
  static vector<string> key_ou{"o", "u"};
  static vector<string> key_ox{"o", "x"};
  static vector<string> key_ux{"u", "x"};
  static vector<string> key_none{"none"};

  if (state_key == key_i) {/*x = 1; th = 0;*/ key = "i";}
  else if (state_key == key_k) {x = 0; th = 0; key = "k";}
  else if (state_key == key_o) {x = 1; th = 1; key = "o";}
  else if (state_key == key_u) {x = 1; th = -1; key = "u";}
  else if (state_key == key_x) {x = 0.8; th = 0; key = "x";}
  else if (state_key == key_io) {x = 1; th = 1; key = "io";}
  else if (state_key == key_iu) {x = 1; th = -1; key = "iu";}
  else if (state_key == key_ix) {x = 0.8; th = 0; key = "ix";}
  else if (state_key == key_ou) {x = 1; th = 0; key = "ou";}
  else if (state_key == key_ox) {x = 1; th = 1; key = "ox";}
  else if (state_key == key_ux) {x = 1; th = -1; key = "ux";}
  else if (state_key == key_none) {key = "none";}

  if (speed_tmp.size()) {
    speed = speed_tmp[0];
  }
  speed = x * speed;
  steering = th * steering;

  if (abs(speed) > speed_max) speed = speed_max;

  ttcRadar_output_msg.ttcSpeed = speed;
  ttcRadar_output_msg.ttcSteering = steering;
  ttcRadar_output_msg.ttcKey = key;

}

void timer_uart_Callback(const ros::TimerEvent&)
{
//     usleep(90000);  // timeout to receive all byte from Radar // baudrate 921600bps ~ 115200byte/s ~ 8.68us/byte ~ actual 10.851us/byte
    static uint32_t msg_counter = 0;
    std_msgs::UInt8MultiArray raw_data;
//    uint16_t dataLen = ttcRadarObj.ser_Data_Port.available();
//    ttcRadarObj.ser_Data_Port.read(raw_data.data, dataLen);
//    ROS_INFO("Read: %u byte -----------------------------,", dataLen);

    uint16_t dataLen = 0;

    readRadarData(dataLen, raw_data);

    if (!dataLen) return;
    ROS_INFO("Read: %u byte -----------------------------,", dataLen);

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
                ttcRadar_output_msg.safetyZone.push_back(ttcRadarObj.Output.safetyZone[i]);

                ttcRadar_output_msg.msg_counter = msg_counter;
                ttcRadar_output_msg.isObject = ttcRadarObj.Output.isObject;

                sort(ttcRadarObj.Output.dis.begin(), ttcRadarObj.Output.dis.end());
                ttcRadar_output_msg.distance = ttcRadarObj.Output.dis[0];
            }
            ttcRadar_output_msg.ptX = ttcRadarObj.ptDetObj.x;
            ttcRadar_output_msg.ptY = ttcRadarObj.ptDetObj.y;
            ttcRadar_output_msg.ptZ = ttcRadarObj.ptDetObj.z;
            autoDrive();


//            for (int i = 0; i < ttcRadarObj.ptStaticDetObj.x.size(); i++) {
//                ttcRadar_output_msg.staticPosX.push_back(ttcRadarObj.ptStaticDetObj.x[i]);
//                ttcRadar_output_msg.staticPosY.push_back(ttcRadarObj.ptStaticDetObj.y[i]);
//            }

            ttcRadar_pub.publish(ttcRadar_output_msg);
            ROS_INFO("isObject:             %d ", ttcRadar_output_msg.isObject);
            ROS_INFO("ttcSpeed:     m/s,    %f", ttcRadar_output_msg.ttcSpeed);
            ROS_INFO("ttcSteering:  m/s,    %f", ttcRadar_output_msg.ttcSteering);
            ROS_INFO("ttcKey:               %s", ttcRadar_output_msg.ttcKey.c_str());

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

    // Connect to COM port of Radar 
    if (!ttcRadarObj.init_cfg_port()) return -1;
    
    #ifdef DataPort_EN
    if (!ttcRadarObj.init_data_port()) return -1;
    #endif
    
    // TTC config or MPC config
    ttcRadarObj.start_radar();
//    ttcRadarObj.start_radar_MPC();

    ttcRadarObj.initParamTTC();

    // Timer to receive data from Radar
    ros::Timer timer_uart = n.createTimer(ros::Duration(0.05), timer_uart_Callback);

    // While loop do nothing, data received by interrupt
    while(ros::ok()) {
        ros::spin();
    }
}
