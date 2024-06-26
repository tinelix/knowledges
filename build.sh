#!/bin/bash

echo "Building Tinelix Knowledges..."

OUT_FILE=""
OUT_DIR="out"

if [[ $OSTYPE == "linux-gnu" ]]; then
    OUT_FILE=${OUT_DIR}/linux/knowledges
    mkdir -p ./${OUT_DIR}/linux
    echo "Your OS: GNU/Linux"
    echo
    if [ -x "$(command -v apt)" ]; then         # <-- for Ubuntu/Debian/derivatives
        su -c "apt install -y libncurses-dev"
    elif [ -x "$(command -v yum)" ]; then       # <-- for Fedora/CentOS/AltLinux/derivatives
        su -c "yum install ncurses-devel"
    elif [ -x "$(command -v pacman)" ]; then    # <-- for Arch/Artix/Manjaro/derivatives
        su -c "pacman -S ncurses"
    else
        echo "ERROR: Your package manager is not supported"
        echo
        exit 1
    fi
elif [ $OSTYPE == "cygwin" ]; then
    OUT_FILE=${OUT_DIR}/windows-mingw64/knowledges
    mkdir -p ./${OUT_DIR}/windows-mingw64
    echo "Your OS: Cygwin/Windows"
    echo
    if [ -x "$(command -v apt-cyg)" ]; then
        apt-cyg install libncursesw-devel
    else
        echo "ERROR: 'apt-cyg' not found"
        echo
        echo "Possible solutions to the problem:"
        echo "* Install the 'gnutls-devel' and 'libncursesw-devel' packages" \
        "in the Cygwin installer"
        echo "* Download 'apt-cyg' package manager from" \
        "https://github.com/transcode-open/apt-cyg"
        echo "* Enter 'make' if all required packages have already been" \
        "installed."
        exit 1
    fi
elif [[ $OSTYPE == "msys" ]]; then
    OUT_FILE=${OUT_DIR}/windows-mingw64/knowledges
    mkdir -p ./${OUT_DIR}/windows-mingw64
    echo "Your OS: MSYS2/Windows"
    echo
    pacman -S mingw-w64-{i686,x86_64}-ncurses
else
    echo "ERROR: Your OS is not supported"
    echo
    exit 1
fi

make standalone

echo
echo "Build completed!"
echo
echo "Run './${OUT_FILE}' for testing, 'gdb ./${OUT_FILE}' + 'r' for debug"
cd ./out
