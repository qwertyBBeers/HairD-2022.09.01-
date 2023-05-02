

cmake_minimum_required(VERSION 3.5)
project(captin_qt_pkg)

## Compile as C++11, supported in ROS Noetic and newer
add_compile_options(-std=c++11)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_service_files(
  FILES
  qt_check.srv
)
generate_messages(
  DEPENDENCIES
  std_msgs
)

## Find Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)




## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS roscpp std_msgs message_runtime
)

## Build the Qt5 node
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Gui_INCLUDE_DIRS}
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  ${CMAKE_CURRENT_SOURCE_DIR}/src/images
  ${CMAKE_CURRENT_SOURCE_DIR}/captin_qt_pkg  # captain_qt_pkg 디렉토리 추가
)

add_executable(captin_qt_node
  src/main.cpp
  src/captain_mainwindow.h
  src/captain_mainwindow.cpp
  src/chair1_dialog.h
  src/chair1_dialog.cpp
  src/chair2_dialog.h
  src/chair2_dialog.cpp
  src/chair3_dialog.h
  src/chair3_dialog.cpp
  src/resources.qrc
)

add_dependencies(captin_qt_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})


target_link_libraries(captin_qt_node
  ${catkin_LIBRARIES}
  Qt5::Widgets
  Qt5::Gui
  Qt5::Core
)


## Install the Qt5 node
install(TARGETS captin_qt_node
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
