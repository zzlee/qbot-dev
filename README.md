# qbot-dev

ROS 2 Jazzy C++ development environment using Docker with multi-platform (amd64 + arm64) support.

## Quick start

```bash
cd dev-env && make build   # build Docker image
cd dev-env && make run     # start container with current dir mounted
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
| `cd dev-env && make build` | Build for native platform |
| `cd dev-env && make build-arm64` | Cross-build for arm64 |
| `cd dev-env && make run` | Start container |
| `cd dev-env && make setup-buildx` | One-time buildx setup |

## Project layout

```
├── src/           # ROS 2 packages
├── dev-env/        # Dockerfile, run script, Makefile
└── AGENTS.md      # Dev workflow reference
```

The project root is mounted to `/home/build` inside the container. Files persist on the host after exit.

## Requirements

- Docker
- `make setup-buildx` once for cross-platform builds
