cmake_minimum_required(VERSION 3.8)
project(qbot_simulation)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)

# Generator Node
add_executable(depth_generator_node src/depth_generator_node.cpp)
ament_target_dependencies(depth_generator_node rclcpp sensor_msgs)

# Processor Node
add_executable(depth_processor_node src/depth_processor_node.cpp)
ament_target_dependencies(depth_processor_node rclcpp sensor_msgs)


install(TARGETS
  depth_generator_node
  depth_processor_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
