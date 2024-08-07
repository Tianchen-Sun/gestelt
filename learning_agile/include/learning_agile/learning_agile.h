#ifndef _LEARNING_AGILE_H_
#define _LEARNING_AGILE_H_

#include <numeric>
#include <deque>

#include <Eigen/Geometry> 
#include <vector>
#include <ros/ros.h>

#include <geometry_msgs/PoseArray.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/TwistStamped.h>


#include <mavros_msgs/AttitudeTarget.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/SetMode.h>


#include <std_msgs/Empty.h>
#include <std_msgs/Int8.h>
#include <std_msgs/Float64.h>
#include <std_msgs/String.h>
#include <chrono>

#include <gestelt_msgs/Goals.h>

// acados
#include "acados/utils/math.h"
#include "acados_c/ocp_nlp_interface.h"

#include "acados_sim_solver_ACADOS_model.h"
#include "acados_solver_ACADOS_model.h"
#include <cmath>
#endif 

typedef ACADOS_model_solver_capsule* ACADOS_model_solver_capsule_ptr;
typedef ocp_nlp_config* nlp_config_ptr;
typedef ocp_nlp_dims* nlp_dims_ptr;
typedef ocp_nlp_in* nlp_in_ptr;
typedef ocp_nlp_out* nlp_out_ptr;
class LearningAgile{
    public:
        void init(ros::NodeHandle& nh);
        
        void mission_start_cb(const gestelt_msgs::GoalsPtr &msg);
        void gate_state_estimation_cb(const ros::TimerEvent &e);
        void setpoint_timer_cb(const ros::TimerEvent &e);
        void drone_state_pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
        void drone_state_twist_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);


        //------------------acados solver-------------------
        void solver_request();

        double* getcontrolOpt() { return control_opt_; };
        void Update();

        //------------------misc-------------------
        void pred_traj_vis();

        typedef std::shared_ptr<LearningAgile> Ptr;
        
        // solver state 
        bool NO_SOLUTION_FLAG_=false;
        bool MISSION_LOADED_FLAG_=false;
    
    
    private:
    ros::Subscriber drone_pose_sub_;
    ros::Subscriber drone_twist_sub_;
    ros::Subscriber waypoint_sub_;

    ros::Publisher next_attitude_setpoint_pub_;
    ros::Publisher gate_centroid_pub_;
    ros::Publisher traverse_time_pub_;

    ros::Publisher mpc_runtime_pub_;
    ros::Publisher current_pred_traj_pub_;

    ros::Timer soft_RT_mpc_timer_;

    //environment setting
    std::string origin_frame_="world";

    // desired traverse state
    Eigen::Vector3d des_trav_point_={0,0,0};
    Eigen::Vector4d des_trav_quat_={1,0,0,0};

    // time setting
    double t_tra_abs_=10;
    std::chrono::high_resolution_clock::time_point mission_start_time_;
    std::chrono::high_resolution_clock::time_point last_request_time_;
    double pub_freq=100;
    double no_solution_flag_t_thresh_=0.02;
    // start point
    Eigen::Vector3d start_point_={0,0,0};
    
    // desired goal state
    Eigen::VectorXd des_goal_state_=Eigen::VectorXd::Zero(10);
    Eigen::Vector3d des_goal_point_={0,0,0};
    Eigen::Vector4d des_goal_quat_={1,0,0,0};
    Eigen::Vector3d des_goal_vel_={0,0,0};

    //current drone state
    Eigen::VectorXd drone_state_=Eigen::VectorXd::Zero(10);
    Eigen::Vector3d drone_pos_= {0,0,0};
    Eigen::Vector3d drone_vel_= {0,0,0};
    Eigen::Vector4d drone_quat_= {1,0,0,0};
    Eigen::Vector3d drone_ang_vel_= {0,0,0};

    //MPC parameters
    double max_tra_w_=0;
    Eigen::Vector4d current_input_={0,0,0,0};
    Eigen::Vector4d last_input_={0,0,0,0};
    double single_motor_max_thrust_=2.1334185;

    //MPC output
    std::vector<std::vector<double>> state_traj_opt_;
    double* state_i_opt_;
    double control_opt_[4] = {0,0,0,0};
  
    
    // acados param
    int status; // acados operation state
    
    //------------------- acados solver -------------------
    int n_nodes_;
    int n_x_;
    int n_u_;
    int dt_=0.1;
    
    ACADOS_model_solver_capsule_ptr acados_ocp_capsule;
    nlp_config_ptr nlp_config;
    nlp_dims_ptr nlp_dims;
    nlp_in_ptr nlp_in;
    nlp_out_ptr nlp_out;


    //threading
    std::mutex cmd_mutex_; 

    // misc
    bool PRED_TRAJ_VIS_FLAG_=false;

};