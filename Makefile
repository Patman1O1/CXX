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
# Install Git
# ===============================
install-git:
	./scripts/cmake/install-git.sh

# ===============================
# Uninstall Git
# ===============================
uninstall-git:
	./scripts/cmake/uninstall-git.sh


# ===============================
# Install All
# ===============================
install-all: install-g++ install-clang install-gdb install-valgrind install-cmake install-git

# ===============================
# Uninstall All
# ===============================
uninstall-all: uninstall-g++ uninstall-clang uninstall-gdb uninstall-valgrind uninstall-cmake uninstall-git
	

# ===============================
# Upgrade
# ===============================
upgrade:
	./scripts/upgrade.sh
