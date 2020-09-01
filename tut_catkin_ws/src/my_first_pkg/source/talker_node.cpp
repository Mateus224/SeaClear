//#include "include/talker_node.h"
#include <ros/ros.h>
#include <std_msgs/String.h>


int main(int argc, char* argv[])
{
  ros::init(argc, argv, "talker_node");
  ros::NodeHandle node_handle;

  ros::Rate loop_rate(30);
  ros::Publisher pub;
  pub = node_handle.advertise<std_msgs::String>("cahtter",1);

  while(ros::ok())
  {
    std_msgs::String msg;
    msg.data = "Hello World";
    pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
