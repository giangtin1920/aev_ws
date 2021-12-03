#include "Radar_Cfg.h"

RadarObj::RadarObj()
{

}

RadarObj::~RadarObj()
{

}


bool RadarObj::init_cfg_port(void)
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
    if(ser_Cfg_Port.isOpen()){
        ROS_INFO_STREAM("Radar Config Port initialized");
    }else{
        return false;
    }
}

bool RadarObj::init_data_port(void)
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
    if(ser_Data_Port.isOpen()){
        ROS_INFO_STREAM("Radar Data Port initialized");
    }else{
        return 1;
    }
}

void RadarObj::send_cfg(std::string msg)
{
    ros::Rate loop_rate1(CFG_LOOP_RATE);

    ser_Cfg_Port.write(msg + "\n");
    ROS_INFO_STREAM("Send: " << msg);
    loop_rate1.sleep();

    if(ser_Cfg_Port.available())
    {
      std_msgs::String result;
      result.data = ser_Cfg_Port.read(ser_Cfg_Port.available());
      ROS_INFO_STREAM("-Read: " << result.data);
      //read_pub.publish(result);
    }
    loop_rate1.sleep();
}

void RadarObj::start_radar(void)
{
    std::string msg;

    msg = "sensorStop";
    send_cfg(msg);

    msg = "flushCfg";
    send_cfg(msg);

    msg = "dfeDataOutputMode 1";
    send_cfg(msg);

    msg = "channelCfg 15 5 0";
    send_cfg(msg);

    msg = "adcCfg 2 1";
    send_cfg(msg);

    msg = "adcbufCfg -1 0 1 1 1";
    send_cfg(msg);

    msg = "lowPower 0 0";
    send_cfg(msg);

    msg = "profileCfg 0 60.25 7 3 24 0 0 156 1 256 12500 0 0 30";
    send_cfg(msg);

    msg = "chirpCfg 0 0 0 0 0 0 0 1";
    send_cfg(msg);

    msg = "chirpCfg 1 1 0 0 0 0 0 4";
    send_cfg(msg);

    // 100 is 100ms delay between 2 output frame
    msg = "frameCfg 0 1 32 0 100 1 0";
    send_cfg(msg);

    msg = "guiMonitor -1 1 1 1 0 0 1";
    send_cfg(msg);

    //Threshold scale [0..100]
    msg = "cfarCfg -1 0 2 8 4 3 0 15 0";
    send_cfg(msg);
    msg = "cfarCfg -1 1 0 4 2 3 1 15 0";
    send_cfg(msg);

    msg = "multiObjBeamForming -1 1 0.5";
    send_cfg(msg);

    msg = "calibDcRangeSig -1 0 -5 8 256";
    send_cfg(msg);

    msg = "clutterRemoval -1 0";
    send_cfg(msg);

    // View config (degrees) : [ -1 <minAzimuthDeg> <maxAzimuthDeg> <minElevationDeg> <maxElevationDeg> ]
    msg = "aoaFovCfg -1 -10 10 -8 8";
    send_cfg(msg);

    // Config point filtering in range direction (meter)
    msg = "cfarFovCfg -1 0 0.25 5.0";
    send_cfg(msg);

    // Config point filtering in Doppler direction (meter/sec)
    msg = "cfarFovCfg -1 1 -10 10";
    send_cfg(msg);

    msg = "compRangeBiasAndRxChanPhase 0.0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0";
    send_cfg(msg);

    msg = "measureRangeBiasAndRxChanPhase 0 1. 0.2";
    send_cfg(msg);

    msg = "extendedMaxVelocity -1 0";
    send_cfg(msg);

    msg = "lvdsStreamCfg  -1 0 0 0";
    send_cfg(msg);

    msg = "bpmCfg -1 0 0 0";
    send_cfg(msg);

    msg = "CQRxSatMonitor 0 3 4 99 0";
    send_cfg(msg);

    msg = "CQSigImgMonitor 0 31 4";
    send_cfg(msg);

    msg = "analogMonitor 0 0";
    send_cfg(msg);

    msg = "sensorStart";
    send_cfg(msg);
}

void RadarObj::stop_radar(void)
{
    std::string msg;
    msg = "sensorStop";
    send_cfg(msg);
}

structHeader RadarObj::getFrameHeader (uint8_t framePacket[], uint16_t dataLen)
{
	structHeader frameHeader;
	// check that all packet has been read
    frameHeader.totalPacketLen = framePacket[12] + framePacket[13] * 256.0 + framePacket[14] * 65536.0 + framePacket[15] * 1.6777216E+7;
	uint32_t idX = 0;
	// Read the header
	if ((dataLen >= frameHeader.totalPacketLen) && (dataLen != 0))
	{
		//word array to convert 4 bytes to a 32 bit number
        //word = [1, 2**8, 2**16, 2**24]

        // Initialize the pointer index
        for (auto idX = 0; idX < 8; idX++)
		{
			frameHeader.magicWord[idX] = framePacket[idX];
		}
		idX += 8;
		 for (auto idX = 0; idX < 4; idX++)
		{
			frameHeader.version[idX] = framePacket[idX + 8];
		}
		idX += 4;
        frameHeader.totalPacketLen = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
        frameHeader.platform = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
        frameHeader.frameNumber = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
        frameHeader.timeCpuCycles = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
        frameHeader.numDetectedObj = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
        frameHeader.numTLVs = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
		frameHeader.subFrameNumber = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
        idX += 4;
 	}
	frameHeader.idX = idX;

	return frameHeader;
}

