# ===============================
# Install g++
# ===============================

# Check if g++ is already installed
if command -v g++ >/dev/null 2>&1; then
    # Prompt user and exit
    echo "g++ is already installed.";
    exit 0;
fi

# Attempt to install g++
if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt update && sudo apt install -y g++;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg install -y clang;
elif command -v yum >/dev/null 2>&1; then
	sudo yum install -y gcc-c++;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -Sy --noconfirm gcc;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew install gcc;
else
	echo "Unsupported package manager. Please install g++ manually.";
	exit 1;
fi
	