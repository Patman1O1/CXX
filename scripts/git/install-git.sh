#!/bin/bash

# ===============================
# Install Git
# ===============================

# Check if Git is already installed
if command -v git >/dev/null 2>&1; then
    # Prompt user and exit
	echo "Git is already installed.";
	exit 0;
fi

# Attempt to install Git
if command -v apt >/dev/null 2>&1; then # Ubuntu/Debian
	sudo apt update && sudo apt install -y git;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg install -y git;
elif command -v yum >/dev/null 2>&1; then # RHEL/CentOS/Fedora
	sudo yum install -y git;
elif command -v pacman >/dev/null 2>&1; then # Arch
	sudo pacman -S --noconfirm git;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew install git;
else
	echo "Unsupported package manager. Please install Git manually.";
	exit 1;
fi
