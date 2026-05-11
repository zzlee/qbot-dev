cmake_minimum_required(VERSION 3.8)
project(qbot_utils)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

add_library(qbot_utils src/qbot_utils.cpp)
target_include_directories(qbot_utils PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

ament_export_include_directories(include)
ament_export_libraries(qbot_utils)
install(TARGETS qbot_utils
  EXPORT qbot_utilsTarget
  DESTINATION lib)
ament_export_targets(qbot_utilsTarget)
ament_package()

install(DIRECTORY include/ DESTINATION include)
