std_msgs/Header header

# Goal waypoints
geometry_msgs/Pose[] waypoints
geometry_msgs/Twist[] velocities
geometry_msgs/Accel[] accelerations

std_msgs/Bool[] velocities_mask  # 0 means use the value, 1 means ignore the value
std_msgs/Bool[] accelerations_mask # 0 means use the value, 1 means ignore the value