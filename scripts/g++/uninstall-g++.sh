#!/bin/bash

# ===============================
# Uninstall g++
# ===============================

# Check if g++ is already installed
if ! command -v g++ >/dev/null 2>&1; then
	# Prompt user and exit
    echo "g++ is not installed.";
    exit 0;
fi

# Attempt to uninstall g++
if command -v apt >/dev/null 2>&1; then # Ubuntu/Debian
	sudo apt remove --purge -y g++;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg uninstall -y clang;
elif command -v yum >/dev/null 2>&1; then # RHEL/CentOS/Fedora
	sudo yum remove -y gcc-c++;
elif command -v pacman >/dev/null 2>&1; then # Arch
	sudo pacman -Rns --noconfirm gcc;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew uninstall gcc;
else
	echo "Unsupported package manager. Please uninstall g++ manually."; \
	exit 1;
fi
	