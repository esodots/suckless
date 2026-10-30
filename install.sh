#!/bin/sh
# Build dwm, slstatus and st and install them, with the bar scripts, into
# PREFIX (default ~/.local, so no root needed). Usage: ./install.sh [PREFIX]
set -e
PREFIX=${1:-$HOME/.local}
cd "$(dirname "$0")"
for d in dwm slstatus st; do
    make -C "$d" clean
    make -C "$d"
    make -C "$d" PREFIX="$PREFIX" install
done
mkdir -p "$PREFIX/bin"
cp bin/* "$PREFIX/bin/"
echo "installed into $PREFIX/bin - make sure it is on PATH (see xinitrc)"
