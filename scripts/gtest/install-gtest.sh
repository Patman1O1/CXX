#!/bin/bash

# ===============================
# Install gtest
# ===============================

# Check if gtest and gmock are already installed (non-Termux)
if command -v ls /usr/lib/x86_64-linux-gnu/libgtest* >/dev/null 2>&1 && \
   command -v ls /usr/lib/x86_64-linux-gnu/libgmock* >/dev/null 2>&1; then
    # Prompt user and exit
	echo "GoogleTest and GoogleMock are already installed.";
	exit 0;
fi

# Check if gtest and gmock are already installed (Termux)
if command -v ls $PREFIX/lib/libgtest* >/dev/null 2>&1 && \
   command -v ls $PREFIX/lib/libgmock* >/dev/null 2>&1; then
    # Prompt user and exit
	echo "GoogleTest and GoogleMock are already installed.";
	exit 0;
fi

