// https://github.com/astuff/astuff_sensor_msgs/tree/master/mobileye_560_660_msgs/msg
// /clock
// /core_nodelet_manager/bond
// /diagnostics
// /localization/map_origin
// /localization/odometry/filtered_map
// /localization/odometry/filtered_odom
// /map/HERE_visualization/lanes
// /map/HERE_visualization/roads
// /minisim/location
// /minisim/waypoints
// /planning/fub_here_road_follower/parameter_descriptions
// /planning/fub_here_road_follower/parameter_updates
// /planning/planned_trajectory
// /rosout
// /rosout_agg
// /sensors/can/brake_info_report
// /sensors/can/brake_report
// /sensors/can/can_odom
// /sensors/can/can_rx
// /sensors/can/dbw_enabled
// /sensors/can/filtered_accel
// /sensors/can/fuel_level_report
// /sensors/can/gear_report
// /sensors/can/gps/fix
// /sensors/can/gps/time
// /sensors/can/gps/vel
// /sensors/can/imu/data_raw
// /sensors/can/joint_states
// /sensors/can/misc_1_report
// /sensors/can/sonar_cloud
// /sensors/can/steering_report
// /sensors/can/surround_report
// /sensors/can/throttle_info_report
// /sensors/can/throttle_report
// /sensors/can/tire_pressure_report
// /sensors/can/twist
// /sensors/can/twist_controller/parameter_descriptions
// /sensors/can/twist_controller/parameter_updates
// /sensors/can/vin
// /sensors/can/wheel_position_report
// /sensors/can/wheel_speed_report
// /sensors/mobileye/as_tx/lane_markers
// /sensors/mobileye/as_tx/lane_models
// /sensors/mobileye/as_tx/object_markers
// /sensors/mobileye/as_tx/objects
// /sensors/mobileye/can_tx
// /sensors/mobileye/parsed_tx/aftermarket_lane
// /sensors/mobileye/parsed_tx/aws_display
// /sensors/mobileye/parsed_tx/fixed_foe
// /sensors/mobileye/parsed_tx/lane
// /sensors/mobileye/parsed_tx/left_lka_lane
// /sensors/mobileye/parsed_tx/lka_num_of_next_lane_markers_reported
// /sensors/mobileye/parsed_tx/lka_reference_points
// /sensors/mobileye/parsed_tx/next_lka_lanes
// /sensors/mobileye/parsed_tx/obstacle_data
// /sensors/mobileye/parsed_tx/obstacle_status
// /sensors/mobileye/parsed_tx/right_lka_lane
// /sensors/mobileye/parsed_tx/tsr
// /sensors/mobileye/parsed_tx/tsr_vision_only

// Things that we might want to visualize
// // // Metrics
// /sensors/can/brake_report
  // Type: dbw_mkz_msgs/BrakeReport
// /sensors/can/can_odom
  // Type: nav_msgs/Odometry
// /sensors/can/gear_report
  // Type: dbw_mkz_msgs/GearReport
// /sensors/can/steering_report
  // Type: dbw_mkz_msgs/SteeringReport
// /sensors/can/throttle_report
  // Type: dbw_mkz_msgs/ThrottleReport

// // // Pathes
// /minisim/waypoints
  // Type: nav_msgs/Path
// /planning/planned_trajectory
  // Type: minisim_msgs/Trajectory

// Lanes are most important
// Odometry
// Objects
  // Let it be a point in relation to the camera
  // Camera isn't center of the car, it's a bit further than middle

// Parse:
  // Just get location of objects & lanes(this will be a line-> equation of a curve)
  // M grab -> everyone else visualize it 
    // The equation for the line is in the documentatoin
      // Page 92

// // // Mobileye Information
// /sensors/mobileye/as_tx/lane_markers
  // Type: visualization_msgs/Marker
// /sensors/mobileye/as_tx/lane_models
  // Type: derived_object_msgs/LaneModels
// /sensors/mobileye/as_tx/object_markers
  // Type: visualization_msgs/Marker
