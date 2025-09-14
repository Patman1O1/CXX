.PHONY: install-clang      \
		uninstall-clang    \
		install-cmake      \
		uninstall-cmake    \
		install-g++        \
		uninstall-g++      \
		install-gdb        \
		uninstall-gdb      \
		install-git        \
		uinstall-git       \
		install-valgrind   \
		uninstall-valgrind \
		chmod-all          \
		upgrade            


# ===============================
# Install Clang
# ===============================
install-clang:

	./scripts/pkg-mgr.sh install clangd

# ===============================
# Uninstall Clang
# ===============================
uninstall-clang:
	./scripts/pkg-mgr.sh uninstall clangd


# ===============================
# Install CMake
# ===============================
install-cmake:
	./scripts/pkg-mgr.sh install cmake

# ===============================
# Uninstall CMake
# ===============================
uninstall-cmake:
	./scripts/pkg-mgr.sh uninstall cmake


# ===============================
# Install g++
# ===============================
install-g++: 
	./scripts/pkg-mgr.sh install g++

# ===============================
# Uninstall g++
# ===============================
uninstall-g++:
	./scripts/pkg-mgr.sh uninstall g++


# ===============================
# Install GDB
# ===============================
install-gdb:
	./scripts/pkg-mgr.sh install gdb

# ===============================
# Uninstall GDB
# ===============================
uninstall-gdb:
	./scripts/pkg-mgr.sh uninstall gdb


# ===============================
# Install Git
# ===============================
install-git:
	./scripts/pkg-mgr.sh install git

# ===============================
# Uninstall Git
# ===============================
uninstall-git:
	./scripts/pkg-mgr.sh uninstall git


# ===============================
# Install Valgrind
# ===============================
install-valgrind:
	./scripts/pkg-mgr.sh install valgrind

# ===============================
# Uninstall Valgrind
# ===============================
uninstall-valgrind:
	./scripts/pkg-mgr.sh uninstall valgrind


# ===============================
# Install All
# ===============================
install-all: install-clang    \
			 install-cmake    \
			 install-g++      \
			 install-gdb      \
			 install-git      \
			 install-valgrind \

# ===============================
# Uninstall All
# ===============================
uninstall-all: uninstall-clang    \
			   uninstall-cmake    \
			   uninstall-g++      \
			   uninstall-gdb      \
			   uninstall-git      \
			   uninstall-valgrind \


# ===============================
# Chmod All
# ===============================
chmod-all:
	chmod $(ARG) ./scripts/chmod-all.sh && ./scripts/chmod-all.sh $(ARG)


# ===============================
# Upgrade
# ===============================
upgrade:
	./scripts/upgrade.sh
