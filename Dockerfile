FROM ubuntu:22.04

# Install build tools
RUN apt-get update && apt-get install -y \
    build-essential cmake \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy project
COPY . .

# Build
RUN mkdir build && cd build && cmake .. && make -j$(nproc)

# Run the DB binary when container starts
CMD ["./build/mydb"]
