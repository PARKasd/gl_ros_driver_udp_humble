# GL-3 (Mechanical scanning 2D LiDAR) — ROS 2 Humble

## Guide
- Installation
```
$ cd ${ROS2 workspace}/src
$ git clone --recurse-submodules https://github.com/PARKasd/gl_ros_driver_udp_humble.git
$ cd ${ROS2 workspace}
$ colcon build --packages-select gl_ros_driver_udp --cmake-args -DCMAKE_BUILD_TYPE=Release
$ source install/setup.bash
```
- Set local IP as `10.110.1.3`
- Run GL-3 publisher node
```
$ ros2 launch gl_ros_driver_udp gl_ros_driver_udp.launch.py
```
- Run GL-3 publisher node with RViz2
```
$ ros2 launch gl_ros_driver_udp view_gl_ros_driver_udp.launch.py
```
- Change setting parameters in `gl_ros_driver_udp/launch/gl_ros_driver_udp.launch.py`

## Parameters
- `gl_ip` (string, default `10.110.1.2`): LiDAR IP address
- `gl_port` (int, default `2000`): LiDAR UDP port
- `pc_port` (int, default `3000`): PC-side UDP port
- `frame_id` (string, default `laser`): frame id of the published scan
- `pub_topicname_lidar` (string, default `scan`): topic name to publish
- `angle_offset` (double, default `0.0`): angle offset in degrees

## Published Topics
- _scan_ (sensor_msgs/msg/LaserScan): it publishes scan topic from the laser (reliable QoS, keep last 10).

## Test environment
- ROS 2 Humble Hawksbill
- Ubuntu 22.04
- x86_64 (PC), aarch64 (Jetson series)

## Application demo
- [GL-3, Demo] 2D LiDAR, Mapping (https://youtu.be/AfsqlU_f-Go)
- [GL-3, Demo] Create 3D Point Cloud with 2D LiDAR (https://youtu.be/_HBWe95GqXM)
- [GL-3, Demo] Create 3D Point Cloud with 2D LiDAR (pulse-width version) (https://youtu.be/q4MeeS9eP4c)
- [GL-3, Demo] Human Tracking Demo of Multiple Mobile Robots (https://youtu.be/ZzEvm8gMPaA)
- [GL-3, Demo] 2D LiDAR Object Detection (https://youtu.be/V29QzU9AcQo)
