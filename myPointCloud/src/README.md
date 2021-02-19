# To start:

```console
roscore
```
```console
rosrun tf static_transform_publisher 0 0 0 0 0 0 map pointcloud 50
```
```console
rosrun gis_to_pcl preprocess.py 
```

```console
rosrun rviz rviz 
```

