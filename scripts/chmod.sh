# ===============================
# Chmod
# ===============================
# 
# chmod 123 path/to/filename
# ==========================
# 1st digit = user permissions
# 2nd digit = group permissions
# 3rd digit = others' permissions
# ===========================
# 0 = 0b000 = --- (no permissions)
# 1 = 0b001 = --x (can execute)
# 2 = 0b010 = -w- (can write)
# 3 = 0b011 = -wx (can write and execute)
# 4 = 0b100 = r-- (can read)
# 5 = 0b101 = r-x (can read and execute)
# 6 = 0b110 = rw- (can read and write)
# 7 = 0b111 = rwx (can read, write, and execute)
# ============================
CHMOD_ARG="$1"
chmod "$CHMOD_ARG" ./scripts/g++/install-g++.sh
chmod "$CHMOD_ARG" ./scripts/g++/uninstall-g++.sh

chmod "$CHMOD_ARG" ./scripts/clang/install-clang.sh
chmod "$CHMOD_ARG" ./scripts/clang/uninstall-clang.sh

chmod "$CHMOD_ARG" ./scripts/gdb/install-gdb.sh
chmod "$CHMOD_ARG" ./scripts/gdb/uninstall-gdb.sh

chmod "$CHMOD_ARG" ./scripts/valgrind/install-valgrind.sh
chmod "$CHMOD_ARG" ./scripts/valgrind/uninstall-valgrind.sh

chmod "$CHMOD_ARG" ./scripts/git/install-git.sh
chmod "$CHMOD_ARG" ./scripts/git/uninstall-git.sh

chmod "$CHMOD_ARG" ./scripts/cmake/install-cmake.sh
chmod "$CHMOD_ARG" ./scripts/cmake/uninstall-cmake.sh
