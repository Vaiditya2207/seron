#!/usr/bin/env bash
set -e

INSTALL_DIR="$HOME/.local/bin"
REPO="https://github.com/Vaiditya2207/seron.git"

echo "==> Installing Seron..."

# Detect distro
if [ -f /etc/fedora-release ]; then
  DISTRO="fedora"
else
  echo "Only Fedora is supported by this script for now. Please build manually."
  exit 1
fi

# Install dependencies
echo "==> Installing dependencies..."
sudo dnf install -y gcc-c++ cmake ninja-build git nodejs npm \
  qt6-qtbase-devel qt6-qtbase-private-devel qt6-qtsvg-devel \
  qt6-qtdeclarative-devel qt6-qtwayland-devel \
  protobuf-devel libqalculate-devel qtkeychain-qt6-devel \
  libicu-devel libsecret-devel minizip-ng-compat-devel \
  openssl-devel kf6-syntax-highlighting-devel \
  extra-cmake-modules wayland-protocols-devel ccache

# Clone
BUILD_DIR=$(mktemp -d)
echo "==> Cloning Seron into $BUILD_DIR..."
git clone --depth=1 "$REPO" "$BUILD_DIR/seron"
cd "$BUILD_DIR/seron"

# Configure
echo "==> Configuring..."
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DUSE_SYSTEM_CMARK_GFM=OFF \
  -DUSE_SYSTEM_LAYER_SHELL=OFF \
  -DCMAKE_INSTALL_PREFIX="$HOME/.local" \
  -B build

# Build
echo "==> Building (this takes a few minutes)..."
cmake --build build

# Install binaries
echo "==> Installing to $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"
cp build/bin/seron build/bin/seron-server build/bin/seron-* "$INSTALL_DIR/" 2>/dev/null || true

# Autostart for Hyprland
HYPR_CONF="$HOME/.config/hypr/hyprland.conf"
if [ -f "$HYPR_CONF" ] && ! grep -q "seron server" "$HYPR_CONF"; then
  echo "" >> "$HYPR_CONF"
  echo "exec-once = $INSTALL_DIR/seron server" >> "$HYPR_CONF"
  echo "==> Added seron server to Hyprland autostart"
fi

echo ""
echo "==> Seron installed! Add this to your Hyprland config:"
echo "    bindl = \$mod, Space, exec, $INSTALL_DIR/seron toggle"
echo ""
echo "    Then run: hyprctl reload && $INSTALL_DIR/seron server &"
