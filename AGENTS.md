# qbot-dev — ROS 2 Jazzy C++ dev environment

## Quick start

```bash
make build        # build Docker image for native platform
make build-app    # build ROS 2 apps from host (headless)
make run          # start container (mounts $(pwd) to /home/build)
```

Inside container: `cd /home/build/src`, create packages, `colcon build`.

## Build commands

| Command | What |
|---|---|
| `make build` | Native platform build |
| `make build-arm64` | Cross-build for arm64 (needs `make setup-buildx` once) |
| `make build-amd64` | Cross-build for amd64 |
| `make build-app` | Build ROS 2 application from host (headless) |
| `make test-app` | Run ROS 2 tests from host (headless) |
| `make run` | Run native container |
| `make run-arm64` | Run arm64 container |
| `make setup-buildx` | One-time: create buildx multiarch builder |

`make build` passes `--build-arg UID=$(id -u) --build-arg GID=$(id -g)` automatically so the `build` user inside the container matches host ownership.

## Container structure

- **User**: `build` (sudo with password `build`). Pre-existing `ubuntu:1000:1000` from base image is deleted.
- **Mount**: `$(pwd)` → `/home/build` (the `build` user's home)
- **ROS 2**: sourced in `/etc/bash.bashrc` (survives volume mount of `/home/build`)
- **OpenCode**: pre-installed globally at `/usr/local/bin/opencode` (survives volume mount)
- **Network**: `--net=host` for ROS 2 inter-process communication

## Development workflow

1. Create ROS 2 packages under `src/` on the host.
2. Build using `make build-app` (headless) or `make run` (interactive).
3. If using interactive mode: Inside: `colcon build`, then `source install/setup.bash`, then `ros2 run <pkg> <node>`.
4. Run tests using `make test-app` (headless).
5. Exit container (Ctrl+D) — all source files persist on host in `src/`.

## Important

- **`src/` is excluded from the Docker build** (`.dockerignore`). Source code is mounted at runtime. To add new system dependencies, update `Dockerfile` and rebuild.
- **`.gitignore`** ignores `build/`, `install/`, `log/` — colcon output stays out of version control.
