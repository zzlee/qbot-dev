#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <algorithm>
#include <vector>

class DepthProcessorNode : public rclcpp::Node {
public:
    DepthProcessorNode() : Node("depth_processor_node") {
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "/camera/depth/image_raw", 10, std::bind(&DepthProcessorNode::depth_callback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Depth Processor Node started. Subscribing to /camera/depth/image_raw");
    }

private:
    void depth_callback(const sensor_msgs::msg::Image::SharedPtr msg) {
        if (msg->encoding != "32FC1") {
            RCLCPP_WARN(this->get_logger(), "Unsupported encoding: %s. Expected 32FC1", msg->encoding.c_str());
            return;
        }

        const float* data = reinterpret_cast<const float*>(msg->data.data());
        size_t num_pixels = msg->width * msg->height;
        
        float min_dist = std::numeric_limits<float>::max();
        for (size_t i = 0; i < num_pixels; ++i) {
            if (data[i] < min_dist) {
                min_dist = data[i];
            }
        }

        if (min_dist < 1.0f) {
            RCLCPP_WARN(this->get_logger(), "Obstacle detected! Min distance: %.2fm", min_dist);
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DepthProcessorNode>());
    rclcpp::shutdown();
    return 0;
}
