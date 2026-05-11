cmake_minimum_required(VERSION 3.8)
project(qbot_app)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(qbot_utils REQUIRED)

add_executable(qbot_app_node src/qbot_app_node.cpp)
target_link_libraries(qbot_app_node rclcpp::rclcpp qbot_utils::qbot_utils)
target_include_directories(qbot_app_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include})

install(TARGETS qbot_app_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()
