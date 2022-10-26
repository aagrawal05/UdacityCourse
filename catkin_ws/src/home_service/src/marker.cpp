#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <visualization_msgs/Marker.h>

int state = 0;
visualization_msgs::Marker marker;
ros::Publisher marker_pub;

void state_callback(const std_msgs::Empty::ConstPtr& msg){
  state++;
  ROS_INFO("State updated: %d", state);
  if (state == 1){
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "pickup";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::DELETE;
  } else {
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();
    marker.ns = "pickup";
    marker.id = 0;
    marker.type = visualization_msgs::Marker::CUBE;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = -5.0;
    marker.pose.position.y = 0.0;
    marker.pose.position.z = 0.0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;
    marker.lifetime = ros::Duration(); 
  }
  marker_pub.publish(marker);
}
int main( int argc, char** argv )
{
  ros::init(argc, argv, "home_service_marker_node");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  ros::Subscriber state_sub = n.subscribe("/state_update", 10, state_callback);

  //Setup initial marker
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();
  marker.ns = "pickup";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::CUBE;
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = 1.0;
  marker.pose.position.y = 0.0;
  marker.pose.position.z = 0.0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;
  marker.scale.x = 0.2;
  marker.scale.y = 0.2;
  marker.scale.z = 0.2;
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;
  marker.lifetime = ros::Duration();  
 
  // Set our initial shape type to be a cube
  while (ros::ok())
  {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);   
    ros::spin();
    r.sleep();
  }
}

