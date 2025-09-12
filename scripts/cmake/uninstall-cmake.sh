# ===============================
# Uninstall CMake
# ===============================

# Check if CMake is already installed
if ! command -v cmake >/dev/null 2>&1; then
    # Prompt user and exit
    echo "CMake is not installed.";
    exit 0;
fi

# Attempt to uninstall CMake
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt remove --purge -y cmake;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg uninstall -y cmake;
elif command -v yum >/dev/null 2>&1; then
	sudo yum remove -y cmake;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -Rns --noconfirm cmake;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew uninstall cmake;
else
	echo "Unsupported package manager. Please uninstall CMake manually.";
	exit 1;
fi
