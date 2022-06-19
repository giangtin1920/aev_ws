#include "ttcRadar_Cfg.h"

ttcRAdarObj::ttcRAdarObj()
{

}

ttcRAdarObj::~ttcRAdarObj()
{

}


/*----------Config Radar----------------------------------*/

bool ttcRAdarObj::init_cfg_port(void)
{
    // Init Radar Config Port
    try
    {
        ser_Cfg_Port.setPort(ser_Cfg_Port_Name);
        ser_Cfg_Port.setBaudrate(115200);
        serial::Timeout to1 = serial::Timeout::simpleTimeout(1000);
        ser_Cfg_Port.setTimeout(to1);
        ser_Cfg_Port.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open config port ");
        return false;
    }
    if (ser_Cfg_Port.isOpen()) {
        ROS_INFO_STREAM("Radar Config Port initialized");
        return true;
    }
    else
        return false;
}

bool ttcRAdarObj::init_data_port(void)
{
    // Init Radar Data Port
    try
    {
        ser_Data_Port.setPort(ser_Data_Port_Name);
        ser_Data_Port.setBaudrate(921600);
        serial::Timeout to2 = serial::Timeout::simpleTimeout(1000);
        ser_Data_Port.setTimeout(to2);
        ser_Data_Port.open();
    }
    catch (serial::IOException& e)
    {
        ROS_ERROR_STREAM("Unable to open data port ");
        return false;
    }
    if (ser_Data_Port.isOpen()) {
        ROS_INFO_STREAM("Radar Data Port initialized");
        return true;
    }
    else
        return 1;
}

void ttcRAdarObj::send_cfg(std::string msg)
{
    ros::Rate loop_rate1(CFG_LOOP_RATE);

    ser_Cfg_Port.write(msg + "\n");
    ROS_INFO_STREAM("Send: " << msg);
    loop_rate1.sleep();

    if (ser_Cfg_Port.available()) {
      std_msgs::String result;
      result.data = ser_Cfg_Port.read(ser_Cfg_Port.available());
      ROS_INFO_STREAM("-Read: " << result.data);
      //read_pub.publish(result);
    }
    loop_rate1.sleep();
}

void ttcRAdarObj::start_radar(void)
{
  std::string msg;
  msg = "sensorStop";
  send_cfg(msg);

  msg = "flushCfg";
  send_cfg(msg);

  msg = " dfeDataOutputMode 1 ";
  send_cfg(msg);

  msg = " channelCfg 15 7 0 ";
  send_cfg(msg);

  msg = " adcCfg 2 1 ";
  send_cfg(msg);

  msg = " adcbufCfg -1 0 1 1 1 ";
  send_cfg(msg);

  msg = " profileCfg 0 60.25 8 7 28 0 0 20 1 256 12500 0 0 48 ";
  send_cfg(msg);

  msg = " chirpCfg 0 0 0 0 0 0 0 1 ";
  send_cfg(msg);

  msg = " chirpCfg 1 1 0 0 0 0 0 4 ";
  send_cfg(msg);

  msg = " chirpCfg 2 2 0 0 0 0 0 2 ";
  send_cfg(msg);

  // 55 is 55ms delay between 2 output frame
  msg = " frameCfg 0 0 140 0 100 1 0 ";
  send_cfg(msg);

  msg = " lowPower 0 0 ";
  send_cfg(msg);

  msg = " guiMonitor -1 1 0 0 0 0 0 ";
  send_cfg(msg);

  //Threshold scale [0..100]
  msg = " cfarCfg -1 0 2 8 4 3 0 10 0 ";
  send_cfg(msg);

  msg = " cfarCfg -1 1 0 4 2 3 1 20 0 ";
  send_cfg(msg);

  msg = " multiObjBeamForming -1 1 0.5 ";
  send_cfg(msg);

  msg = " clutterRemoval -1 1 ";
  send_cfg(msg);

  msg = " calibDcRangeSig -1 0 -5 8 256 ";
  send_cfg(msg);

  msg = " extendedMaxVelocity -1 0 ";
  send_cfg(msg);

  msg = " bpmCfg -1 0 0 1 ";
  send_cfg(msg);

  msg = " lvdsStreamCfg -1 0 0 0 ";
  send_cfg(msg);

  msg = " compRangeBiasAndRxChanPhase 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 ";
  send_cfg(msg);

  msg = " measureRangeBiasAndRxChanPhase 0 1.5 0.2 ";
  send_cfg(msg);

  msg = " CQRxSatMonitor 0 3 15 125 0 ";
  send_cfg(msg);

  msg = " CQSigImgMonitor 0 115 6 ";
  send_cfg(msg);

  msg = " analogMonitor 0 0 ";
  send_cfg(msg);

  // View config (degrees) : [ -1 <minAzimuthDeg> <maxAzimuthDeg> <minElevationDeg> <maxElevationDeg> ]
  msg = " aoaFovCfg -1 -60 60 0 10 ";
  send_cfg(msg);

  // Config point filtering in range direction (meter)
  msg = " cfarFovCfg -1 0 2 75 ";
  send_cfg(msg);

  // Config point filtering in Doppler direction (meter/sec)
  msg = " cfarFovCfg -1 1 -20 20 ";
  send_cfg(msg);

  // *****************TRACKING COMMANDS*****************************
  // https://dev.ti.com/tirex/explore/content/mmwave_industrial_toolbox_4_7_0/labs/people_counting/docs/3D_people_counting_tracker_layer_tuning_guide.pdf
  msg = " staticBoundaryBox -1 1 0 1 0 1 ";
  send_cfg(msg);

  msg = " boundaryBox -6 1 5 75 0 1 ";
  send_cfg(msg);

  msg = " gatingParam 50 5 5 2 20 ";
  send_cfg(msg);

  msg = " stateParam 3 3 3 1 1 ";
  send_cfg(msg);

  msg = " allocationParam 200 100 0.05 5 16 20 ";
  send_cfg(msg);

  msg = " maxAcceleration 20 20 20 ";
  send_cfg(msg);

  msg = " trackingCfg 1 2 500 25 200 50 100 90 ";
  send_cfg(msg);

  // *****************STATIC DETECTION COMMANDS*********************
  msg = " heatmapGenCfg -1 1 0 10 130 60 3 10 ";
  send_cfg(msg);

  msg = " staticDetectionCfg -1 0 -50 50 0 20 0.7 6 0.2 4 20 ";
  send_cfg(msg);

  msg = "sensorStart";
  send_cfg(msg);
}

