from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    # execute GL-3 for LaserScan publish
    gl_node = Node(
        package='gl_ros_driver_udp',
        executable='gl_ros_driver_udp_node',
        name='gl_ros_driver_udp_node',
        output='screen',
        parameters=[{
            'gl_ip': '10.110.1.2',
            'gl_port': 2000,
            'pc_port': 3000,
            'frame_id': 'laser',
            'pub_topicname_lidar': 'scan',
            'angle_offset': 0.0,
        }]
    )

    return LaunchDescription([gl_node])
