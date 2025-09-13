#!/bin/bash

# ===============================
# Install clang
# ===============================

# Check if clang is already installed
if command -v clangd >/dev/null 2>&1; then
    # Prompt user and exit
	echo "Clang is already installed.";
    exit 0;
fi

# Attempt to install clang
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt install -y clangd;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg install -y clangd;
elif command -v yum >/dev/null 2>&1; then
	sudo yum install -y clang-tools-extra;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -S --noconfirm clang;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew install llvm;
else \
	echo "Unsupported package manager. Please install clang manually.";
	exit 1;
fi
