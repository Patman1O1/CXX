#!/bin/bash

# ===============================
# Uninstall Valgrind
# ===============================

# Check if Valgrind is already installed
if ! command -v valgrind >/dev/null 2>&1; then
    # Prompt user and exit
    echo "Valgrind is not installed.";
    exit 0;
fi

# Attempt to uninstall Valgrind
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt remove --purge -y valgrind;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg uninstall -y valgrind;
elif command -v yum >/dev/null 2>&1; then
	sudo yum remove -y valgrind;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -Rns --noconfirm valgrind;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew uninstall valgrind;
else
	echo "Unsupported package manager. Please uninstall Valgrind manually.";
	exit 1;
fi
	