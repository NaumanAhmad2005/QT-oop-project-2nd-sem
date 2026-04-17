# Deployment Guide

This guide explains how to package your Qt Election application for distribution to users who don't have Qt installed.

## Windows Deployment

### Using windeployqt

1. **Build in Release mode:**
   ```bash
   qmake Election.pro CONFIG+=release
   mingw32-make
   ```

2. **Deploy Qt libraries:**
   ```bash
   # Find windeployqt in your Qt installation
   # Typically: C:\Qt\Tools\QtCreator\bin\windeployqt.exe
   # Or: C:\Qt\6.x\mingw_64\bin\windeployqt.exe
   
   windeployqt release\Election.exe
   ```

3. **Test the deployment:**
   - Copy the entire `release` folder to a machine without Qt
   - Run `Election.exe` to verify it works

4. **Create installer (optional):**
   - Use [Inno Setup](https://jrsoftware.org/isdl.php) (free)
   - Use [NSIS](https://nsis.sourceforge.io/) (free)
   - Use InstallShield for commercial projects

### Creating a Windows Icon

1. Create a 256x256 PNG icon
2. Convert to `.ico` format using [icoconvert.com](https://www.icoconvert.com/)
3. Add to `resources.qrc`
4. For `.exe` embedding, use [Resource Hacker](http://www.angusj.com/resourcehacker/)

## macOS Deployment

### Using macdeployqt

1. **Build in Release mode:**
   ```bash
   qmake Election.pro CONFIG+=release
   make
   ```

2. **Deploy Qt frameworks:**
   ```bash
   # Find macdeployqt in your Qt installation
   # Typically: /Users/username/Qt/6.x/clang_64/bin/macdeployqt
   
   macdeployqt Election.app
   ```

3. **Code signing (for distribution):**
   ```bash
   # Sign the application
   codesign --deep --force --sign "Developer ID Application: Your Name" Election.app
   
   # Create a DMG
   macdeployqt Election.app -dmg
   ```

4. **Notarization (required for Catalina+):**
   ```bash
   xcrun notarytool submit Election.app --apple-id "your@email.com" --password "app-password" --team-id "YOUR_TEAM_ID"
   ```

## Linux Deployment

### Option 1: AppImage (Recommended)

AppImage works on most Linux distributions without installation.

1. **Install linuxdeployqt:**
   ```bash
   wget https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage
   chmod +x linuxdeployqt-continuous-x86_64.AppImage
   ```

2. **Build your application:**
   ```bash
   qmake Election.pro CONFIG+=release
   make
   ```

3. **Create AppImage:**
   ```bash
   # Copy your executable to a folder with a name
   mkdir AppDir
   cp Election AppDir/
   cp -r resources AppDir/
   
   # Create desktop file
   cat > AppDir/Election.desktop << EOF
   [Desktop Entry]
   Type=Application
   Name=Election Management System
   Exec=Election
   Icon=app_icon
   Categories=Utility;
   EOF
   
   # Create the AppImage
   ./linuxdeployqt-continuous-x86_64.AppImage AppDir/Election.desktop -appimage
   ```

### Option 2: Native Package

#### Ubuntu/Debian (.deb)

Create a `debian/` folder with control files, then use `debuild`.

#### Fedora/RHEL (.rpm)

Create a `.spec` file and use `rpmbuild`.

## Distribution Checklist

Before distributing your application:

- [ ] Build in Release mode
- [ ] Run deployment tool (windeployqt/macdeployqt/linuxdeployqt)
- [ ] Test on a clean machine without Qt installed
- [ ] Include LICENSE file
- [ ] Include README with basic instructions
- [ ] Test all features work correctly
- [ ] Verify database is created in correct location
- [ ] Check that all UI elements display properly

## Database Location

By default, the database is created in the build directory. For production:

1. Consider using application data directory:
   - Windows: `%APPDATA%/Election/`
   - macOS: `~/Library/Application Support/Election/`
   - Linux: `~/.local/share/Election/`

2. Modify `databasemanager.cpp` to use:
   ```cpp
   QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
   QDir().mkpath(dbPath);
   QString dbFile = dbPath + "/project.db";
   ```

## Version Information

Add version info to `Election.pro`:

```qmake
VERSION = 1.0.0
QMAKE_APP_VERSION = $$VERSION

# Windows version info
win32 {
    RC_FILE = resources/election.rc
}
```

## Support

For issues with deployment:
- Check Qt documentation: https://doc.qt.io/
- Qt Forums: https://forum.qt.io/
- Open an issue on the GitHub repository
