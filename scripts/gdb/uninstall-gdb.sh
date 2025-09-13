#!/bin/bash

# ===============================
# Uninstall GDB
# ===============================

# Check if GDB is already installed
if ! command -v gdb >/dev/null 2>&1; then
    # Prompt user and exit
    echo "GDB is not installed.";
    exit 0;
fi

# Attempt to uninstall GDB
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt remove --purge -y gdb;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg uninstall -y gdb;
elif command -v yum >/dev/null 2>&1; then
	sudo yum remove -y gdb;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -Rns --noconfirm gdb;
elif command -v brew >/dev/null 2>&1; then # macOS
    brew uninstall gdb;
else
	echo "Unsupported package manager. Please uninstall GDB manually.";
	exit 1;
fi
	