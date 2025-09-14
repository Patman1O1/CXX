#!/bin/bash

# ===============================
# Package Manager
# ===============================

# Exit the script immediately if any command returns a non-zero exit status
set -e

# If the user entered no arguments...
if [ $# -lt 1 ]; then
    # Prompt the user to enter at least one command line argument and exit
    echo "❌ Usage: $0 <install|uninstall|update> [pkg1 pkg2 ... pkgN]"
    exit 1
fi

# Remove first argument (the package action), leaving only the package names
ACTION=$1
shift
PKGS="$@"

# Get the Unix distribution
DISTRO=$(./scripts/detect-distro.sh)

# If the Unix distribution is not supported...
if [ "$DISTRO" = "unknown" ]; then
    # Prompt the user and exit
    echo "❌ Unsupported Unix distribution"
    exit 1
fi

# Perform the user-specified action on the user-specified packages
case "$DISTRO:$ACTION" in
    # Ubuntu/Debian Actions
    ubuntu:install|debian:install)
        sudo apt update
        sudo apt install -y $PKGS
        ;;
    ubuntu:uninstall|debian:uninstall)
        sudo apt remove --purge -y $PKGS
        ;;
    ubuntu:update|debian:update)
        sudo apt update && sudo apt upgrade -y
        ;;
    ubuntu:check|debian:check)
        for pkg in $PKGS; do
            if dpkg -l | grep -q "^ii\s\+$pkg"; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # Fedora Actions
    fedora:install)
        sudo dnf install -y $PKGS
        ;;
    fedora:uninstall)
        sudo dnf remove -y $PKGS
        ;;
    fedora:update)
        sudo dnf upgrade -y
        ;;
    fedora:check|centos:check|rhel:check)
        for pkg in $PKGS; do
            if rpm -q "$pkg" >/dev/null 2>&1; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # Centos Actions
    centos:install|rhel:install)
        sudo yum install -y $PKGS
        ;;
    centos:uninstall|rhel:uninstall)
        sudo yum remove -y $PKGS
        ;;
    centos:update|rhel:update)
        sudo yum update -y
        ;;
    centos:check|rhel:check)
        for pkg in $PKGS; do
            if rpm -q "$pkg" >/dev/null 2>&1; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # Arch/Manjaro Actions
    arch:install|manjaro:install)
        sudo pacman -Syu --noconfirm $PKGS
        ;;
    arch:uninstall|manjaro:uninstall)
        sudo pacman -Rns --noconfirm $PKGS
        ;;
    arch:update|manjaro:update)
        sudo pacman -Syu --noconfirm
        ;;
    arch:check|manjaro:check)
        for pkg in $PKGS; do
            if pacman -Q "$pkg" >/dev/null 2>&1; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # Alphine Actions
    alpine:install)
        sudo apk add $PKGS
        ;;
    alpine:uninstall)
        sudo apk del $PKGS
        ;;
    alpine:update)
        sudo apk update && sudo apk upgrade
        ;;
    alpine:check)
        for pkg in $PKGS; do
            if apk info | grep -q "^$pkg$"; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # Termux (Android) Actions
    termux:install)
        pkg update -y
        pkg install -y $PKGS
        ;;
    termux:uninstall)
        pkg uninstall -y $PKGS
        ;;
    termux:update)
        pkg update -y && pkg upgrade -y
        ;;
    termux:check)
        for pkg in $PKGS; do
            if pkg list-installed | grep -q "^$pkg"; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # macOS Actions
    macos:install)
        if ! command -v brew >/dev/null 2>&1; then
            echo "❌ Homebrew not found. Install it first:"
            echo '/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"'
            exit 1
        fi
        brew install $PKGS
        ;;
    macos:uninstall)
        brew uninstall $PKGS
        ;;
    macos:update)
        brew update && brew upgrade
        ;;
    macos:check)
        for pkg in $PKGS; do
            if brew list --formula | grep -q "^$pkg\$"; then
                echo "✅ $pkg is installed"
            else
                echo "❌ $pkg is NOT installed"
            fi
        done
        ;;

    # Unsupported Actions
    *)
        echo "❌ Unsupported action: $ACTION on $DISTRO"
        exit 1
        ;;
esac

echo "✅ Successfully completed $ACTION ${PKGS:+for: $PKGS}"
