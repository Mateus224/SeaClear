#include <ros/ros.h>
#include <ros/console.h>
#include <pcl_ros/point_cloud.h>
#include <pcl/point_types.h>
#include <boost/foreach.hpp>
#include <pcl_conversions/pcl_conversions.h>
#include <iostream>
#include "ros/ros.h"
#include "sensor_msgs/PointCloud2.h"
#include <octomap/octomap.h>
#include <octomap/OcTree.h>
#include <pcl/io/pcd_io.h>
#include <pcl/compression/octree_pointcloud_compression.h>
#include <pcl/point_types.h>
#include <pcl/conversions.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/filters/filter.h>
#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>
#include <deque>



typedef pcl::PointCloud<pcl::PointXYZ> PointCloud;
ros::NodeHandle nh;
const float res = 0.1;
//pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA>* PointCloudEncoder;

/*

void
cloud_cb (const sensor_msgs::PointCloud2ConstPtr& input)
{
  // Create a container for the data.
  std::string output;
  std_msgs::String outputString;

  //convert to pointxyzrgba type
  pcl::PCLPointCloud2 pcl_pc2;
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr temp_cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);//convert to pointer to satisfy function requirement
  pcl_conversions::toPCL(*input, pcl_pc2);
  pcl::fromPCLPointCloud2(pcl_pc2, *temp_cloud);

  // stringstream to store compressed point cloud
  std::stringstream compressedData;

  // compress point cloud
  PointCloudEncoder->encodePointCloud (temp_cloud, compressedData);


  compressedData.seekg(0,ios::end);
  int size = compressedData.tellg();
  compressedData.seekg(0,ios::beg);
  std::cout<<size<<std::endl;


  char * buffer = new char[size];

  compressedData.read(buffer,size);

  uint8_t * tempor = reinterpret_cast<uint8_t *>(buffer);
  std::vector<unsigned char> v(tempor, tempor + size);
  std::cout<<"Size: "<<v.size()<<std::endl;


  my_pcl_tutorial::Blob blobmsg;
  blobmsg.data=v;
  blobmsg.size=size;

  sensor_msgs::PointCloud2 pointcloudheader;
  pointcloudheader = *input;
  blobmsg.header = pointcloudheader.header;


//////////////////////////////////////////////
/*
  //converting back, used for testing
  std::stringstream test25;

  std::vector<unsigned char> v2(blobmsg.data);
std::cout<<"Size2: "<<v2.size()<<std::endl;
std::cout<<"Size of message: "<<blobmsg.size<<std::endl;

  std::copy(v2.begin(), v2.end(), std::ostream_iterator<unsigned char>(test25));
std::cout<<"debug"<<std::endl;

  test25.seekg(0,ios::end);
  int size2 = test25.tellg();
  test25.seekg(0,ios::beg);
  std::cout<<size2<<std::endl;

  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloudOut (new pcl::PointCloud<pcl::PointXYZRGBA> ());
  //decompress
  PointCloudDecoder->decodePointCloud (test25, cloudOut);




  sensor_msgs::PointCloud2 outputmessage;
  std::cout<<"Convert to right format now .."<<std::endl;
  //save header info since toROSmsg throws away this information
  //convert to pointcloud2
  pcl::toROSMsg(*cloudOut, outputmessage);
  outputmessage.header = blobmsg.header;
  std::cout<<outputmessage.header<<std::endl;

/**/

/*

/////////////////////////////


  // Publish the data.
  pub.publish (blobmsg);
}

int
main (int argc, char** argv)
{
  // Initialize ROS
  ros::init (argc, argv, "my_pcl_tutorial");
  ros::NodeHandle nh;


  //\\
  //setup compression algorithm


  bool showStatistics = false;

  pcl::io::compression_Profiles_e compressionProfile = pcl::io::LOW_RES_ONLINE_COMPRESSION_WITHOUT_COLOR;

  // instantiate point cloud compression for encoding and decoding
  PointCloudEncoder = new pcl::io::OctreePointCloudCompression<pcl::PointXYZRGBA> (compressionProfile, showStatistics);
  //\\



  // Create a ROS subscriber for the input point cloud
  ros::Subscriber sub = nh.subscribe ("velodyne_points", 1, cloud_cb);

  // Create a ROS publisher for the output point cloud
  pub = nh.advertise<my_pcl_tutorial::Blob> ("velodyne_points/compressed", 1);

  // Spin
  ros::spin ();

  delete(PointCloudEncoder);
}
*/


void pointsCallback(const sensor_msgs::PointCloud2ConstPtr& msg)
{
//********* Retirive and process raw pointcloud************
        std::cout<<"Recieved cloud"<<msg<<std::endl;
        std::cout<<"Create Octomap"<<std::endl;
        float a=01;
        octomap::OcTree tree(a);
        std::cout<<"Load points "<<std::endl;
        pcl::PCLPointCloud2 cloud;

        pcl::PointCloud<pcl::PointXYZRGBA>::Ptr temp_cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);//convert to pointer to satisfy function requirement
        pcl_conversions::toPCL(*msg, cloud);
        pcl::fromPCLPointCloud2(cloud, *temp_cloud);



        std::cout<<"Filter point clouds for NAN"<<std::endl;
        std::vector<int> nan_indices;
        //pcl::removeNaNFromPointCloud(temp_cloud,temp_cloud,nan_indices);
        octomap::Pointcloud oct_pc;
        octomap::point3d origin(0.0f,0.0f,0.0f);
        std::cout<<"Adding point cloud to octomap"<<std::endl;
        //octomap::point3d origin(0.0f,0.0f,0.0f);
        for(int i = 0;i<temp_cloud.points.size();i++){
                oct_pc.push_back((float) pcl_pc.points[i].x,(float) pcl_pc.points[i].y,(float) pcl_pc.points[i].z);
}
        tree.insertPointCloud(oct_pc,origin,-1,false,false);
        /*
        */

        /*
        //******************Traverse the tree ********************
        for(octomap::OcTree::tree_iterator it =tree.begin_tree(), end = tree.end_tree();it!= end;it++){
                 //manipulate node, e.g.:
                std::cout << "_____________________________________"<<std::endl;
                std::cout << "Node center: " << it.getCoordinate() << std::endl;
                std::cout << "Node size: " << it.getSize() << std::endl;
                std::cout << "Node depth: "<<it.getDepth() << std::endl;
                std::cout << "Is Leaf : "<< it.isLeaf()<< std::endl;
                std::cout << "_____________________________________"<<std::endl;
                }
        //**********************************************************
        */
        std::cout<<"finished"<<std::endl;
        std::cout<<std::endl;

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

  ros::Subscriber sub = nh.subscribe<sensor_msgs::PointCloud2>("points", 1000, pointsCallback);
  ros::spin();
}
