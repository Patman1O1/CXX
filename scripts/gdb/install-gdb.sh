#!/bin/bash

# ===============================
# Install GDB
# ===============================

# Check if GDB is already installed
if command -v gdb >/dev/null 2>&1; then
    # Prompt user and exit
    echo "GDB is already installed.";
    exit 0;
fi

# Attempt to install GDB
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt install -y gdb;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg install -y gdb;
elif command -v yum >/dev/null 2>&1; then
	sudo yum install -y gdb;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -S --noconfirm gdb;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew install gdb;
else
	echo "Unsupported package manager. Please install GDB manually.";
	exit 1;
fi
