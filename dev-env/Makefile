IMAGE_NAME ?= ros2_dev
DOCKER_DIR  := docker

.PHONY: build build-arm64 build-amd64 run run-arm64 setup-buildx clean

# Detect native architecture
UNAME_M := $(shell uname -m)
ifeq ($(UNAME_M),x86_64)
  NATIVE_PLATFORM := linux/amd64
endif
ifeq ($(UNAME_M),aarch64)
  NATIVE_PLATFORM := linux/arm64
endif

BUILD_ARGS := --build-arg UID=$(shell id -u) --build-arg GID=$(shell id -g)

# Build for native platform
build:
	@echo "Building for native platform ($(NATIVE_PLATFORM))..."
	docker build $(BUILD_ARGS) -t $(IMAGE_NAME) $(DOCKER_DIR)

# Build for arm64 (e.g. from x86_64 machine)
build-arm64:
	@echo "Building for linux/arm64..."
	docker buildx build \
	  $(BUILD_ARGS) \
	  --platform linux/arm64 \
	  -t $(IMAGE_NAME):arm64 \
	  --load \
	  $(DOCKER_DIR)

# Build for amd64 (e.g. from arm64 / Apple Silicon machine)
build-amd64:
	@echo "Building for linux/amd64..."
	docker buildx build \
	  $(BUILD_ARGS) \
	  --platform linux/amd64 \
	  -t $(IMAGE_NAME):amd64 \
	  --load \
	  $(DOCKER_DIR)

# Build multi-arch manifest (push to registry)
build-all:
	@echo "Building and pushing multi-arch image..."
	docker buildx build \
	  --platform linux/amd64,linux/arm64 \
	  -t $(IMAGE_NAME):latest \
	  --push \
	  $(DOCKER_DIR)

# Run native image
run:
	./$(DOCKER_DIR)/run.sh native

# Run arm64 image
run-arm64:
	IMAGE=$(IMAGE_NAME):arm64 ./$(DOCKER_DIR)/run.sh arm64

# Set up buildx builder (one-time setup)
setup-buildx:
	docker buildx create --name multiarch --use || true
	docker buildx inspect --bootstrap

# Clean up dangling images
clean:
	docker image prune -f