void ttcRAdarObj::start_radar_MPC(void)
{
  std::string msg;
  msg = "sensorStop";
  send_cfg(msg);

  msg = "flushCfg";
  send_cfg(msg);

  msg = " dfeDataOutputMode 1 ";
  send_cfg(msg);

  msg = " channelCfg 15 7 0 ";
  send_cfg(msg);

  msg = " adcCfg 2 1 ";
  send_cfg(msg);

  msg = " adcbufCfg -1 0 1 1 1 ";
  send_cfg(msg);

  msg = " profileCfg 0 60.25 4 3.9 22.73 0 0 41.91 1 166 9313 3 0 30 ";
  send_cfg(msg);

  msg = " chirpCfg 0 0 0 0 0 0 0 1 ";
  send_cfg(msg);

  msg = " chirpCfg 1 1 0 0 0 0 0 4 ";
  send_cfg(msg);

  msg = " chirpCfg 2 2 0 0 0 0 0 2 ";
  send_cfg(msg);

  // 55 is 55ms delay between 2 output frame
  msg = " frameCfg 0 0 140 0 100 1 0 ";
  send_cfg(msg);

  msg = " lowPower 0 0 ";
  send_cfg(msg);

  msg = " guiMonitor -1 1 0 0 0 0 0 ";
  send_cfg(msg);

  //Threshold scale [0..100]
  msg = " cfarCfg -1 0 2 8 4 3 0 10 0 ";
  send_cfg(msg);

  msg = " cfarCfg -1 1 0 4 2 3 1 15 0 ";
  send_cfg(msg);

  msg = " multiObjBeamForming -1 1 0.5 ";
  send_cfg(msg);

  msg = " clutterRemoval -1 1 ";
  send_cfg(msg);

  msg = " calibDcRangeSig -1 0 -5 8 256 ";
  send_cfg(msg);

  msg = " extendedMaxVelocity -1 0 ";
  send_cfg(msg);

  msg = " bpmCfg -1 0 0 1 ";
  send_cfg(msg);

  msg = " lvdsStreamCfg -1 0 0 0 ";
  send_cfg(msg);

  msg = " compRangeBiasAndRxChanPhase 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 ";
  send_cfg(msg);

  msg = " measureRangeBiasAndRxChanPhase 0 1.5 0.2 ";
  send_cfg(msg);

  msg = " CQRxSatMonitor 0 3 15 125 0 ";
  send_cfg(msg);

  msg = " CQSigImgMonitor 0 115 6 ";
  send_cfg(msg);

  msg = " analogMonitor 0 0 ";
  send_cfg(msg);

  // View config (degrees) : [ -1 <minAzimuthDeg> <maxAzimuthDeg> <minElevationDeg> <maxElevationDeg> ]
  msg = " aoaFovCfg -1 -40 40 0 20 ";
  send_cfg(msg);

  // Config point filtering in range direction (meter)
  msg = " cfarFovCfg -1 0 1 50 ";
  send_cfg(msg);

  // Config point filtering in Doppler direction (meter/sec)
  msg = " cfarFovCfg -1 1 -20 20 ";
  send_cfg(msg);

  // *****************TRACKING COMMANDS*****************************
  // https://dev.ti.com/tirex/explore/content/mmwave_industrial_toolbox_4_7_0/labs/people_counting/docs/3D_people_counting_tracker_layer_tuning_guide.pdf
  msg = " staticBoundaryBox -1 1 0 1 0 1 ";
  send_cfg(msg);

  msg = " boundaryBox -4 1 2 50 0 1.5 ";
  send_cfg(msg);

  msg = " gatingParam 200 6 6 6 20 ";
  send_cfg(msg);

  msg = " stateParam 3 1 1 1 1 ";
  send_cfg(msg);

  msg = " allocationParam 2200 2150 0.01 10 20 20 ";
  send_cfg(msg);

  msg = " maxAcceleration 8 8 8 ";
  send_cfg(msg);

  msg = " trackingCfg 1 2 500 25 200 50 100 90 ";
  send_cfg(msg);

  // *****************STATIC DETECTION COMMANDS*********************
  msg = " heatmapGenCfg -1 1 0 10 130 60 3 10 ";
  send_cfg(msg);

  msg = " staticDetectionCfg -1 0 -50 50 0 20 0.7 6 0.2 4 20 ";
  send_cfg(msg);

  msg = "sensorStart";
  send_cfg(msg);
}

