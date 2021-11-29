# aev_ws
AEV workspace catkin

## the first
mkdir -p ~/aev/aev_ws /src
cd ~/aev/aev_ws
catkin_make
source ~/aev/aev_ws/devel/setup.bash
. ~/aev/aev_ws/devel/setup.bash
cd src
catkin_create_pkg aev_pkg std_msgs rospy roscpp


## create msg
cd aev_pkg/
mkdir msg
cd msg
touch radar_msg.msg
nano radar_msg.msg  (add 3line to this file
uint32 msg_counter
bool isObject
float32 distance
)

## edit CmakeLists.txt
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
  LIBRARIES aev_pkg
  CATKIN_DEPENDS roscpp rospy std_msgs
  DEPENDS system_lib
)

add_executable(
  Radar 
  src/Radar/Radar.cpp
  src/Radar/Radar_Cfg.cpp
)

target_link_libraries(Radar ${catkin_LIBRARIES})


## edit package.xml
  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>

## add Radar node
copy folder Radar to ~/aev/aev_ws/src/aev_pkg/src$ 

## build ws
cd ~/aev/aev_ws/
catkin_make

## run roscore
roscore

## run package Radar in another Terminal
rosrun aev_pkg Radar


## for second time

mkdir aev
cd aev/
git clone https://github.com/giangtin1920/aev_ws
cd aev_ws/





