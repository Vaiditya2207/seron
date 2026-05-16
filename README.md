# Seron

A fast, native command palette launcher for Linux — inspired by Raycast.

## Features

- App launcher with fuzzy search
- Calculator with unit & currency conversion
- Clipboard history
- File search
- Extension ecosystem (Raycast-compatible API)
- Native Wayland / layer shell support

## Install

### One-line install (Fedora — x86_64 & ARM64)

```bash
curl -fsSL https://raw.githubusercontent.com/Vaiditya2207/seron/main/scripts/install.sh | bash
```

### Manual build

**Dependencies (Fedora):**

```bash
sudo dnf install -y gcc-c++ cmake ninja-build git nodejs npm \
  qt6-qtbase-devel qt6-qtbase-private-devel qt6-qtsvg-devel \
  qt6-qtdeclarative-devel qt6-qtwayland-devel \
  protobuf-devel libqalculate-devel qtkeychain-qt6-devel \
  libicu-devel libsecret-devel minizip-ng-compat-devel \
  openssl-devel kf6-syntax-highlighting-devel \
  extra-cmake-modules wayland-protocols-devel ccache
```

**Build:**

```bash
git clone git@github.com:Vaiditya2207/seron.git && cd seron
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DUSE_SYSTEM_CMARK_GFM=OFF \
  -DUSE_SYSTEM_LAYER_SHELL=OFF \
  -B build
cmake --build build
sudo cmake --install build
```

## Usage

Start the server:

```bash
seron server &
```

Toggle the window:

```bash
seron toggle
```

**Recommended keybind (Hyprland):**

```
bindl = $mod, Space, exec, seron toggle
```

## Paste support

```bash
sudo usermod -aG input $USER
```

Log out and back in after.

## License

Not Decided Yet.
