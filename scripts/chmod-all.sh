#!/bin/bash

# ===============================
# Chmod all
# ===============================
ARG="$1"

chmod "$ARG" ./scripts/clang/
chmod "$ARG" ./scripts/clang/install-clang.sh
chmod "$ARG" ./scripts/clang/uninstall-clang.sh

chmod "$ARG" ./scripts/cmake/
chmod "$ARG" ./scripts/cmake/install-cmake.sh
chmod "$ARG" ./scripts/cmake/uninstall-cmake.sh

chmod "$ARG" ./scripts/g++/
chmod "$ARG" ./scripts/g++/install-g++.sh
chmod "$ARG" ./scripts/g++/uninstall-g++.sh

chmod "$ARG" ./scripts/gdb/
chmod "$ARG" ./scripts/gdb/install-gdb.sh
chmod "$ARG" ./scripts/gdb/uninstall-gdb.sh

chmod "$ARG" ./scripts/git/
chmod "$ARG" ./scripts/git/install-git.sh
chmod "$ARG" ./scripts/git/uninstall-git.sh

chmod "$ARG" ./scripts/gtest/
chmod "$ARG" ./scripts/gtest/install-gtest.sh
chmod "$ARG" ./scripts/gtest/uninstall-gtest.sh

chmod "$ARG" ./scripts/valgrind/
chmod "$ARG" ./scripts/valgrind/install-valgrind.sh
chmod "$ARG" ./scripts/valgrind/uninstall-valgrind.sh

chmod "$ARG" ./scripts/new-lib.sh
chmod "$ARG" ./scripts/upgrade.sh
