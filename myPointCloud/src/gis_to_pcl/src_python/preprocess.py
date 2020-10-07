#!/usr/bin/env python3
import csv
import rospy
import math
import sys

from sensor_msgs.msg import PointCloud2
import std_msgs.msg
import sensor_msgs.point_cloud2 as pcl2
import numpy as np

class Publisher:
    def __init__(self):
        self.x = None
        self.y = None
        self.z = None

    def stream(self):
        # "Store" message received.
        pass


    def dataset(array):
        rospy.init_node('reader', anonymous=True)
        pub = rospy.Publisher('/points', PointCloud2, queue_size=1)
        #giving some time for the publisher to register
        rospy.sleep(0.5)
        header = std_msgs.msg.Header()
        header.stamp = rospy.Time.now()
        header.frame_id = "pointcloud"
        array_= []
        for point in range(array.shape[0]):
        #array_.append([1,1,1])
            array_.append([array[point][0]-886810,array[point][1]-6254020,array[point][2]+4])
        scaled_polygon_pcl = pcl2.create_cloud_xyz32(header, array_)
        rate = rospy.Rate(0.1) # 1hz
        print(array.shape[0])

        while not rospy.is_shutdown():
            rospy.loginfo("sending")
            pub.publish(scaled_polygon_pcl)
            rate.sleep()




class PrepareData:
    def readData(self):
        with open('/home/mateus/seaclear/seaclearCode/myPointCloud/src/gis_to_pcl/src_python/boat_estaque.xyz') as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=' ')
            next(csv_reader, None)
            data = [data for data in csv_reader]
            data_array = np.asarray(data, dtype = np.float64)
            data_array = np.delete(data_array,4,axis=1)
            data_array = np.delete(data_array,3,axis=1)

            print(data_array.shape)
        return data_array





if __name__ == '__main__':
    #rospy.init_node('prozessor')
    data = PrepareData()
    server = Publisher()
    try:
        data = data.readData()
        Publisher.dataset(data)
    except rospy.ROSInterruptException:
        pass




    rospy.spin()
