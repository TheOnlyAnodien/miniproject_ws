#include <ros/ros.h>
#include <turtlesim/Pose.h>
#include <iomanip>
#include <geometry_msgs/Twist.h>

ros::Publisher *pubPtr;

void poseMessageRecieved(const turtlesim::Pose&msgIn){
	geometry_msgs::Twist msgOut;
	msgOut.linear.x = 8;
	msgOut.angular.z = 2*double(rand())/double(RAND_MAX)-2;
	
	if (msgIn.x > 6){
	 msgOut.angular.z = 8;
	 msgOut.linear.x = 4;
	}
	else if (msgIn.x < 4){
	 msgOut.angular.z = 8;
	 msgOut.linear.x = 4;
	}
	else if (msgIn.y > 6){
	 msgOut.angular.z = 8;
	 msgOut.linear.x = 4;
	}
	else if (msgIn.y < 4){
	 msgOut.angular.z = 8;
	 msgOut.linear.x = 4;
	}
	pubPtr-> publish(msgOut);

	ROS_INFO_STREAM(std::setprecision(2)<<std::fixed<<"position= (" << msgIn.x << ","
	<< msgIn.y << ")" << "direction= " << msgIn.theta);
	
	}

int main(int argc, char **argv){
	ros::init(argc, argv, "subscribe_to_pose");
	ros::NodeHandle nh;
	
	pubPtr = new ros::Publisher(nh.advertise<geometry_msgs::Twist>
	("turtle1/cmd_vel", 1000));

	ros::Subscriber sub = nh.subscribe("turtle1/pose", 1000, &poseMessageRecieved);
	ros::spin();
}
