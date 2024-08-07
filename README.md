# gestelt
A swarm-focused path planning framework. 

For simulation and deployment on a physical drone, PX4 is the firmware of choice, although it is possible to remap the topics for use with Ardupilot or any other Mavlink-compatible firmware.

# Architecture
<img src="docs/pictures/gestelt_architecture_24_10.png" alt="Gestelt Architecture" style="width: 1200px;"/>

# Installation and Setup for Simulation
1. Install dependencies
```bash
# Install ROS (if not done)
sudo apt install ros-noetic-desktop-full

# Install other dependencies
sudo apt install git build-essential tmux python3-catkin-tools python3-vcstool xmlstarlet -y
sudo apt install ros-${ROS_DISTRO}-mavlink ros-${ROS_DISTRO}-mavros ros-${ROS_DISTRO}-mavros-msgs ros-${ROS_DISTRO}-mavros-extras -y
wget https://raw.githubusercontent.com/mavlink/mavros/master/mavros/scripts/install_geographiclib_datasets.sh
sudo bash ./install_geographiclib_datasets.sh
```

2. Clone repositories
```bash
mkdir -p ~/gestelt_ws/src/
cd ~/gestelt_ws/src
git clone https://github.com/JohnTGZ/gestelt.git -b min_snap_tianchensun
cd gestelt
vcs import < simulators.repos --recursive
vcs import < thirdparty.repos --recursive
```

3. Install PX4 firmware
```bash
# cd to PX4-Autopilot repo
cd ~/gestelt_ws/PX4-Autopilot


# Copy the custom controller over
cp -r ~/gestelt_ws/src/gestelt/gestelt_bringup/customized_controller/PositionControl ~/gestelt_ws/PX4-Autopilot/src/modules/mc_pos_control/

bash ./Tools/setup/ubuntu.sh 
# Make SITL target for Gazebo simulation
DONT_RUN=1 make px4_sitl gazebo-classic
# for PX4 V1.13.0
DONT_RUN=1 make px4_sitl gazebo


# Copy the custom drone model over
cp -r ~/gestelt_ws/src/gestelt/gestelt_bringup/simulation/models/raynor ~/gestelt_ws/PX4-Autopilot/Tools/simulation/gazebo-classic/sitl_gazebo-classic/models/
# for PX4 V1.13.0
cp -r ~/gestelt_ws/src/gestelt/gestelt_bringup/simulation/models/raynor ~/gestelt_ws/PX4-Autopilot/Tools/sitl_gazebo/models/


# [EMERGENCY USE] IF you screw up the PX4 Autopilot build at any point, clean up the build files via the following command:
make distclean
```
4. ACADOS solver installation on the Radxa
- Before the installation, the cmake should be updated to the latest version. please refer to this [cmake update](https://zhuanlan.zhihu.com/p/513871916).
- Requirements

  CasADi: version 3.5.5 Info: https://web.casadi.org/
  Numpy: version 1.23.0 Info: https://numpy.org/
  Pytorch: version 1.12.0+cu116 Info: https://pytorch.org/
  Matplotlib: version 3.3.0 Info:   https://matplotlib.org/
  Python: version 3.8.10 Info: https://www.python.org/
  ACADOS: version LATEST Info: https://docs.acados.org/
    Please refer to this [acados doc](https://docs.acados.org/installation/index.html#linux-mac) for detail.

- Modification to the installation process for the Radxa:
  - After the MAKE installation
     - In the `acados/CMakeLists.txt`,the `BLASFEO_TARGET`and the `HPIPM_TARGET` should be set to `ARMV8A_ARM_CORTEX_A53`.
     - In the `acados/Makefile.rule`, the `BLASFEO_TARGET` should be set to `ARMV8A_ARM_CORTEX_A53` .
     - In the `acados/Makefile.rule`, the `HPIPM_TARGET` should be set to `GENERIC` .
     - 
  - Before `make run_examples_c`
    -  add `export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/acados/lib` to the `~/.bashrc` file.
    -  add `export ACADOS_SOURCE_DIR=~/acados` to the `~/.bashrc` file. for acados python interface.
    -  `source ~/.bashrc`
  -  Install ACADOS [python interface](https://docs.acados.org/python_interface/index.html)
     -  `tera_renderer` should be installed from source. refer to this [tera_renderer solution](https://discourse.acados.org/t/problems-with-t-renderer/438)


  
1. Building the workspace
```bash
# Assuming your workspace is named as follows
cd ~/gestelt_ws/

# Building for debugging/development
catkin config --merge-devel
catkin clean
catkin build
# Building for release mode (For use on Radxa)
catkin build -DCMAKE_BUILD_TYPE=Release
```

# Quick start
There are 2 scripts you can use to run an example simulation. 

## 1. Run PX4 SITL with Gazebo. 
The first script runs a simulated PX4 SITL instance with Gazebo, with physics. This should be tested before deployment on an actual drone. It runs the following:
1. Gazebo simulation environment.
2. Trajectory Server.
3. Minimum Snap Trajectory Planner and Sampler.
4. Mission commands.
```bash
cd ~/gestelt_ws/src/gestelt/gestelt_bringup/scripts
# Run the script, the script sources all the relevant workspaces so you don't have to worry about sourcing. 
./sitl_drone_bringup.sh

# To kill everything, use the following command
killall -9 gazebo; killall -9 gzserver; killall -9 gzclient; killall -9 rosmaster; tmux kill-server;

# IF you want to add a shortcut to kill the simulation you can add the following to ~/.bashrc
alias killbill="killall -9 gazebo; killall -9 gzserver; killall -9 gzclient; killall -9 rosmaster; tmux kill-server;
```
5. If you want to change the planning setpoints:
- The mission source code is in [mission.py](gestelt_bringup/src/mission.py)
    - Here, the quadrotor is commanded to take off, enter mission mode and are given goal points.
- The trajectory planner source code is in [example_planner.cc](trajectory_planner/src/example_planner.cc)
    - Here, given a goal point, a minimum snap trajectory is planned
- The trajectory sampler source code is in [trajectory_sampler.cpp](trajectory_planner/src/trajectory_sampler.cpp)
    - Here, given a minimum snap trajectory, the points are sampled and sent to the Trajectory server.
- The trajectory execution source code is in [traj_server.cpp](trajectory_server/src/traj_server.cpp)
    - Here, each individual setpoint is converted to PVA commands and sent to the quadrotor.
    - The function in charge of converting the minimum snap point to PVA point is `void TrajServer::multiDOFJointTrajectoryCb(const trajectory_msgs::MultiDOFJointTrajectory::ConstPtr &msg)`
- Refer to the architecture above for more information on how they are connected.

## 2. Run a fake physics-less drone simulation
The second one is a fake drone with no physics and be used to test the architecture or algorithm. It runs the following:
1. Fake drone simulation.
2. Trajectory Server.
3. Minimum Snap Trajectory Planner and Sampler.
4. Mission commands.





# Acknowledgements
1. [EGO-Planner-V2 repo](https://github.com/ZJU-FAST-Lab/EGO-Planner-v2)
2. [ETHZ-ASL/mav_trajectory_generation](https://github.com/ethz-asl/mav_trajectory_generation)