void ttcRAdarObj::stop_radar(void)
{
    std::string msg;
    msg = "sensorStop";
    send_cfg(msg);
    msg = "sensorStop";
    send_cfg(msg);

//    msg = "flushCfg";
//    send_cfg(msg);
}

/*----------Frame Header----------------------------------*/

structPacket ttcRAdarObj::getFramePacket(std_msgs::UInt8MultiArray raw_data, vector<uint16_t> &startIdx, uint16_t dataLen)
{
    structPacket framePacket;
    startIdx.clear();

    // Magic word = {2,1,4,3,6,5,8,7}
    const uint16_t lenMagicWord = 7;

    for (uint16_t i = 0; i < dataLen - lenMagicWord; i++) {
        // check start index of Magic word
        if (raw_data.data[i] == 2 && raw_data.data[i+1] == 1 && raw_data.data[i+2] == 4 && raw_data.data[i+3] == 3
            && raw_data.data[i+4] == 6 && raw_data.data[i+5] == 5 && raw_data.data[i+6] == 8 && raw_data.data[i+7] == 7)
        {
            startIdx.push_back(i);
        }
    }

    // Check that startIdx is not empty // framePacket has executed only 1 frame
    startIdx.push_back(dataLen);

    //update dataLen
    framePacket.dataLen = startIdx[1] - startIdx[0];

    //Remove the data before the first start index
    for (uint16_t i = 0; i < (framePacket.dataLen); i++) {
        framePacket.data.push_back(raw_data.data[startIdx[0] + i]);

        // print all frame to parse
        // int a = framePacket.data[i];
        // cout << a << ' ';
    }

    return framePacket;
}

