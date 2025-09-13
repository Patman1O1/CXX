#!/bin/bash

# ===============================
# Uninstall clang
# ===============================

# Check if clang is already installed
if ! command -v clangd >/dev/null 2>&1; then
    # Prompt user and exit
    echo "Clang is not installed.";
    exit 0;
fi

# Attempt to uninstall clang
if command -v apt >/dev/null 2>&1; then # Ubuntu/Debian
	sudo apt remove --purge -y clangd;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg uninstall -y clangd;
elif command -v yum >/dev/null 2>&1; then # RHEL/CentOS/Fedora
	sudo yum remove -y clang-tools-extra;
elif command -v pacman >/dev/null 2>&1; then # Arch
	sudo pacman -Rns --noconfirm clang;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew uninstall llvm;
else
	echo "Unsupported package manager. Please uninstall clangd manually.";
	exit 1;
fi
