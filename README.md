# Laboratory 6: Inverse Kinematics Service

This lab involves utilizing an inverse kinematics service to obtain the manipulator's joint configuration based on a specified end effector goal. Inverse Kinematics refers to the mathematical technique used to derive the joint angles or displacements required to achieve a desired end effector pose. However, this process isn't straightforward due to potential situations where certain poses may be unreachable or where multiple sets of joint angles can reach the same pose.

# Launch
The launch directory contains the ik_service.launch file. This file only launches the ik_service node and outputs the result to the screen.

# src
# ik_service
The ik_service node currently defines a transformation matrix T and generates a series of joint angle solutions, enabling the robot to determine its motion path.

The current setup of the transformation matrix T aligns the vacuum gripper of the robot downward, leveraging the requested positioning data. The service subsequently utilizes the ur_kinematics package by calling num_sol = ur_kinematics::inverse(&T[0][0], (double *)&q_sols[0][0], 0.0); to obtain a series of joint solutions.

To confirm the functionality of the ik_service node, execute rosrun ik_service ik_service &. You should receive a notification indicating that the service has been activated.
```
double T[4][4] = {{0.0, -1.0, 0.0, req.part_pose.position.x}, \
                        {0.0, 0.0, 1.0, req.part_pose.position.y}, \
                        {-1.0, 0.0, 0.0, req.part_pose.position.z}, \
                        {0.0, 0.0, 0.0, 0.0}};
```

# ik_client
The ik_client node initializes the x-position of the request to 0.5 and proceeds to invoke the service. At present, it only retrieves a single set of joint solutions. To validate the functionality of the ik_client node, execute rosrun ik_service ik_client &. You should observe an output containing six joint angles.

# srv

The service defines a request parameter, geometry_msgs/Pose, and produces a response comprising two elements: num_sol of type int8 and joint_solutions of type int8 and ik_service/JointSolutions.

num_sol signifies the count of obtained joint angle solutions, while joint_solutions can store a maximum of eight sets of joint angles.
```
# Pose Service

# Request Part Pose
geometry_msgs/Pose part_pose

---
# Number of solutions returned
int8 num_sols

# The joint angles to reach solution
ik_service/JointSolutions[8] joint_solutions
```

# msg

The message comprises a vector with a width of six, containing six floating-point numbers. These six numbers represent a complete set of joint angles.

```
# Message for Joint Solutions

# A vector of joint angles
float64[6] joint_angles
```

# Launch
We can launch the node using this command. Upon inspecting the output from test_inverse.cpp, ik_service.cpp, and ik_client.cpp, it's evident that both solutions align when derived from identical initial conditions.

```
roslaunch ik_service ik_service.launch
```
