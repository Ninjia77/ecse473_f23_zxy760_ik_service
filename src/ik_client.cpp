#include "ros/ros.h"
#include "ik_service/PoseIK.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ik_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ik_service::PoseIK>("pose_ik");
  ik_service::PoseIK req_poseik;
  geometry_msgs::Pose part_pose;
 

  part_pose.position.x = -0.6;
  part_pose.position.y = -0.5372;
  part_pose.position.z = -0.18;
  req_poseik.request.part_pose = part_pose;

  if (client.call(req_poseik))
  {
    ROS_INFO("solution number%i", req_poseik.response.num_sols);
  }
  else
  {
    ROS_ERROR("Failed to call service pose_ik");
    return 1;
  }

  return 0;
}