#!/bin/bash
set -e

IMAGE="${IMAGE:-ros2_dev}"
PLATFORM="${1:-native}"

if [ "$PLATFORM" = "arm64" ]; then
  IMAGE="${IMAGE}:arm64"
elif [ "$PLATFORM" = "amd64" ]; then
  IMAGE="${IMAGE}:amd64"
fi

exec docker run -it \
  -v "$(pwd):/home/build" \
  --net=host \
  --name ros2_container \
  "$IMAGE"
