################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 3.0.2)
project(omo_r1_bringup)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  sensor_msgs
  nav_msgs
  geometry_msgs
  tf
  #usb_cam
  omo_r1_description
  message_generation
  std_msgs
)

add_service_files(
  FILES
  ResetOdom.srv
  navigation_check.srv
  yolo_check.srv
  qt_check.srv
)


################################################################################
# Setup for python modules and scripts
################################################################################
catkin_python_setup()

################################################################################
# Declare ROS messages, services and actions
################################################################################

################################################################################
# Declare ROS dynamic reconfigure parameters
################################################################################

################################################################################
# Declare catkin specific configuration to be passed to dependent projects
################################################################################
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS rospy roscpp sensor_msgs nav_msgs std_msgs geometry_msgs tf usb_cam omo_r1_description message_runtime
)


################################################################################
# Build
################################################################################

################################################################################
# Install
################################################################################
include_directories(
  ${catkin_INCLUDE_DIRS}
)
# add_library(main_hair
#   src/main_hair.cpp
# )
# add_executable(main_hair_node
#   src/main_hair.cpp
# )
# target_link_libraries(main_hair_node
#   ${catkin_LIBRARIES}
#   main_hair
# )

add_executable(bbangle src/bbangle.cpp)
add_dependencies(bbangle ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(bbangle ${catkin_LIBRARIES})

add_executable(main_hair src/main_hair.cpp)
add_dependencies(main_hair ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(main_hair ${catkin_LIBRARIES})

catkin_install_python(PROGRAMS
  nodes/omo_r1_motor_node.py
  src/hair_goal.py
  src/goal.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

################################################################################
# Test
################################################################################