structHeader ttcRAdarObj::getFrameHeader (structPacket framePacket)
{
    structHeader frameHeader;

    // check that all packet has been read
    frameHeader.totalPacketLen = framePacket.data[12] + framePacket.data[13] * 256.0 + framePacket.data[14] * 65536.0 + framePacket.data[15] * 1.6777216E+7;
    uint32_t idX = 0;

    // read the header
    if (frameHeader.totalPacketLen != framePacket.dataLen) return frameHeader;

    // word array to convert 4 bytes to a 32 bit number
    // word = [1, 2**8, 2**16, 2**24]

    // Initialize the pointer index
    for (int idX = 0; idX < 8; idX++) {
        frameHeader.magicWord[idX] = framePacket.data[idX];
    }
    idX += 8;
    for (int idX = 0; idX < 4; idX++) {
        frameHeader.version[idX] = framePacket.data[idX + 8];
    }
    idX += 4;
    frameHeader.totalPacketLen = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.platform = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.frameNumber = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.timeCpuCycles = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.numDetectedObj = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.numTLVs = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.subFrameNumber = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;
    frameHeader.numStaticDetectedObj  = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
    idX += 4;

    frameHeader.idX = idX;

//    ROS_INFO("totalPacketLen: %u", frameHeader.totalPacketLen);
//    ROS_INFO("frameNumber: %u", frameHeader.frameNumber);
    ROS_INFO("numDetectedObj: %u", frameHeader.numDetectedObj);
//    ROS_INFO("numTLVs: %u \r\n", frameHeader.numTLVs);

    return frameHeader;
}


/*----------Frame TLV----------------------------------*/

void ttcRAdarObj::clearPtCloud(void)
{

    ptStaticDetObj.x.clear();
    ptStaticDetObj.y.clear();
    ptStaticDetObj.z.clear();
    ptStaticDetObj.doppler.clear();

    ptDetObj.x.clear();
    ptDetObj.y.clear();
    ptDetObj.z.clear();
    ptDetObj.doppler.clear();

    ptSideInfo.snr.clear();
    ptSideInfo.noise.clear();

    ptTargets.tid.clear();
    // ptTargets.posX.push_back(data.myFloat[i * 4]);
    ptTargets.posX.clear();
    ptTargets.posY.clear();
    ptTargets.velX.clear();
    ptTargets.velY.clear();
    ptTargets.accX.clear();
    ptTargets.accY.clear();
    ptTargets.posZ.clear();
    ptTargets.velZ.clear();
    ptTargets.accZ.clear();

    Output.IdObj.clear();
    Output.isApproach.clear();
    Output.alpha.clear();
    Output.dis.clear();
    Output.vel.clear();
    Output.ttc.clear();
    Output.safetyZone.clear();
    Output.isObject = false;

}

void ttcRAdarObj::getDetObj(void)
{
    int numDetectedObj = tlv.length/16;
    byte2float data = {0};
    data.myByte.clear();

    if (numDetectedObj) {

        // Convert 4byte to float
        for (uint32_t i = 0; i < tlv.length; i++) {
            data.myByte.push_back(tlv.payload[i]);
        }

        for (int i = 0; i < numDetectedObj; i++) {
            // ptDetObj.range.push_back(data.myFloat[i * 4]);
            // ptDetObj.angle.push_back(data.myFloat[i * 4 + 1]);
            // ptDetObj.elev.push_back(data.myFloat[i * 4 + 2]);
            ptDetObj.doppler.push_back(data.myFloat[i * 4 + 3]);

            ptDetObj.z.push_back(   data.myFloat[i * 4]             *   sin(data.myFloat[i * 4 + 2])                        );
            ptDetObj.y.push_back(   cos(data.myFloat[i * 4 + 2])    *   cos(data.myFloat[i * 4 + 2]) * data.myFloat[i * 4]  );
            ptDetObj.x.push_back(   sin(data.myFloat[i * 4 + 2])    *   cos(data.myFloat[i * 4 + 2]) * data.myFloat[i * 4]  );

//            ROS_INFO("x = %f ", ptDetObj.x[i]);
//            ROS_INFO("y = %f ", ptDetObj.y[i]);
//            ROS_INFO("z = %f ------", ptDetObj.z[i]);

        }
    }
}

void ttcRAdarObj::getSideInfo(void)
{
    int numDetectedObj = tlv.length/4;

    if (numDetectedObj) {
        for (uint32_t i = 0; i < tlv.length ; i+=4) {
            ptSideInfo.snr.push_back(tlv.payload[i]*1 + tlv.payload[i+1]*256.0);
            ptSideInfo.noise.push_back(tlv.payload[i+2]*1 + tlv.payload[i+3]*256.0);

             ROS_INFO("snr   = %u ", ptSideInfo.snr[i]);
             ROS_INFO("noise = %u ", ptSideInfo.noise[i]);
        }
    }
}

