#include "rclcpp/rclcpp.hpp"
#include <iostream>

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("qbot_app_node");
  RCLCPP_INFO(node->get_logger(), "qbot_app_node has started successfully!");
  rclcpp::shutdown();
  return 0;
}
