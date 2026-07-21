cmake_minimum_required(VERSION 3.8)
project(gl_ros_driver_udp)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Threads REQUIRED)

include_directories(
  include
  include/gl_driver_libraries
)

###########
## Build ##
###########

file(GLOB serial_src "include/gl_driver_libraries/serial/*.cc")
add_library(serial STATIC ${serial_src})
target_link_libraries(serial Threads::Threads)
set_target_properties(serial PROPERTIES POSITION_INDEPENDENT_CODE ON)

file(GLOB udp_src "include/gl_driver_libraries/udp/*.cpp")
add_library(udp STATIC ${udp_src})
set_target_properties(udp PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_library(gl_driver STATIC include/gl_driver_libraries/gl_driver.cpp)
target_link_libraries(gl_driver serial udp Threads::Threads)
set_target_properties(gl_driver PROPERTIES POSITION_INDEPENDENT_CODE ON)

add_executable(${PROJECT_NAME}_node
  src/${PROJECT_NAME}_node.cpp
)
ament_target_dependencies(${PROJECT_NAME}_node
  rclcpp
  sensor_msgs
)
target_link_libraries(${PROJECT_NAME}_node
  gl_driver
  serial
  udp
)

#############
## Install ##
#############

install(TARGETS ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch rviz
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
