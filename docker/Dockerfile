FROM ros:jazzy-ros-base

ARG UID=1000
ARG GID=1000

# Install basic build tools and dependencies for C++ development
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    python3-colcon-common-extensions \
    python3-rosdep \
    vim \
    wget \
    curl \
    ca-certificates \
    sudo \
    && rm -rf /var/lib/apt/lists/*

# Remove pre-existing ubuntu user (UID 1000) to free up the ID
RUN userdel -r ubuntu 2>/dev/null || true; \
    groupdel ubuntu 2>/dev/null || true; \
    groupadd -g $GID build

# Create 'build' user with password 'build' and grant sudo privileges
RUN useradd -m -s /bin/bash -u $UID -g $GID build && \
    echo 'build:build' | chpasswd && \
    adduser build sudo

# Initialize rosdep as root
RUN rosdep init || true

# Create a workspace directory and set permissions
WORKDIR /ros2_ws
RUN chown -R build:build /ros2_ws

# Switch to 'build' user for remaining setup
USER build
WORKDIR /home/build

# Run rosdep update as build user
RUN rosdep update

# Install OpenCode as build user
RUN curl -fsSL https://opencode.ai/install | bash

# Set up the shell to source ROS 2 automatically and ensure OpenCode is in PATH
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

# Default command: start bash
CMD ["bash"]

