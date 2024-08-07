#!/usr/bin/env python3

## this file is for traversing moving narrow window
import sys
import os
# acquire the current directory
current_dir = os.path.dirname(os.path.abspath(__file__))

# build the path to the subdirectory
subdirectory_path = os.path.join(current_dir, 'Learning_Agile')

# add to sys.path
sys.path.append("../")
sys.path.append(subdirectory_path)


from typing import Any
from quad_model import *
from quad_policy import *
from quad_nn import *
from quad_moving import *

# ros
import numpy as np
import rospy
# from gestelt_msgs.msg import CommanderState, Goals, CommanderCommand
from geometry_msgs.msg import Pose, Accel,PoseArray,AccelStamped, TwistStamped, PoseStamped,Quaternion,Vector3
from mavros_msgs.msg import PositionTarget, AttitudeTarget
from std_msgs.msg import Int8, Bool,Float32
import math
import time
import tf


# load the DNN2 model
abs_dir=os.path.dirname(os.path.abspath(__file__))
print(abs_dir)
FILE = os.path.join(abs_dir, 'nn3_1.pth')
# FILE ="nn3_1.pth"



class MovingGate():
    def __init__(self, env_inputs):
        # gate status
        self.env_inputs=env_inputs

        # initialize the gate1, with the initial gate position
        self.gate_point0 = np.array([[-self.env_inputs[7]/2,-0,1],[self.env_inputs[7]/2,-0,1],[self.env_inputs[7]/2,-0,-1],[-self.env_inputs[7]/2,-0,-1]])
        self.gate1 = gate(self.gate_point0)
        self.gate_init_p = self.env_inputs[8]
        
        # define the properties of the gate1
        self.gate1.rotate_y(self.env_inputs[8])

        # the four corners of the gate1
        self.gate_point = self.gate1.gate_point

        # update the gate1
        self.gate1 = gate(self.gate_point)
        
    
    def let_gate_move(self):
    
         ## define the kinematics of the narrow window
        self.v =np.array([0,0.0,0.0])
        self.w = 0 #pi/2
        # self.gate_move, self.V = self.gate1.move(v = self.v ,w = self.w,dt=0.002)

        self.gate_move=np.zeros([1,4,3])
        self.V=np.zeros([1,3])
        # return self.w
    
