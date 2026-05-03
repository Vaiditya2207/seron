#!/usr/bin/env bash
set -e

INSTALL_DIR="${SERON_INSTALL_DIR:-$HOME/.local/bin}"
REPO="https://github.com/Vaiditya2207/seron.git"
BUILD_DIR=$(mktemp -d)

# ── Colours ───────────────────────────────────────────────────────────────────
RED='\033[0;31m'; GREEN='\033[0;32m'; YELLOW='\033[1;33m'; BLUE='\033[0;34m'; NC='\033[0m'
info()    { echo -e "${BLUE}==>${NC} $*"; }
success() { echo -e "${GREEN}==>${NC} $*"; }
warn()    { echo -e "${YELLOW}Warning:${NC} $*"; }
die()     { echo -e "${RED}Error:${NC} $*" >&2; exit 1; }

# ── Distro detection ──────────────────────────────────────────────────────────
detect_distro() {
  if [ -f /etc/os-release ]; then
    . /etc/os-release
    echo "${ID}"
  elif command -v lsb_release &>/dev/null; then
    lsb_release -si | tr '[:upper:]' '[:lower:]'
  else
    die "Cannot detect distro. Please install dependencies manually and build with: cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DUSE_SYSTEM_CMARK_GFM=OFF -DUSE_SYSTEM_LAYER_SHELL=OFF -B build && cmake --build build"
  fi
}

# ── Dependency installation ───────────────────────────────────────────────────
install_deps_fedora() {
  info "Installing dependencies via dnf..."
  sudo dnf install -y \
    gcc-c++ cmake ninja-build git nodejs npm \
    qt6-qtbase-devel qt6-qtbase-private-devel qt6-qtsvg-devel \
    qt6-qtdeclarative-devel qt6-qtwayland-devel \
    protobuf-devel libqalculate-devel qtkeychain-qt6-devel \
    libicu-devel libsecret-devel minizip-ng-compat-devel \
    openssl-devel kf6-syntax-highlighting-devel \
    extra-cmake-modules wayland-protocols-devel ccache
}

install_deps_ubuntu() {
  info "Installing dependencies via apt..."
  sudo apt-get update -qq
  sudo apt-get install -y \
    build-essential cmake ninja-build git nodejs npm \
    qt6-base-dev qt6-base-private-dev libqt6svg6-dev \
    qt6-declarative-dev qt6-wayland-dev \
    libprotobuf-dev libqalculate-dev libqt6keychain1 qt6keychain-dev \
    libicu-dev libsecret-1-dev libminizip-dev \
    libssl-dev libkf6syntaxhighlighting-dev \
    extra-cmake-modules wayland-protocols libwayland-dev ccache \
    libxkbcommon-dev pkg-config
}

install_deps_arch() {
  info "Installing dependencies via pacman..."
  sudo pacman -Syu --noconfirm --needed \
    base-devel cmake ninja git nodejs npm \
    qt6-base qt6-svg qt6-declarative qt6-wayland \
    protobuf libqalculate qtkeychain-qt6 \
    icu libsecret minizip \
    openssl syntax-highlighting \
    extra-cmake-modules wayland-protocols ccache
}

install_deps_opensuse() {
  info "Installing dependencies via zypper..."
  sudo zypper install -y \
    gcc-c++ cmake ninja git nodejs npm \
    qt6-base-devel qt6-svg-devel qt6-declarative-devel qt6-wayland-devel \
    protobuf-devel libqalculate-devel qtkeychain-qt6-devel \
    libicu-devel libsecret-devel minizip-devel \
    libopenssl-devel kf6-syntax-highlighting-devel \
    extra-cmake-modules wayland-protocols-devel ccache \
    libxkbcommon-devel
}

