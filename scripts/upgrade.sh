# ===============================
# Upgrade
# ===============================

if command -v apt >/dev/null 2>&1; then # Ubuntu
	sudo apt update && sudo apt upgrade -y;
elif command -v pkg >/dev/null 2>&1; then # Termux
	pkg update -y && pkg upgrade -y;
elif command -v yum >/dev/null 2>&1; then
	sudo yum update -y;
elif command -v dnf >/dev/null 2>&1; then
	sudo dnf upgrade -y;
elif command -v pacman >/dev/null 2>&1; then
	sudo pacman -Syu --noconfirm;
elif command -v brew >/dev/null 2>&1; then # macOS
	brew update && brew upgrade;
else
	echo "Unsupported package manager. Please upgrade manually.";
	exit 1;
fi
