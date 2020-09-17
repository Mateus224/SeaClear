#include <ros/ros.h>
#include <ros/console.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include <std_msgs/Float64MultiArray.h>
#include <std_msgs/String.h>


#include <stdio.h>
#include <stdlib.h>
#include <vector>



typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
ros::NodeHandle nh;

void pointsCallback(const std_msgs::Float64MultiArray::ConstPtr& array)
{
    ROS_DEBUG("Array is:%f",array[0]);
/*
    int Arr[20000];
    int i = 0;
    // print all the remaining numbers
    for(std::vector<int>::const_iterator it = array->data.begin(); it != array->data.end(); ++it)
    {
            Arr[i] = *it;
            printf("%d, ", Arr[i]);
            i++;
    }
    ros::Publisher pub = nh.advertise<PointCloud> ("points2", 1);
    //ROS_INFO(test);

    PointCloud::Ptr msg (new PointCloud);
    msg->header.frame_id = "/some_tf_frame";
    msg->height = 1;
    msg->width = 10;
    for(float i=0; i<10; i++){
      msg->points.push_back (pcl::PointXYZ(i, 2.0, 3.0));
    }
    ros::Rate loop_rate(4);
    while (nh.ok())
    {
      pcl_conversions::toPCL(ros::Time::now(), msg->header.stamp);
      pub.publish (msg);
      ros::spinOnce ();
      loop_rate.sleep ();
    }
    */

}

int main(int argc, char** argv)
{
  ros::init (argc, argv, "pub_pcl");

  ros::Subscriber sub = nh.subscribe("points", 1000, pointsCallback);
  ros::spin();
}