void ttcRAdarObj::getStaticObj(void)
{
    int numDetectedObj = tlv.length/16;
    byte2float data = {0};
    data.myByte.clear();

    if (numDetectedObj) {
        // Convert 4byte to float
        for (uint32_t i = 0; i < tlv.length; i++) {
            data.myByte.push_back(tlv.payload[i]);
        }

        for (int i = 0; i < numDetectedObj; i++) {
            ptStaticDetObj.x.push_back(data.myFloat[i * 4]);
            ptStaticDetObj.y.push_back(data.myFloat[i * 4 + 1]);
            ptStaticDetObj.z.push_back(data.myFloat[i * 4 + 2]);
            ptStaticDetObj.doppler.push_back(data.myFloat[i * 4 + 3]);
        }
    }
}

void ttcRAdarObj::getGtrackTargetList(void)
{
    int numDetectedObj = tlv.length/40;
    byte2float data = {0};
    data.myByte.clear();

    if (numDetectedObj) {
        // Convert 4byte to float
        for (uint32_t i = 0; i < tlv.length; i++) {
            data.myByte.push_back(tlv.payload[i]);
            // ROS_INFO("frame %d: %u", i, tlv.payload[i]);
        }
        // ROS_INFO("kq %f", i, tlv.payload[i]);

        for (int i = 0; i < numDetectedObj; i++) {
            ptTargets.tid.push_back(tlv.payload[i * 40 + 0]*1 + tlv.payload[i * 40 + 1]*256.0 + tlv.payload[i * 40 + 2]*65536.0 + tlv.payload[i * 40 + 3]*1.6777216E+7);
            // ptTargets.tid.push_back(data.myFloat[i * 10 + 0]);
            ptTargets.posX.push_back(data.myFloat[i * 10 + 1]);
            ptTargets.posY.push_back(data.myFloat[i * 10 + 2]);
            ptTargets.velX.push_back(data.myFloat[i * 10 + 3]);
            ptTargets.velY.push_back(data.myFloat[i * 10 + 4]);
            ptTargets.accX.push_back(data.myFloat[i * 10 + 5]);
            ptTargets.accY.push_back(data.myFloat[i * 10 + 6]);
            ptTargets.posZ.push_back(data.myFloat[i * 10 + 7]);
            ptTargets.velZ.push_back(data.myFloat[i * 10 + 8]);
            ptTargets.accZ.push_back(data.myFloat[i * 10 + 9]);

            // ROS_INFO("ID Object = %u ", ptTargets.tid[i]);
            // ROS_INFO("posX = %f ", ptTargets.posX[i]);
            // ROS_INFO("posY = %f ", ptTargets.posY[i]);
            // ROS_INFO("velX = %f ", ptTargets.velX[i]);
            // ROS_INFO("velY = %f ", ptTargets.velY[i]);
            // ROS_INFO("posZ = %f ", ptTargets.posZ[i]);

        }
    }
}


structTLV ttcRAdarObj::getTLV (structPacket framePacket, uint32_t numTLVs, uint32_t idX)
{
    // clear all the elements of the vector container
    clearPtCloud();

    // read all (numTLVs)TLVs to ptCloud
    for (uint32_t tlvIdx = 0; tlvIdx < numTLVs; tlvIdx++) {
        tlv.payload.clear();

        // check the header of the TLV message
        tlv.type = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
        idX += 4;
        tlv.length = framePacket.data[idX]*1 + framePacket.data[idX + 1]*256.0 + framePacket.data[idX + 2]*65536.0 + framePacket.data[idX + 3]*1.6777216E+7;
        idX += 4;
        for (uint32_t i = 0; i < tlv.length ; i++) {
                tlv.payload.push_back(framePacket.data[idX + i]);
        }
        idX += tlv.length;
        tlv.idX = idX;
        // ROS_INFO("type: %u  --------", tlv.type);
        // ROS_INFO("len: %u  ", tlv.length);


        switch (tlv.type) {
            // getGtrackPtCloud() == 1
            case MMWDEMO_UART_MSG_DETECTED_POINTS : {
//                 getDetObj();
            }
            break;

            // getGtrackPtCloud() == 7
            case MMWDEMO_UART_MSG_DETECTED_POINTS_SIDE_INFO : {
//             getSideInfo();
            }
            break;

            // getStaticObj == 8
            case MMWDEMO_UART_MSG_STATIC_DETECTED_POINTS : {
//                 getStaticObj();
            }
            break;

            // getGtrackTargetList == 10
            case MMWDEMO_UART_MSG_TRACKERPROC_TARGET_LIST : {
                getGtrackTargetList();
            }
            break;

            case MMWDEMO_UART_MSG_RANGE_PROFILE:
            break;
            case MMWDEMO_UART_MSG_NOISE_PROFILE:
            break;
            default:
            break;
        }
    }

    return tlv;
}


