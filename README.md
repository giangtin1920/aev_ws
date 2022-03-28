# AEV workspace

aev/aev_ws

**Note**: branch of ttcRadar_pkg `https://github.com/giangtin1920/ttcRadar_pkg` named aev_pkg.

*

*

## Description

As a workspace to read framedata from mmWave_AOP_MistralRadar(IWR6843)
###### Workspace for `giangtin@giangtin-Asus` only


## Installation

### 1. Create workspace catkin

    mkdir -p ~/aev
    cd aev/
    git clone https://github.com/giangtin1920/aev_ws
    cd ~/aev/aev_ws
    git config submodule.recurse true
    git submodule update --init

### 2. Install serial port

##### Ubuntu 18.04 melodic

    sudo apt-get install ros-melodic-serial

##### Ubuntu 20.04 noetic

    cd ~/aev/aev_ws/src/
    git clone https://github.com/wjwwood/serial.git
    make
    make test
    make install
    

## Usage

### Build workspace 

    cd ~/aev/aev_ws/
    catkin_make
    source ~/aev/aev_ws/devel/setup.bash
    . ~/aev/aev_ws/devel/setup.bash

### Run node radar in another Terminal

    rosrun aev_pkg ttcRadar
    
### Run node listener in another Terminal

    rosrun aev_pkg ttcListener
    
### Application GUI in QT_ROS

https://github.com/giangtin1920/radarScanQT_ROS
    
### Simulation in Gazebo

https://github.com/giangtin1920/AEV_simulation_ros_gazebo
    
