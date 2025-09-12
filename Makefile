.PHONY: chmod \
		install-g++ \
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
CHMOD_ARG = 555
chmod:
	chmod $(CHMOD_ARG) ./scripts/g++/install-g++.sh && \
	chmod $(CHMOD_ARG) ./scripts/g++/uninstall-g++.sh && \

	chmod $(CHMOD_ARG) ./scripts/clang/install-clang.sh && \
	chmod $(CHMOD_ARG) ./scripts/clang/uninstall-clang.sh && \

	chmod $(CHMOD_ARG) ./scripts/gdb/install-gdb.sh && \
	chmod $(CHMOD_ARG) ./scripts/gdb/uninstall-gdb.sh && \

	chmod $(CHMOD_ARG) ./scripts/valgrind/install-valgrind.sh && \
	chmod $(CHMOD_ARG) ./scripts/valgrind/uninstall-valgrind.sh && \

	chmod $(CHMOD_ARG) ./scripts/git/install-git.sh && \
	chmod $(CHMOD_ARG) ./scripts/git/uninstall-git.sh && \

	chmod $(CHMOD_ARG) ./scripts/cmake/install-cmake.sh && \
	chmod $(CHMOD_ARG) ./scripts/cmake/uninstall-cmake.sh && \


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
