#!/bin/bash

# ===============================
# Install CMake
# ===============================

# Check if CMake is already installed
if command -v cmake >/dev/null 2>&1; then
    # Prompt user and exit
	echo "CMake is already installed.";
    exit 0;
fi

# Attempt to install CMake
if command -v apt >/dev/null 2>&1; then # Ubuntu/Debian
	sudo apt install -y cmake;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg install -y cmake;
elif command -v yum >/dev/null 2>&1; then # RHEL/CentOS/Fedora
	sudo yum install -y cmake;
elif command -v pacman >/dev/null 2>&1; then # Arch
	sudo pacman -S --noconfirm cmake;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew install cmake;
else
	echo "Unsupported package manager. Please install CMake manually.";
	exit 1;
fi
