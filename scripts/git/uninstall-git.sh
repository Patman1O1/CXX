#!/bin/bash

# ===============================
# Uninstall Git
# ===============================

# Check if Git is already installed
if ! command -v git >/dev/null 2>&1; then
    # Prompt user and exit
    echo "Git is not installed.";
    exit 0;
fi

# Attempt to uninstall Git
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt remove --purge -y git;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg uninstall -y git;
elif command -v yum >/dev/null 2>&1; then
	sudo yum remove -y git;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -Rns --noconfirm git;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew uninstall git;
else
	echo "Unsupported package manager. Please uninstall Git manually.";
	exit 1;
fi
	