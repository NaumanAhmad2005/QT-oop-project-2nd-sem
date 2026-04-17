# Building the Election Management System

This guide provides step-by-step instructions for building and running the Qt GUI application on Windows, macOS, and Linux.

## Prerequisites

### Qt Installation

#### Windows
1. Download Qt Online Installer from: https://www.qt.io/download-qt-installer
2. Run the installer and select:
   - Qt 6.x (latest stable version recommended)
   - MinGW 11.2.0 64-bit compiler (or MSVC if you have Visual Studio)
   - Qt Creator IDE
3. Complete the installation and restart your computer if prompted

#### macOS
1. Download Qt Online Installer from: https://www.qt.io/download-qt-installer
2. Run the installer and select:
   - Qt 6.x (latest stable version)
   - Clang 64-bit compiler
   - Qt Creator IDE

#### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-charts-dev qtcreator build-essential
```

#### Linux (Fedora/RHEL)
```bash
sudo dnf install qt6-qtbase-devel qt6-qtcharts-devel qtcreator gcc-c++
```

#### Linux (Arch)
```bash
sudo pacman -S qt6-base qt6-charts qtcreator base-devel
```

## Building the Project

### Method 1: Using Qt Creator (Recommended)

1. **Open Qt Creator**

2. **Open the project:**
   - File → Open File or Project...
   - Navigate to the project folder
   - Select `Election.pro`
   - Click "Open"

3. **Configure the kit:**
   - Qt Creator should auto-detect your Qt installation
   - Go to Tools → Options → Kits to verify
   - Ensure a desktop kit is selected (e.g., "Desktop Qt 6.x MinGW 64-bit")

4. **Build the project:**
   - Click the hammer icon (Build) or press `Ctrl+B` (Windows/Linux) / `Cmd+B` (macOS)
   - Wait for the build to complete

5. **Run the application:**
   - Click the green play button (Run) or press `Ctrl+R` (Windows/Linux) / `Cmd+R` (macOS)

### Method 2: Command Line

#### Windows (MinGW)
```bash
# Open Qt Creator Command Prompt or set up Qt environment
# Navigate to project directory
cd "path\to\QT OOP project"

# Run qmake
qmake Election.pro

# Build with mingw32-make
mingw32-make

# Run the application
debug\Election.exe
```

#### Windows (MSVC)
```cmd
# Open "Developer Command Prompt for Visual Studio"
cd "path\to\QT OOP project"

qmake Election.pro
nmake
```

#### macOS
```bash
cd "/path/to/QT OOP project"

# Run qmake
qmake Election.pro

# Build
make

# Run the application
open Election.app
# Or run from terminal:
./Election.app/Contents/MacOS/Election
```

#### Linux
```bash
cd "/path/to/QT OOP project"

# Run qmake
qmake Election.pro

# Build
make

# Run the application
./Election
```

## Build Output Locations

| Platform | Debug Build | Release Build |
|----------|-------------|---------------|
| Windows | `debug/Election.exe` | `release/Election.exe` |
| macOS | `Election.app` | `Election.app` |
| Linux | `Election` | `Election` |

## Creating a Release Build

### Qt Creator
1. Click the "Projects" button (left sidebar)
2. Select "Release" configuration
3. Click "Run CMake" or reconfigure
4. Build and run

### Command Line
```bash
# Windows
qmake Election.pro CONFIG+=release
mingw32-make

# macOS/Linux
qmake Election.pro CONFIG+=release
make
```

## Deploying the Application

### Windows
To create a standalone executable that can run without Qt installed:

```bash
# After building in Release mode
windeployqt release/Election.exe
```

This copies all required Qt DLLs to the release folder. You can then distribute the entire folder.

### macOS
```bash
# Create app bundle with dependencies
macdeployqt Election.app
```

### Linux
Create an AppImage or use linuxdeployqt:
```bash
# Install linuxdeployqt
wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
chmod +x linuxdeployqt-continuous-x86_64.AppImage
./linuxdeployqt-continuous-x86_64.AppImage Election
```

## Troubleshooting

### "Qt not found" or "QApplication not found"
- Ensure Qt is installed correctly
- Verify the kit is configured in Qt Creator
- On Linux, ensure `QT_PLUGIN_PATH` is set

### "Cannot find -lQt6Charts"
- Qt Charts module is not installed
- Install it via Qt Maintenance Tool or package manager

### Build fails with "ui_*.h: No such file"
- Clean the build: Build → Clean in Qt Creator
- Delete the `.ui` folder and rebuild

### Application crashes on startup
- Ensure all Qt DLLs are present (Windows)
- Check if the database file can be created in the build directory
- Run from terminal to see error messages

### Database errors
- The application creates `project.db` in the build directory
- Ensure write permissions in the build folder
- Delete `project.db` and restart to recreate

## Quick Start Summary

```bash
# 1. Install Qt 6.x
# 2. Open Election.pro in Qt Creator
# 3. Select your desktop kit
# 4. Click Build (hammer icon)
# 5. Click Run (play button)
```

For additional help, see the [README.md](README.md) or open an issue on GitHub.
