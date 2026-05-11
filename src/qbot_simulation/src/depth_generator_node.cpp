#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std::chrono_literals;

class DepthGeneratorNode : public rclcpp::Node {
public:
    DepthGeneratorNode() : Node("depth_generator_node"), count_(0) {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("/camera/depth/image_raw", 10);
        timer_ = this->create_wall_timer(100ms, std::bind(&DepthGeneratorNode::timer_callback, this));
        RCLCPP_INFO(this->get_logger(), "Depth Generator Node started. Publishing to /camera/depth/image_raw");
    }

private:
    void timer_callback() {
        auto message = sensor_msgs::msg::Image();
        message.height = 480;
        message.width = 640;
        message.encoding = "32FC1";

        // 32FC1 means 4 bytes per pixel
        std::vector<float> data(message.width * message.height);
        
        float wall_dist = 5.0f;
        float obstacle_dist = 0.5f;
        int obstacle_size = 50;
        
        // Moving obstacle position
        int obs_x = (count_ % (message.width - obstacle_size));
        int obs_y = 240; // center

        for (int y = 0; y < message.height; ++y) {
            for (int x = 0; x < message.width; ++x) {
                if (x >= obs_x && x < obs_x + obstacle_size && y >= obs_y && y < obs_y + obstacle_size) {
                    data[y * message.width + x] = obstacle_dist;
                } else {
                    data[y * message.width + x] = wall_dist;
                }
            }
        }

        // Convert float vector to byte vector
        message.data.resize(data.size() * sizeof(float));
        std::memcpy(message.data.data(), data.data(), message.data.size());

        publisher_->publish(message);
        count_++;
    }

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int count_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DepthGeneratorNode>());
    rclcpp::shutdown();
    return 0;
}
