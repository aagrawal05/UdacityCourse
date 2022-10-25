#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  std_msgs::Empty empty_msg;
  ros::init(argc, argv, "home_service_goal_node");    
  ros::NodeHandle n;
  ros::Publisher goal_pub = n.advertise<std_msgs::Empty>("state_update", 1);

  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal, goal2;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = 1.0;
  goal.target_pose.pose.orientation.w = 1.0;
  goal2.target_pose.header.frame_id = "map";
  goal2.target_pose.header.stamp = ros::Time::now();
  goal2.target_pose.pose.position.x = -5.0;
  goal2.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
     ROS_INFO("Pick up point reached");
     goal_pub.publish(empty_msg);
     while(!ac.waitForServer(ros::Duration(5.0))){
         ROS_INFO("Waiting for pick up");
     }
     goal_pub.publish(empty_msg);
     ROS_INFO("Sending second goal");
     ac.sendGoal(goal2);
     ac.waitForResult();
     if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
       ROS_INFO("Item delivered");
  } else
    ROS_INFO("Failed to reach pickup point");
  return 0;
}

