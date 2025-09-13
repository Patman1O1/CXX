#!/bin/bash

# ===============================
# Install Valgrind
# ===============================

# Check if Valgrind is already installed
if command -v valgrind >/dev/null 2>&1; then
    # Prompt user and exit
    echo "Valgrind is already installed.";
    exit 0;
fi

# Attempt to install Valgrind
if command -v apt >/dev/null 2>&1; then # Ubuntu/Debian
	sudo apt install -y valgrind;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg install -y valgrind;
elif command -v yum >/dev/null 2>&1; then # RHEL/CentOS/Fedora
	sudo yum install -y valgrind;
elif command -v pacman >/dev/null 2>&1; then # Arch
	sudo pacman -S --noconfirm valgrind;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew install valgrind;
else
	echo "Unsupported package manager. Please install Valgrind manually.";
    exit 1;
fi
