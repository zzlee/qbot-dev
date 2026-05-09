# qbot-dev

ROS 2 Jazzy C++ development environment using Docker with multi-platform (amd64 + arm64) support.

## Quick start

```bash
make build   # build Docker image
make run     # start container with current dir mounted
```

Inside the container:

```bash
cd src
colcon build
source install/setup.bash
ros2 run <pkg> <node>
```

## Commands

| Command | Purpose |
|---|---|
| `make build` | Build for native platform |
| `make build-arm64` | Cross-build for arm64 |
| `make run` | Start container |
| `make setup-buildx` | One-time buildx setup |

## Project layout

```
├── src/           # ROS 2 packages
├── docker/        # Dockerfile, run script
├── Makefile       # Build/run targets
└── AGENTS.md      # Dev workflow reference
```

The project root is mounted to `/home/build` inside the container. Files persist on the host after exit.

## Requirements

- Docker
- `make setup-buildx` once for cross-platform builds
