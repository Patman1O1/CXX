#!/bin/bash

# ===============================
# Chmod all
# ===============================
ARG="$1"

chmod "$ARG" ./scripts/clang/ *
chmod "$ARG" ./scripts/cmake/ *
chmod "$ARG" ./scripts/g++/ *
chmod "$ARG" ./scripts/gdb/ *
chmod "$ARG" ./scripts/git/ *
chmod "$ARG" ./scripts/gtest/ *
chmod "$ARG" ./scripts/valgrind/ *
chmod "$ARG" ./scripts/new-lib.sh
chmod "$ARG" ./scripts/upgrade.sh