/*----------Data Handle----------------------------------*/

bool ttcRAdarObj::processingGtrackTarget(void)
{
    Output.numObj = ptTargets.tid.size();
    //
    for (uint16_t i = 0; i < Output.numObj; i++) {

        if (!ptTargets.velY[i]) ptTargets.velY.at(i) = 0.0001;  // Dividing a number by Zero
        Output.IdObj.push_back(ptTargets.tid[i]);
        Output.isObject = true;
        Output.dis.push_back( sqrt(pow(ptTargets.posX[i],2) + pow(ptTargets.posY[i],2) ));
        Output.alpha.push_back(acos(ptTargets.posX[i] / Output.dis[i]));
        Output.vel.push_back( ptTargets.velX[i]*cos(Output.alpha[i]) + ptTargets.velY[i]*cos(M_PI_2 - Output.alpha[i]) );
        float gamma = acos(-Output.vel[i]/sqrt( pow(ptTargets.velX[i],2) + pow(ptTargets.velY[i],2)));

        // gamma is angle of (velocity, vector(radar, point))
        float ttcPosX = 5.0f;
        float maxttcPosX = 1; // width of AEVs (m)
        if (gamma >= 0 && gamma < M_PI_2) {
            ttcPosX = ptTargets.posX[i] - (ptTargets.velX[i]*ptTargets.posY[i])/ptTargets.velY[i];
        }

        if (ttcPosX > -maxttcPosX && ttcPosX < maxttcPosX) {
            Output.isApproach.push_back(true);
        }
        else {
            Output.isApproach.push_back(false);
        }

        Output.ttc.push_back(Output.dis[i] / abs(Output.vel[i]));
        if (Output.ttc.at(i) > 99) Output.ttc.at(i) = 99;

        if (!Output.isApproach[i])
          Output.safetyZone.push_back("carNormal");
        else if(Output.ttc[i] < paramTTC.accidence)
          Output.safetyZone.push_back("carAccidence");
        else if(Output.ttc[i] < paramTTC.warning)
          Output.safetyZone.push_back("carWarning");
        else
          Output.safetyZone.push_back("carSafety");


//        ROS_INFO("ID Track Object =============, %u ", ptTargets.tid[i]);
//        ROS_INFO("alpha:        deg,     %f", Output.alpha[i]*180/M_PI);
        ROS_INFO("distance:     m,      %f", Output.dis[i]);
//        ROS_INFO("gamma:        deg,     %f", gamma*180/M_PI);
        ROS_INFO("velocity:     m/s,    %f", Output.vel[i]);
        ROS_INFO("is Approach:  m,      %f", ttcPosX);
        ROS_INFO("TTC:          s,      %f", Output.ttc[i]);
    }

    return true;
}

