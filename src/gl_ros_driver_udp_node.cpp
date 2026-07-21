#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>

#include "gl_driver.h"


int main(int argc, char** argv)
{
    // ros init
    rclcpp::init(argc, argv);
    auto node = std::make_shared<rclcpp::Node>("gl_ros_driver_udp_node");

    std::string gl_ip = node->declare_parameter<std::string>("gl_ip", "10.110.1.2");
    int gl_port = node->declare_parameter<int>("gl_port", 2000);
    int pc_port = node->declare_parameter<int>("pc_port", 3000);
    std::string frame_id = node->declare_parameter<std::string>("frame_id", "laser");
    std::string pub_topicname_lidar = node->declare_parameter<std::string>("pub_topicname_lidar", "scan");
    double angle_offset = node->declare_parameter<double>("angle_offset", 0.0);

    // reliable QoS so both reliable and best-effort subscribers can connect
    auto data_pub = node->create_publisher<sensor_msgs::msg::LaserScan>(
        pub_topicname_lidar, rclcpp::QoS(rclcpp::KeepLast(10)));

    // GL Init
    SOSLAB::GL gl(gl_ip, gl_port, pc_port);
    RCLCPP_INFO(node->get_logger(), "Serial Num : %s", gl.GetSerialNum().c_str());
    gl.SetFrameDataEnable(true);

    // loop
    rclcpp::Rate loop_rate(80);
    while(rclcpp::ok())
    {
        sensor_msgs::msg::LaserScan scan_msg;

        SOSLAB::GL::framedata_t frame_data;
        gl.ReadFrameData(frame_data);
        int num_data = frame_data.distance.size();
        if(num_data > 0)
        {
            scan_msg.header.stamp = node->now();
            scan_msg.header.frame_id = frame_id;
            scan_msg.angle_min = frame_data.angle[0] + angle_offset*3.141592/180.0;
            scan_msg.angle_max = frame_data.angle[num_data-1] + angle_offset*3.141592/180.0;
            scan_msg.angle_increment = (scan_msg.angle_max - scan_msg.angle_min) / (double)(num_data-1);
            scan_msg.range_min = 0.001;
            scan_msg.range_max = 30.0;
            scan_msg.ranges.resize(num_data);
            for(int i=0; i<num_data; i++)
            {
                scan_msg.ranges[i] = frame_data.distance[i];
            }

            data_pub->publish(scan_msg);
        }

        rclcpp::spin_some(node);
        loop_rate.sleep();
    }

    gl.SetFrameDataEnable(false);
    rclcpp::shutdown();

    return 0;
}
