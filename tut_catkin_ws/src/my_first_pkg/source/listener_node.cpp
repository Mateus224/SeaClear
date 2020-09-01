#include <ros/ros.h>
#include <std_msgs/String.h>

void subscriber_callback(const std_msgs::String::ConstPtr& receivedMsg)
{
  ROS_INFO("I received the following: %s", receivedMsg->data.c_str());
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener_node");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("cahtter",1,subscriber_callback);
  ros::spin();

}
