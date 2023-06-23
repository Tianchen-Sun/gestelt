# gestelt
A simple path planning framework for swarm robots. This is a work in progress, and a lot of existing components are refactored parts of the work done by ZJU in [EGO-Planner-V2 repo](https://github.com/ZJU-FAST-Lab/EGO-Planner-v2).

# Requirements
1. Operating System/Frameworks
    - Ubuntu 20.04 (ROS Noetic)
2. Tools
    - vcstool: For repo setup 
    - xmlstarlet: For multi-vehicle simulation
3. Simulation
    - Gazebo Classic (Version 11)
    - PX4-Autopilot (Main branch)
    - Simple Quad Simulator
4. Other packages:
    - MavROS 
    - plotjuggler (For visualization of data over time)
    - Listed in "Setup" section

# Setup
1. Install binaries
```bash 
export ROS_DISTRO="noetic"

# Install ROS dependencies
sudo apt install ros-${ROS_DISTRO}-tf2-sensor-msgs -y
sudo apt install ros-${ROS_DISTRO}-mavlink ros-${ROS_DISTRO}-mavros ros-${ROS_DISTRO}-mavros-msgs ros-${ROS_DISTRO}-mavros-extras -y
# Install external dependencies
sudo apt install tmux python3-vcstool xmlstarlet -y
sudo apt install protobuf-compiler libeigen3-dev libopencv-dev libgoogle-glog-dev -y
wget https://raw.githubusercontent.com/mavlink/mavros/master/mavros/scripts/install_geographiclib_datasets.sh
sudo bash ./install_geographiclib_datasets.sh
# Extra tools for debugging
sudo snap install plotjuggler
```

2. Clone repositories
```bash
mkdir -p ~/gestelt_ws/src/
cd ~/gestelt_ws/src
git clone https://github.com/JohnTGZ/gestelt.git
cd gestelt
vcs import < thirdparty.repos --recursive
```

3. Install PX4 firmware
```bash
# cd to PX4-Autopilot repo
cd ~/gestelt_ws/PX4-Autopilot
bash ./Tools/setup/ubuntu.sh --no-nuttx
# Make SITL target for Gazebo simulation
DONT_RUN=1 make px4_sitl_default gazebo-classic
cp -r ~/gestelt_ws/src/gestelt/gestalt_bringup/simulation/models/raynor ~/gestelt_ws/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/models/

# If you screw up the PX4 Autopilot build at any point, clean up the build files via the following command:
make distclean
```

# Future Roadmap
- Solidify framework for managing multiple robots
- Port to ROS2
- Investigate changing the custom GridMap implementation to alternatives such as Octomap but still consider the potential performance issues with an established library.
- Trajectory Server
    - Support Cancel/Start/Pause of waypoints execution
    - Handle goals in obstacle regions (Cancel the goal?)
    - Check if every UAV in formation has finished execution of current waypoint before planning for the next one

# Acknowledgements
Plenty of inspiration was taken from the [EGO-Planner-V2 repo](https://github.com/ZJU-FAST-Lab/EGO-Planner-v2) from ZJU, without which, this would not have been possible.