class LearningAgileAgent():
    def __init__(self) -> None:

        # inputs [start, end]
        self.env_inputs = nn_sample()
        # self.env_inputs[8]=pi/2 # gate pitch angle
        # drone state
        self.state = np.zeros(10)

        # moving gate
        self.moving_gate = MovingGate(self.env_inputs)
        self.gate_point = self.moving_gate.gate_point

        # load trained DNN2 model
        self.model = torch.load(FILE)
    

        ##-------------------- planning variables --------------------------##
        # MPC prediction step, and prediction horizon
        self.dt=0.1
        self.horizon=10 #(T/dt)

        self.u = np.array([2,0.0,0.0,0.0])
        self.tm = [0,0,0,0]
        self.state_n = []
        self.control_n = [self.u.tolist()]
        self.control_tm = [self.tm]
        
        self.hl_para = [0,0,0,0,0,0,0]
        self.hl_variable = [self.hl_para]
        
        ##---------------------gate initialization ------------------------##
        self.moving_gate.let_gate_move()
        self.gate_move = self.moving_gate.gate_move
        self.gate_n = gate(self.gate_move[0])


        ##-------------- initial guess of the traversal time---------------##
        self.t_guess = magni(self.gate_n.centroid-self.state[0:3])/3
        
        self.Ttra    = []
        self.T       = []
        self.Time    = []
        self.Pitch   = []
        self.i       = 0
        self.solving_time = []
        self.tra_weight_list = []   
        # trajectory pos_vel_att_cmd
        self.pos_vel_att_cmd=np.zeros(10)
        self.pos_vel_att_cmd_n = [self.pos_vel_att_cmd]

        # FIXME Temporally set the traversal time here, for both python and gazebo simulation
        
    
    def receive_mission_states(self,
                                start,
                                end,
                                gate_center=np.array([0,0,1.5]),
                                gate_ori_euler=np.array([0,0,0]),
                                t_tra_abs=1,
                                max_tra_w=0,
                                ):
        """
        receive the start and end point defined in the mission file

        """
        
        self.env_inputs[0:3]=start
        self.env_inputs[3:6]=end
        self.start_point = start
        self.final_point = end

        self.gate_center = gate_center
        self.gate_ori_euler = gate_ori_euler
        self.t_tra_abs =t_tra_abs
        self.max_tra_w=max_tra_w

    def problem_definition(self,drone_init_quat=None,gazebo_sim=False,dyn_step=0.002):
        """
        initial traversal problem

        """
        ini_q=toQuaternion(self.env_inputs[6],[0,0,1]) # drone_init_yaw
        if drone_init_quat is not None:
            ini_q=drone_init_quat.tolist()
          

        self.quad1 = run_quad(goal_pos=self.env_inputs[3:6],
                              ini_r=self.env_inputs[0:3].tolist(),
                              ini_q=ini_q,
                              horizon=self.horizon,
                              gazebo_sim=gazebo_sim,
                              dt=self.dt)
        

        self.quad1.init_obstacle(self.gate_point.reshape(12))

        self.dyn_step=dyn_step
        self.quad1.uav1.setDyn(self.dyn_step)



        print('start_point=',self.env_inputs[0:3])
        print('final_point=',self.env_inputs[3:6])
        
    
    def gate_state_estimation(self,gazebo_model_state):

        """
        estimate the gate pose, using binary search

        """

        # run in 100 hz
        drone_state=gazebo_model_state

        if self.i <= 500:
    
            self.gate_n = gate(self.gate_move[0])
            # self.state_n = [drone_state]

            # binary search for the traversal time
            # t = solver(self.model,self.state,self.final_point,self.gate_n,self.moving_gate.V[self.i],self.moving_gate.w)
            # t=self.t_tra_abs-self.i*0.01
            # t_tra = t+self.i*0.01
            # gap_pitch = self.moving_gate.gate_init_p + self.moving_gate.w*self.i*0.01
            
            # print('step',self.i,'tranversal time W.R.T current=',t,'gap_pitch=',gap_pitch*180/pi)
            # print('step',self.i,'abs_tranversal time W.R.T mission=',t_tra)
            
            # self.Ttra = np.concatenate((self.Ttra,[self.t_tra_abs]),axis = 0)
            # self.T = np.concatenate((self.T,[t]),axis = 0)
            # self.Time = np.concatenate((self.Time,[self.i*0.01]),axis = 0)
            # self.Pitch = np.concatenate((self.Pitch,[gap_pitch]),axis = 0)
            

            ## obtain the future traversal window state
            # self.gate_n.translate(t*self.moving_gate.V[0])
            # self.gate_n.rotate_y(t*self.moving_gate.w)
             
            # print('rotation matrix I_G=',gate_n.I_G)
               
        self.i += 1
        # return self.t_tra_abs,self.gate_n.centroid

    def solve_problem_gazebo(self,drone_state=None):
        """ 
        gazebo simulation
        
        """
        
        t_comp = time.time()  
        self.state=drone_state

        # FIXME, the drone state sould under the gate frame
        nn_mpc_inputs = np.zeros(18)
        # nn_mpc_inputs[16] = magni(self.gate_n.gate_point[0,:]-self.gate_n.gate_point[1,:]) # gate width
        # nn_mpc_inputs[17] = atan((self.gate_n.gate_point[0,2]-self.gate_n.gate_point[1,2])/(self.gate_n.gate_point[0,0]-self.gate_n.gate_point[1,0])) # compute the actual gate pitch ange in real-time
        nn_mpc_inputs[0:10] = self.state #self.gate_n.transform(self.state)
        nn_mpc_inputs[10:13] = self.final_point#self.gate_n.t_final(self.final_point)

        # NN2 OUTPUT the traversal time and pose
        # out = self.model(nn_mpc_inputs).data.numpy()

        # FIXME, manually set the traversal time and pose
        out=np.zeros(7)
        out[0:3]=self.gate_center

        angle=-0.785# rad 0.707
        rod_ang=np.tan(angle/2)
        out[3:6]=self.gate_ori_euler  
        out[6]=self.t_tra_abs-self.i*0.01
        # end FIXME

        ## solve the mpc problem and get the control command
        cmd_solution,weight_vis,NO_SOLUTION_FLAG = self.quad1.get_input(nn_mpc_inputs[0:10],
                                                        self.u,out[0:3],
                                                        out[3:6],
                                                        out[6],
                                                        max_tra_w=self.max_tra_w) # control input 4-by-1 thrusts to pybullet
                    

        self.u=cmd_solution['control_traj_opt'][0,:]
        current_pred_traj=cmd_solution['state_traj_opt']

        callback_runtime=time.time()-t_comp

        # IF the solving time is too long, stop the mission
        if callback_runtime>0.025:
            print("too long to solve")
            NO_SOLUTION_FLAG=True
        return self.u, callback_runtime,current_pred_traj,NO_SOLUTION_FLAG


    def solve_problem_comparison(self):
        """
        python simulation

        """
        
        self.state = self.quad1.ini_state # state= feedback from pybullet, 13-by-1, 3 position, 3 velocity (world frame), 4 quaternion, 3 angular rate
        self.state_n = [self.state]
        for self.i in range(2500): # 5s, 500 Hz
            # decision variable is updated in 100 hz
            self.gate_n = gate(self.gate_move[0])
           
            # t = solver(self.model,self.state,self.final_point,self.gate_n,self.moving_gate.V[self.i],self.moving_gate.w)
            # t_tra = t+self.i*self.dyn_step

            t=self.t_tra_abs-self.i*self.dyn_step
            gap_pitch = self.moving_gate.gate_init_p + self.moving_gate.w*self.i*self.dyn_step
            
            
            # print('step',self.i,'tranversal time=',t,'gap_pitch=',gap_pitch*180/pi)
            # print('step',i,'abs_tranversal time=',t_tra)
            
            self.Ttra = np.concatenate((self.Ttra,[self.t_tra_abs]),axis = 0)
            self.T = np.concatenate((self.T,[t]),axis = 0)
            self.Time = np.concatenate((self.Time,[self.i*self.dyn_step]),axis = 0)
            self.Pitch = np.concatenate((self.Pitch,[gap_pitch]),axis = 0)
            
            if (self.i%5)==0: # control frequency = 100 hz

                ## obtain the future traversal window state
                self.gate_n.translate(t*self.moving_gate.V[0])
                self.gate_n.rotate_y(t*self.moving_gate.w)
                # print('rotation matrix I_G=',gate_n.I_G)
                
                ## obtain the state in window frame 
                
                # FIXME, the drone state sould under the gate frame
                nn_mpc_inputs = np.zeros(18)
                # nn_mpc_inputs[16] = magni(self.gate_n.gate_point[0,:]-self.gate_n.gate_point[1,:]) # gate width
                # nn_mpc_inputs[17] = atan((self.gate_n.gate_point[0,2]-self.gate_n.gate_point[1,2])/(self.gate_n.gate_point[0,0]-self.gate_n.gate_point[1,0])) # compute the actual gate pitch ange in real-time
                nn_mpc_inputs[0:10] = self.state #self.gate_n.transform(self.state)
                nn_mpc_inputs[10:13] = self.final_point#self.gate_n.t_final(self.final_point)

                # NN2 OUTPUT the traversal time and pose
                # out = self.model(nn_mpc_inputs).data.numpy()

                # FIXME, manually set the traversal time and pose
                out=np.zeros(7)
                out[0:3]=self.gate_center
                out[3:6]=self.gate_ori_euler
                out[6]=self.t_tra_abs-self.i*self.dyn_step
                # end FIXME

                t_comp = time.time()
                
                cmd_solution,weight_vis,NO_SOLUTION_FLAG  = self.quad1.get_input(nn_mpc_inputs[0:10],
                                                    self.u,out[0:3],
                                                    out[3:6],
                                                    out[6],
                                                    max_tra_w=self.max_tra_w) # control input 4-by-1 thrusts to pybullet
                
                print('solving time at main=',time.time()-t_comp)
                self.solving_time.append(time.time()- t_comp)
                self.u=cmd_solution['control_traj_opt'][0,:].tolist()
                self.pos_vel_att_cmd=cmd_solution['state_traj_opt'][0,:]
                self.tra_weight_list.append(weight_vis)
            
            self.state = np.array(self.quad1.uav1.dyn_fn(self.state, self.u)).reshape(10) # Yixiao's simulation environment ('uav1.dyn_fn'), replaced by pybullet
            self.state_n = np.concatenate((self.state_n,[self.state]),axis = 0)
            self.control_n = np.concatenate((self.control_n,[self.u]),axis = 0)
            self.pos_vel_att_cmd_n = np.concatenate((self.pos_vel_att_cmd_n,[self.pos_vel_att_cmd]),axis = 0)
            u_m = self.quad1.uav1.u_m
            u1 = np.reshape(self.u,(4,1))
            tm = np.matmul(u_m,u1)
            tm = np.reshape(tm,4)
            # control_tm = np.concatenate((control_tm,[tm]),axis = 0)
            # self.hl_variable = np.concatenate((self.hl_variable,[out]),axis=0)       
            
        print('MPC finished')   
        np.save('gate_move_traj',self.gate_move)
        np.save('uav_traj',self.state_n)
        np.save('uav_ctrl',self.control_n)
        np.save('abs_tra_time',self.Ttra)
        np.save('tra_time',self.T)
        np.save('Time',self.Time)
        np.save('Pitch',self.Pitch)
        np.save('HL_Variable',self.hl_variable)
        np.save('solving_time',self.solving_time)
        self.quad1.uav1.play_animation(wing_len=1.5,
                                    #    gate_traj1=self.gate_move[::5,:,:],
                                       state_traj=self.state_n[::5,:],
                                       goal_pos=self.final_point.tolist(),
                                       dt=self.dyn_step)

        # self.quad1.uav1.plot_thrust(self.control_n)
        # self.quad1.uav1.plot_angularrate(self.control_n)
        # self.quad1.uav1.plot_position(self.pos_vel_att_cmd_n)
        # self.quad1.uav1.plot_velocity(self.pos_vel_att_cmd_n)
        plt.plot(self.solving_time)
        plt.title('mpc solving time at the main loop')
        plt.show()

        # plt.plot(self.tra_weight_list)
        # plt.title('traverse weight')
        # plt.show()
        # self.quad1.uav1.plot_T(control_tm)
        # self.quad1.uav1.plot_M(control_tm)
    
        
def main():
    ## --------------for single planning part test-------------------------------##.
    # create the learning agile agent
    learing_agile_agent=LearningAgileAgent()
    
    # receive the start and end point, and the initial gate point, from ROS side
    # rewrite the inputs
    # learing_agile_agent.receive_mission_states(start=np.array([0,1.8,1.4]),
    #                                             end=np.array([0,-1.8,1.4]),
    #                                             gate_center=np.array([1.2,0,1.4]),
    #                                             gate_ori_euler=np.array([0,-0.707/2,0]),
    #                                             t_tra_abs=1,
    #                                             max_tra_w=60)

    #------------------------------python hover test--------------------------------------#
    learing_agile_agent.receive_mission_states(start=np.array([0,1.8,1.4]),
                                                end=np.array([3,1.8,1.4]),
                                                gate_center=np.array([1,3.8,1.4]),
                                                gate_ori_euler=np.array([0,0,0]),
                                                t_tra_abs=1,
                                                max_tra_w=70)

    # #------------------------------------------------------------------------------#
    # problem definition
    learing_agile_agent.problem_definition(dyn_step=0.002)

    # solve the problem
    learing_agile_agent.solve_problem_comparison()

if __name__ == '__main__':
    main()
   