float ttcRAdarObj::processingPtMinDistance (structHeader frameHeader)
{

    // sorting vector distance in increasing order
    sort(ptDetObj.y.begin(), ptDetObj.y.end());

    // para config output
    float delta = 0.3;
    float numRangePt = 1;
    float ptMinDistance = 0;
    float rangePt = (float)(ptDetObj.y.size())/3;

    // for (int i = 0; i < ptDetObj.y.size(); i++) {
    //    ROS_INFO("y= %f", ptDetObj.y[i]);
    // }

    // check the numDetected, 
    if (ptDetObj.y.size() > 1) {
        for (size_t i = 0; i < ptDetObj.y.size() - 1; i++) {
            ptMinDistance = ptDetObj.y[i];
            numRangePt = 1;
            for (size_t j = 0; j < ptDetObj.y.size() - 1 - i; j++) {
                if(abs(ptDetObj.y[i + j +1] - ptDetObj.y[i]) < delta) {
                    ptMinDistance += ptDetObj.y[i + j +1];
                    numRangePt++;
                }
            }
//            ROS_INFO("numRangePt = %f", numRangePt);

            if(numRangePt >= rangePt) {
                ptMinDistance = ptMinDistance/(int)numRangePt;
                break;
            }
            else {
                ptMinDistance = ptDetObj.y[0];
            }
        }
    }
    else if(ptDetObj.y.size() == 1) {
        ptMinDistance = ptDetObj.y[0];
    }
    else {
        ptMinDistance = 20.0;
    }
//    ROS_INFO("outDisTmp = %f", ptMinDistance);
    
    // fillter 2
    float delta_2 = 0.8;
    float numRangePt_2 = 1;
    bufDistance.push_back(ptMinDistance); // vector global

    // buffer output distance has 5 elements
    if (bufDistance.size() == 6) {
        for (int i = 0; i < bufDistance.size() - 1; i++) {
//        ROS_INFO("bufDis= %f", bufDistance[i+1]);
        }

        bufDistance.erase(bufDistance.begin());
        float rangePt_2 = (float)(bufDistance.size())/2; // how many elements to fit 

        for (size_t i = 0; i < bufDistance.size() - 1; i++) {
            ptMinDistance = bufDistance[i];
            numRangePt_2 = 1;
            for (size_t j = 0; j < bufDistance.size() - 1 - i; j++) {
                if(abs(bufDistance[i + j +1] - bufDistance[i]) < delta_2)
                {
                    ptMinDistance += bufDistance[i + j +1];
                    numRangePt_2++;
                }
            }
//            ROS_INFO("numRangePt_2 = %f", numRangePt_2);

            if(numRangePt_2 >= rangePt_2) {
                ptMinDistance = ptMinDistance/(int)numRangePt_2;
                break;
            }
            else {
                ptMinDistance = bufDistance[0];
//                ROS_INFO("no filter 2");
            }
        }
    }

    return ptMinDistance;
}

bool ttcRAdarObj::data_handler( std_msgs::UInt8MultiArray raw_data, uint16_t dataLen)
{
    bool is_data_ok = false;

    // Check for all possible locations of the magic word to startIdx
    structPacket framePacket = getFramePacket(raw_data, startIdx, dataLen);

    // Processing
    if (!framePacket.dataLen) return is_data_ok;

    // Read the Header messages
    structHeader frameHeader = getFrameHeader(framePacket);
    uint32_t idX = frameHeader.idX;

    // Check is_data_ok
    if (!frameHeader.numTLVs) return (is_data_ok = false);
    is_data_ok = true;

    // Read the TLV messages
    structTLV tlv = getTLV(framePacket, frameHeader.numTLVs, idX);
    idX = tlv.idX;

    // processing output
    switch (modeRadar)
    {
        case ENABLE_RADAR_TTC: {
            bool isTrackedObj = processingGtrackTarget();
        }
        break;

        case ENABLE_RADAR_MPC: {
            float ptMinDistance = processingPtMinDistance(frameHeader);
            // update output
            if (frameHeader.numDetectedObj) {
                Output.isObject = true;
                Output.dis.push_back(ptMinDistance);
                ROS_INFO("\nisObject ============= %d",1);
                ROS_INFO("distance ============= %f",ptMinDistance);
            }
            else {
                Output.isObject = false;
                Output.dis.push_back(ptMinDistance);
                ROS_INFO("isObject ============= %d",0);
                ROS_INFO("distance ============= %f", ptMinDistance);
            }

        }
        break;

        default:
        break;
    }

    return is_data_ok;
}

void ttcRAdarObj::clear_msg(aev_pkg::radar_msg &msg)
{
    msg.numObj = 0;
    msg.IdObj.clear();
    msg.isApproach.clear();
    msg.alpha.clear();
    msg.posX.clear();
    msg.posY.clear();
    msg.dis.clear();
    msg.vel.clear();
    msg.ttc.clear();
    msg.safetyZone.clear();
    msg.ptX.clear();
    msg.ptY.clear();
    msg.ptZ.clear();

//    msg.staticPosX.clear();
//    msg.staticPosY.clear();

    msg.isObject = false;
    msg.distance = 20;

}

void ttcRAdarObj::initParamTTC()
{
  paramTTC.safety = 50;
  paramTTC.warning = 30;
  paramTTC.accidence = 1;

  paramTTC.carNormal = "white";
  paramTTC.carSafety = "green";
  paramTTC.carWarning = "yellow";
  paramTTC.carAccidence = "red";
}


