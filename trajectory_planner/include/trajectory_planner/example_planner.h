#ifndef TRAJECTORY_PLANNER_H
#define TRAJECTORY_PLANNER_H

#include <iostream>
#include <ros/ros.h>
#include <Eigen/Dense>
#include <nav_msgs/Odometry.h>
#include <eigen_conversions/eigen_msg.h>
#include <mav_trajectory_generation/polynomial_optimization_nonlinear.h>

#include <mav_trajectory_generation/polynomial_optimization_linear.h>

#include <mav_trajectory_generation_ros/ros_visualization.h>
#include <mav_trajectory_generation_ros/ros_conversions.h>

#include <gestelt_msgs/Goals.h>

class ExamplePlanner {
 public:
  ExamplePlanner(ros::NodeHandle& nh);

  void uavOdomCallback(const nav_msgs::Odometry::ConstPtr& pose);

  void waypointsCB(const gestelt_msgs::GoalsPtr &msg);

  void setMaxSpeed(double max_v);

  // Plans a trajectory to take off from the current position and
  // fly to the given altitude (while maintaining x,y, and yaw).
  bool planTrajectory(const std::vector<Eigen::Vector3d>& wp_pos,
                      const std::vector<Eigen::Vector3d>& wp_vel,
                      const std::vector<Eigen::Vector3d>& wp_acc,
                      const gestelt_msgs::GoalsPtr &msg,
                      mav_trajectory_generation::Trajectory* trajectory);
                      

  // Plans a trajectory to take off from the current position and
  // fly to the given altitude (while maintaining x,y, and yaw).
  bool planTrajectory(const Eigen::VectorXd& goal_pos,
                      const Eigen::VectorXd& goal_vel,
                      mav_trajectory_generation::Trajectory* trajectory);

  bool planTrajectory(const Eigen::VectorXd& goal_pos,
                      const Eigen::VectorXd& goal_vel,
                      const Eigen::VectorXd& start_pos,
                      const Eigen::VectorXd& start_vel,
                      double v_max, double a_max,
                      mav_trajectory_generation::Trajectory* trajectory);
                      
  bool publishTrajectory(const mav_trajectory_generation::Trajectory& trajectory);

 private:
  ros::Publisher pub_markers_;
  ros::Publisher pub_trajectory_;
  ros::Subscriber sub_odom_;
  ros::Subscriber goal_waypoints_sub_;
  
  ros::NodeHandle& nh_;
  Eigen::Affine3d current_pose_;
  Eigen::Vector3d current_velocity_;
  Eigen::Vector3d current_angular_velocity_;
  double max_v_; // m/s
  double max_a_; // m/s^2
  double max_ang_v_;
  double max_ang_a_;

  std::vector<Eigen::Vector3d> goal_waypoints_;
  std::vector<Eigen::Vector3d> goal_waypoints_vel_;
  std::vector<Eigen::Vector3d> goal_waypoints_acc_;
  std::string trajectory_frame_id_; //frame id of planned trajectory
};

#endif // TRAJECTORY_PLANNER_H
