# AEV workspace catkin by giangtin
aev/aev_ws

# Building workspace by hand
mkdir -p ~/aev/aev_ws/src
cd ~/aev/aev_ws
catkin_make
source ~/aev/aev_ws/devel/setup.bash
. ~/aev/aev_ws/devel/setup.bash

# install serial port
sudo apt-get install ros-melodic-serial

## ubuntu 20.04 (as package)
cd ~/aev/aev_ws/src/
git clone https://github.com/wjwwood/serial.git
make
make test
make install

# add Radar package  to aev_ws
## method 1: create package by hand
cd ~/aev/aev_ws/src
catkin_create_pkg radar_pkg std_msgs rospy roscpp

### create msg
cd radar_pkg/
mkdir msg
cd msg
touch radar_msg.msg
nano radar_msg.msg  (add 3line to this file
uint32 msg_counter
bool isObject
float32 distance
)

### edit CmakeLists.txt
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  serial
  message_generation
)

add_message_files(
  FILES
  radar_msg.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES radar_pkg
  CATKIN_DEPENDS roscpp rospy std_msgs
  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#### add to the end line
add_executable(
  listener
  src/listener.cpp
)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener radar_pkg_generate_messages_cpp)

add_executable(
  radar 
  src/Radar.cpp
  src/Radar_Cfg.cpp
)
target_link_libraries(radar ${catkin_LIBRARIES})
add_dependencies(radar radar_pkg_generate_messages_cpp)

### edit package.xml
  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>

### add Radar node
copy Radar.cpp(s) to ~/aev/aev_ws/src/radar_pkg/src$ 

## method 2: Github
cd ~/aev/aev_ws/src/
git clone https://github.com/giangtin1920/aev_ws

# build ws
cd ~/aev/aev_ws/
catkin_make

# run roscore
roscore

# run package Radar in another Terminal
rosrun aev_pkg Radar