structTLV RadarObj::getTLV (uint8_t framePacket[], uint32_t numTLVs, uint16_t idX)
{
	structTLV tlv;

	// Check the header of the TLV message
	for (auto tlvIdx = 0; tlvIdx < numTLVs; tlvIdx++)
	{
		tlv.type = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
		idX += 4;
		tlv.length = framePacket[idX]*1 + framePacket[idX + 1]*256.0 + framePacket[idX + 2]*65536.0 + framePacket[idX + 3]*1.6777216E+7;
		idX += 4;
		for (auto i = 0; i < tlv.length ; i++)
			{
				tlv.payload.push_back(framePacket[idX + i]);
			}
		idX += tlv.length;

		switch (tlv.type)
		{
			case MMWDEMO_UART_MSG_DETECTED_POINTS :
			{
				// getGtrackPtCloud(payload)
				uint32_t length = tlv.length;
				int numDetectedObj = length/16;
				byte2float data = {0};

				if (numDetectedObj)
				{
					for (auto i = 0; i < length; i++)
						{
							data.myByte.push_back(tlv.payload[i]);
						}

					for (auto i = 0; i < numDetectedObj; i++)
					{
						ptCloud.x.push_back(data.myFloat[i * 4]);
						ptCloud.y.push_back(data.myFloat[i * 4 + 1]);
						ptCloud.z.push_back(data.myFloat[i * 4 + 2]);
						ptCloud.doppler.push_back(data.myFloat[i * 4 + 3]);
					}
					int a = 5;
				}
			}
			break;

			case MMWDEMO_UART_MSG_RANGE_PROFILE:
			break;
			case MMWDEMO_UART_MSG_NOISE_PROFILE:
			break;
			case MMWDEMO_UART_MSG_DETECTED_POINTS_SIDE_INFO:
			break;
			default:
			break;
		}

		
	}
}

bool RadarObj::data_handler(std_msgs::UInt8MultiArray raw_data, uint16_t dataLen)
{
    //if (data_len > 16)
    // std_msgs::String msg;
    // std::stringstream ss;
    bool is_data_ok = false;
    uint8_t magicWord[] = {2,1,4,3,6,5,8,7};
    uint16_t numframesAvailable = 0;
    uint32_t totalPacketLen = 0;


    // ss << "-Read " << data_len << " byte:";
    // for (int i = 0; i < data_len; i++)
    // {
    //   ss << " " << (int)raw_data.data[i];
    // }
    // msg.data = ss.str();
    // ROS_INFO("%s", msg.data.c_str());

    // Processing

	// Check for all possible locations of the magic word
	for (uint16_t i = 0; i < dataLen - 7; i++)
	{
		if (raw_data.data[i] == 2 && raw_data.data[i+1] == 1 && raw_data.data[i+2] == 4 && raw_data.data[i+3] == 3 && raw_data.data[i+4] == 6 && raw_data.data[i+5] == 5 && raw_data.data[i+6] == 8 && raw_data.data[i+7] == 7)
		{
			numframesAvailable++;
		}
	}
	uint32_t startIdx[numframesAvailable + 1];
	uint16_t framesAvailable = 0;
	for (uint16_t i = 0; i < dataLen - 7; i++)
	{
		if (raw_data.data[i] == 2 && raw_data.data[i+1] == 1 && raw_data.data[i+2] == 4 && raw_data.data[i+3] == 3 && raw_data.data[i+4] == 6 && raw_data.data[i+5] == 5 && raw_data.data[i+6] == 8 && raw_data.data[i+7] == 7)
		{
			startIdx[framesAvailable] = i;
			framesAvailable++;
		}
	}

    // Check that startIdx is not empty // byteBuffer has only one frame
	startIdx[numframesAvailable] = dataLen;
	uint8_t bytesBuffer[(startIdx[1] - startIdx[0])];
    if (numframesAvailable)
	{
		//Remove the data before the first start index
		if (startIdx[0] > 0 && startIdx[0] < dataLen)
		{
			for (auto i = 0; i < (startIdx[1] - startIdx[0]); i++)
			{
				bytesBuffer[i] = raw_data.data[startIdx[0] + i];
			}

            //update dataLen
			dataLen = sizeof bytesBuffer / sizeof(uint8_t);
		}
	}

    // Read the total packet length // as only 1 frame in buffer // parse Header and TLV
	uint8_t framePacket[dataLen];
	for (auto i = 0; i < dataLen; i++)
	{
		framePacket[i] = bytesBuffer[i];
	}
	structHeader frameHeader = getFrameHeader(framePacket, dataLen);
	uint32_t idX = frameHeader.idX;

    // Read the TLV messages
	structTLV tlv = getTLV(framePacket, frameHeader.numTLVs, idX);

    // Update output
    //sort(ptCloud.y.begin(), ptCloud.y.end());

    if (frameHeader.numDetectedObj)
    {
        is_data_ok = true;
        Output.isObject = true;
        Output.msg_counter++;
        Output.distance = ptCloud.y[0];
    }

    return is_data_ok;
}
