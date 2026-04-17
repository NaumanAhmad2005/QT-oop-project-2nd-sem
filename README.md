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
├── docs/                # Documentation
├── Election.pro         # Qt project file
└── README.md            # This file
```

## Prerequisites

- Qt 6.x (tested with Qt 6.9.0)
- C++17 compatible compiler
- qmake or Qt Creator

## Building the Project

### Using Qt Creator

1. Open `Election.pro` in Qt Creator
2. Select your kit (Desktop Qt 6.x MinGW 64-bit recommended)
3. Click **Build** → **Run**

### Using Command Line

```bash
qmake Election.pro
make
```

## Running the Application

After building, run the executable:

- **Windows:** `build/.../debug/Election.exe`
- **Linux/Mac:** `./Election`

## Default Credentials

The application uses a SQLite database for user management. Admin credentials are set up during initial database creation.

## Database

The application uses SQLite (`project.db`) located in the build directory. The database stores:

- User accounts (admins and voters)
- Election data
- Candidate information
- Vote records

## Screenshots

Add screenshots of the main windows here:
- Main login screen
- Admin dashboard
- Voter interface
- Results view

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
