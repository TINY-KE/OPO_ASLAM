#include <ros/ros.h>
#include <gazebo_msgs/ModelStates.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_broadcaster.h>

#include <tf/transform_broadcaster.h>

#include <gazebo_msgs/SetModelState.h>
#include <gazebo_msgs/GetModelState.h>
#include <gazebo_msgs/GetLinkState.h>
#include <gazebo_msgs/GetWorldProperties.h>
#include <gazebo_msgs/GetModelProperties.h>

std::string robot_name = "mrobot";  // 机器人模型名称


geometry_msgs::Pose getPose(ros::NodeHandle& n, std::string name, bool output = false)
{
    ros::ServiceClient get_model_state_client = n.serviceClient<gazebo_msgs::GetModelState>("/gazebo/get_model_state");
    geometry_msgs::Pose pose;
    gazebo_msgs::GetModelState srv;
    srv.request.model_name = name; 
    get_model_state_client.call(srv);
    if(output){
         ROS_INFO("Pose of [%s]: position(x: %f, y: %f, z: %f), orientation(x: %f, y: %f, z: %f, w: %f)", 
             name.c_str(), 
             srv.response.pose.position.x, srv.response.pose.position.y, srv.response.pose.position.z,
             srv.response.pose.orientation.x, srv.response.pose.orientation.y, 
             srv.response.pose.orientation.z, srv.response.pose.orientation.w);
    }
    return srv.response.pose;
}



int main(int argc, char** argv) {
    ros::init(argc, argv, "gazebo_tf_broadcaster");
    ros::NodeHandle nh;

    //创建一个tf发布对象
    static tf::TransformBroadcaster tf_broadcaster;

    ros::Rate rate(10.0);  // 每秒10次发布频率

    while(ros::ok()){
        geometry_msgs::Pose robot_pose = getPose(nh, robot_name, true);
        
        // 创建 TransformStamped 消息，表示 odom -> base_link 的变换
        tf::Transform tf_msg;
        // tf_msg.header.frame_id = "world";        // 发布的父坐标系
        // tf_msg.child_frame_id = "wam/base_link";    // 发布的子坐标系

        // 设置位置
        tf_msg.setOrigin(tf::Vector3(robot_pose.position.x, robot_pose.position.y, robot_pose.position.z));

        // 设置方向（四元数）
        // 从 Pose 中提取方向（四元数）
        tf_msg.setRotation(tf::Quaternion(robot_pose.orientation.x, robot_pose.orientation.y, robot_pose.orientation.z, robot_pose.orientation.w));
        // tf_msg.transform.rotation.x = robot_pose.orientation.x;
        // tf_msg.transform.rotation.y = robot_pose.orientation.y;
        // tf_msg.transform.rotation.z = robot_pose.orientation.z;
        // tf_msg.transform.rotation.w = robot_pose.orientation.w;

        // 通过 tf_broadcaster 发布变换
        tf_broadcaster.sendTransform(tf::StampedTransform(tf_msg, ros::Time::now(), "world", "wam/base_link"));

        rate.sleep();
    }
    
    return 0;
}