# ── Main ──────────────────────────────────────────────────────────────────────
echo ""
echo -e "${BLUE}  ███████╗███████╗██████╗  ██████╗ ███╗   ██╗${NC}"
echo -e "${BLUE}  ██╔════╝██╔════╝██╔══██╗██╔═══██╗████╗  ██║${NC}"
echo -e "${BLUE}  ███████╗█████╗  ██████╔╝██║   ██║██╔██╗ ██║${NC}"
echo -e "${BLUE}  ╚════██║██╔══╝  ██╔══██╗██║   ██║██║╚██╗██║${NC}"
echo -e "${BLUE}  ███████║███████╗██║  ██║╚██████╔╝██║ ╚████║${NC}"
echo -e "${BLUE}  ╚══════╝╚══════╝╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝${NC}"
echo ""
info "Installing Seron — the command palette for Linux"
echo ""

DISTRO=$(detect_distro)
info "Detected distro: $DISTRO"

case "$DISTRO" in
  fedora|rhel|centos|almalinux|rocky) install_deps_fedora ;;
  ubuntu|debian|linuxmint|pop)        install_deps_ubuntu ;;
  arch|manjaro|endeavouros|garuda)    install_deps_arch   ;;
  opensuse*|sles)                     install_deps_opensuse ;;
  *)
    warn "Distro '$DISTRO' is not explicitly supported."
    warn "Trying Fedora-style install — if it fails, install deps manually."
    install_deps_fedora
    ;;
esac

# ── Clone & build ─────────────────────────────────────────────────────────────
info "Cloning Seron..."
git clone --depth=1 "$REPO" "$BUILD_DIR/seron"
cd "$BUILD_DIR/seron"

info "Configuring..."
cmake -G Ninja \
  -DCMAKE_BUILD_TYPE=Release \
  -DUSE_SYSTEM_CMARK_GFM=OFF \
  -DUSE_SYSTEM_LAYER_SHELL=OFF \
  -DCMAKE_INSTALL_PREFIX="$HOME/.local" \
  -B build

info "Building (grab a coffee, this takes a few minutes on first run)..."
cmake --build build

# ── Install ───────────────────────────────────────────────────────────────────
info "Installing binaries to $INSTALL_DIR..."
mkdir -p "$INSTALL_DIR"
find build/bin -maxdepth 1 -type f -executable | xargs -I{} cp {} "$INSTALL_DIR/"

# Ensure install dir is in PATH
if [[ ":$PATH:" != *":$INSTALL_DIR:"* ]]; then
  warn "$INSTALL_DIR is not in your PATH."
  echo "  Add this to your ~/.zshrc or ~/.bashrc:"
  echo "  export PATH=\"\$PATH:$INSTALL_DIR\""
fi

# ── Hyprland autostart ────────────────────────────────────────────────────────
HYPR_CONF="$HOME/.config/hypr/hyprland.conf"
if [ -f "$HYPR_CONF" ]; then
  if ! grep -q "seron server" "$HYPR_CONF"; then
    echo "" >> "$HYPR_CONF"
    echo "exec-once = $INSTALL_DIR/seron server" >> "$HYPR_CONF"
    success "Added seron server to Hyprland autostart"
  fi
  if ! grep -q "seron toggle" "$HYPR_CONF"; then
    echo "bindl = \$mod, Space, exec, $INSTALL_DIR/seron toggle" >> "$HYPR_CONF"
    success "Bound Super+Space to seron toggle in Hyprland"
  fi
fi

# ── Done ──────────────────────────────────────────────────────────────────────
echo ""
success "Seron installed successfully!"
echo ""
echo "  Start the server:  seron server &"
echo "  Toggle launcher:   seron toggle"
echo ""
if [ -f "$HYPR_CONF" ]; then
  echo "  Hyprland keybind added. Run: hyprctl reload"
else
  echo "  Add to your compositor config:"
  echo "    exec-once = $INSTALL_DIR/seron server"
  echo "    bindl = \$mod, Space, exec, $INSTALL_DIR/seron toggle"
fi
echo ""
warn "For paste support: sudo usermod -aG input \$USER  (then log out/in)"
echo ""
