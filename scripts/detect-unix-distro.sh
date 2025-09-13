#!/bin/bash

# ===============================
# Detect Unix Distributor
# ===============================

# Exit the script immediately if any command returns a non-zero exit status
set -e

# Check the Unix distribution
if [ -f /etc/os-release ]; then # Linux
    . /etc/os-release
    echo $ID
elif [ "$(uname -s)" = "Darwin" ]; then # macOS
    echo "mac-os"
elif [ -n "$PREFIX" ] && [ -x "$(command -v pkg)" ]; then # Termux (Android)
    echo "termux"
else
    echo "unknown"
fi