// /sensors/mobileye/as_tx/objects
  // Type: derived_object_msgs/ObjectWithCovariance
// /sensors/mobileye/parsed_tx/aftermarket_lane
  // Type: mobileye_560_660_msgs/AftermarketLane
// /sensors/mobileye/parsed_tx/aws_display
  // Type: mobile_560_660_msgs/AwsDisplay
// /sensors/mobileye/parsed_tx/fixed_foe
  // Type: mobile_560_660_msgs/FixedFoe

// /sensors/mobileye/parsed_tx/lane
  // Type: mobile_560_660_msgs/Lane
  // Basic information about detected lanes including curvature, heading, pitch angle, and yaw angle.
// /sensors/mobileye/parsed_tx/left_lka_lane
  // Type: mobileye_560_660_msgs/LkaLane
  // Extended information about the left lane including type, quality, marker width, and parameters used to generate a 3rd degree polynomial model.
// /sensors/mobileye/parsed_tx/right_lka_lane
  // Type: mobileye_560_660_msgs/LkaLane
  // Extended information about the right lane including type, quality, marker width, and parameters used to generate a 3rd degree polynomial model.

// /sensors/mobileye/parsed_tx/lka_num_of_next_lane_markers_reported
  // Type: mobileye_560_660_msgs/LkaNumOfNextLaneMarkersReported
// /sensors/mobileye/parsed_tx/lka_reference_points
  // Type: mobileye_560_660_msgs/LkaReferencePoints
// /sensors/mobileye/parsed_tx/next_lka_lanes
  // Type: mobileye_560_660_msgs/LkaLane
// /sensors/mobileye/parsed_tx/obstacle_data
  // Type: mobileye_560_660_msgs/ObstacleData
// /sensors/mobileye/parsed_tx/obstacle_status
  // Type: mobileye_560_660_msgs/ObstacleStatus
// /sensors/mobileye/parsed_tx/tsr
  // Type: mobileye_560_660_msgs/Tsr
// /sensors/mobileye/parsed_tx/tsr_vision_only
  // Type: mobileye_560_660_msgs/TsrVisionOnly

#include <iostream>

#include "mvp/engine.h"
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <mobileye_560_660_msgs/Lane.h>
#include <mobileye_560_660_msgs/LkaLane.h>
#include <mobileye_560_660_msgs/ObstacleData.h>
/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void laneParse(const mobileye_560_660_msgs::Lane::ConstPtr& passedLane)
{
  ROS_INFO("=======LANE=======\nLane Curvature: [%f]\nLane Heading: [%f]\nConstruction Area? [%d]\nPitch Angle: [%f]\nYaw Angle: [%f]\nRight_ldw_available? [%d]\nLeft_ldw_available? [%d] |" 
        , passedLane->lane_curvature 
        , passedLane->lane_heading 
        , passedLane->construction_area
        , passedLane->pitch_angle
        , passedLane->yaw_angle
        , passedLane->right_ldw_availability
        , passedLane->left_ldw_availability);
}

void obstacleParse(const mobileye_560_660_msgs::ObstacleData::ConstPtr& passedObst)
{
  ROS_INFO("=======OBST DATA=======\nposition_x: [%f]\nposition_y: [%f]\nRelative velocity x: [%f]\nLength: [%f]\nWidth: [%f]" 
        , passedObst->obstacle_pos_x 
        , passedObst->obstacle_pos_y
        , passedObst->obstacle_rel_vel_x
        , passedObst->obstacle_length
        , passedObst->obstacle_width);
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle lane;
  ros::NodeHandle obstacle;
  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */
  ros::Subscriber sub_lane = lane.subscribe("/sensors/mobileye/parsed_tx/lane", 1000, laneParse);
  ros::Subscriber sub_obstacle = obstacle.subscribe("/sensors/mobileye/parsed_tx/obstacle_data", 1000, obstacleParse);
  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  ros::spin();

  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("MVP Demo", 1600, 800);
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}
