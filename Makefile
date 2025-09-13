.PHONY: install-g++ \
		uninstall-g++ \
		install-gdb \
		uninstall-gdb \
		install-valgrind \
		uninstall-valgrind \
		install-clang \
		uninstall-clang \
		install-cmake \
		uninstall-cmake \
		install-git \
		uninstall-git \
		install-gtest \
		uninstall-gtest \
		install-all \
		uninstall-all


# ===============================
# Install g++
# ===============================
install-g++: 
	./scripts/g++/install-g++.sh

# ===============================
# Uninstall g++
# ===============================
uninstall-g++:
	./scripts/g++/uninstall-g++.sh


# ===============================
# Install clang
# ===============================
install-clang:
	./scripts/clang/install-clang.sh

# ===============================
# Uninstall clang
# ===============================
uninstall-clang:
	./scripts/clang/uninstall-clang.sh


# ===============================
# Install GDB
# ===============================
install-gdb:
	./scripts/gdb/install-gdb.sh

# ===============================
# Uninstall GDB
# ===============================
uninstall-gdb:
	./scripts/gdb/uninstall-gdb.sh


# ===============================
# Install Valgrind
# ===============================
install-valgrind:
	./scripts/valgrind/install-valgrind.sh

# ===============================
# Uninstall Valgrind
# ===============================
uninstall-valgrind:
	./scripts/valgrind/uninstall-valgrind.sh


# ===============================
# Install CMake
# ===============================
install-cmake:
	./scripts/cmake/install-cmake.sh

# ===============================
# Uninstall CMake
# ===============================
uninstall-cmake:
	./scripts/cmake/uninstall-cmake.sh


# ===============================
# Install gtest
# ===============================
install-gtest:
	./scripts/gtest/install-gtest.sh

# ===============================
# Uninstall gtest
# ===============================
uninstall-gtest:
	./scripts/gtest/uninstall-gtest.sh


# ===============================
# Install All
# ===============================
install-all: install-g++ install-clang install-gdb install-valgrind install-cmake install-git install-gtest

# ===============================
# Uninstall All
# ===============================
uninstall-all: uninstall-g++ uninstall-clang uninstall-gdb uninstall-valgrind uninstall-cmake uninstall-git uninstall-gtest


# ===============================
# Chmod all
# ===============================
chmod-all:
	chmod $(ARG) ./scripts/chmod-all.sh && ./scripts/chmod-all.sh $(ARG)


# ===============================
# Upgrade
# ===============================
upgrade:
	./scripts/upgrade.sh
