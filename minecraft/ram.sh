#!/bin/bash

# Find the process ID (PID) using the port 25565
PID=$(lsof -ti :25565)

# Check if the process exists
if [ -z "$PID" ]; then
    echo "No process found running on port 25565."
    exit 1
fi

# Get the memory usage in MB
RAM_USAGE=$(ps -o rss= -p $PID | awk '{print $1 / 1024}')
echo "Minecraft server (PID: $PID) is using $RAM_USAGE KB of RAM."
