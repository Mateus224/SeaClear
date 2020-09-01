cmake_minimum_required(VERSION 3.0.2)
project(my_first_pkg)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES my_first_pkg
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(talker_node source/talker_node.cpp)
target_link_libraries(talker_node ${catkin_LIBRARIES})


add_executable(listener_node source/listener_node.cpp)
target_link_libraries(listener_node ${catkin_LIBRARIES})
