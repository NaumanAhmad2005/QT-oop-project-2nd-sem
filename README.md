# Election Management System

A desktop application built with Qt for managing elections, voters, and candidates.

## Features

- **User Authentication**
  - Admin login with full system access
  - Voter login with restricted access

- **Admin Features**
  - Create and manage elections
  - Add and manage voters
  - Create and manage candidates
  - View election results

- **Voter Features**
  - Browse available elections
  - Cast votes securely
  - View results after elections close

## Tech Stack

- **Framework:** Qt 6
- **Language:** C++17
- **Database:** SQLite
- **UI:** Qt Widgets

## Project Structure

```
.
├── src/                 # Source files (.cpp)
├── include/             # Header files (.h)
├── ui/                  # Qt Designer forms (.ui)
├── resources/           # Application resources (icons, images)
├── docs/                # Documentation (reports, rubrics)
├── Election.pro         # Qt project file
├── resources.qrc        # Qt resource collection
├── README.md            # This file
├── BUILDING.md          # Detailed build instructions
├── DEPLOYMENT.md        # Distribution guide
└── LICENSE              # MIT License
```

## Prerequisites

- **Qt 6.x** (Qt 6.5 or later recommended)
- **C++17** compatible compiler
- **Qt Creator** IDE (recommended) or qmake command-line tool

### Installing Qt

| Platform | Installation |
|----------|--------------|
| Windows | [Qt Online Installer](https://www.qt.io/download-qt-installer) - Select MinGW 64-bit |
| macOS | [Qt Online Installer](https://www.qt.io/download-qt-installer) - Select Clang 64-bit |
| Linux (Ubuntu) | `sudo apt install qt6-base-dev qt6-charts-dev qtcreator` |
| Linux (Fedora) | `sudo dnf install qt6-qtbase-devel qt6-qtcharts-devel qtcreator` |

## Building & Running

### Quick Start (Qt Creator)

1. Open Qt Creator → **File** → **Open Project** → Select `Election.pro`
2. Select your desktop kit
3. Click **Build** (hammer) then **Run** (play)

For detailed platform-specific instructions, see [BUILDING.md](BUILDING.md).

## Default Credentials

The application uses a SQLite database (`project.db`) created on first run in the build directory.

> **Note:** Default admin credentials are set during initial database creation. Check with the project author or examine `databasemanager.cpp` for default login details.

## Database

The application uses SQLite (`project.db`) created automatically in the build directory. The database stores:

- User accounts (admins and voters)
- Election data
- Candidate information
- Vote records

To reset the database, delete `project.db` from the build folder and restart the application.

## Screenshots

> Screenshots coming soon. The application features:
> - Main login screen (admin/voter selection)
> - Admin dashboard for managing elections, voters, and candidates
> - Voter interface for browsing and voting in elections
> - Results view for viewing election outcomes

## Development

### Key Classes

| Class | Description |
|-------|-------------|
| `MainWindow` | Main application window |
| `AdminLogin` | Admin authentication |
| `AdminFunctionality` | Admin dashboard and operations |
| `VoterLogin` | Voter authentication |
| `VoterFunctionality` | Voter dashboard and voting |
| `DatabaseManager` | SQLite database operations |
| `UserManager` | User account management |

## License

This project is created as part of an OOP (Object-Oriented Programming) course.
See [LICENSE](LICENSE) for details.

## Contributors

- naumanf25

## Contact

For questions or issues, please open an issue on GitHub.

## Documentation

| File | Description |
|------|-------------|
| [README.md](README.md) | Project overview and quick start |
| [BUILDING.md](BUILDING.md) | Detailed build instructions for all platforms |
| [DEPLOYMENT.md](DEPLOYMENT.md) | Guide for distributing the application |
| [LICENSE](LICENSE) | MIT License terms |
