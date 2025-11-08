# Typst Preview Native Webview

A lightweight C++ binary that opens Typst preview in a native WebKitGTK window instead of a full browser.

## Dependencies

- GTK+ 3.0
- WebKit2GTK 4.0

### Install dependencies (Ubuntu/Debian)
```bash
sudo apt-get install libgtk-3-dev libwebkit2gtk-4.0-dev
```

### Install dependencies (Fedora)
```bash
sudo dnf install gtk3-devel webkit2gtk3-devel
```

### Install dependencies (Arch)
```bash
sudo pacman -S gtk3 webkit2gtk
```

## Building

```bash
make
```

This creates the `typstview` binary.

## Usage

```bash
./typstview http://127.0.0.1:23625
```

## Integration with typst-preview.nvim

The Neovim plugin will automatically use this binary when available instead of opening a browser.
