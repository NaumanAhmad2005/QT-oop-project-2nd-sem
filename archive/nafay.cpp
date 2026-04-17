#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Base User class
class User {
protected:
    string username;
    string password;
    string userId;
    bool isLoggedIn;

public:
    User(string username, string password, string userId) {
        this->username = username;
        this->password = password;
        this->userId = userId;
        this->isLoggedIn = false;
    }

    bool login(string username, string password) {
        if (this->username == username && this->password == password) {
            isLoggedIn = true;
            return true;
        }
        return false;
    }

    void logout() {
        isLoggedIn = false;
    }

    string getUserId() {
        return userId;
    }

    string getUsername() {
        return username;
    }

    bool getLoginStatus() {
        return isLoggedIn;
    }

    void setLoginStatus(bool status) {
        isLoggedIn = status;
    }

    virtual void displayMenu() = 0; // Pure virtual function
};

// Voter class derived from User
class Voter : public User {
private:
    string voterName;
    string voterAddress;
    string* votedElections; // Array of election IDs the voter has voted in
    int votedElectionsCount; // Number of elections voted in
    int maxElections; // Maximum number of elections a voter can vote in

public:
    Voter(string username, string password, string userId, string name = "", string address = "") 
        : User(username, password, userId) {
        this->voterName = name;
        this->voterAddress = address;
        this->maxElections = 10; // Assuming a voter can participate in maximum 10 elections
        this->votedElections = new string[maxElections];
        this->votedElectionsCount = 0;
    }

    ~Voter() {
        delete[] votedElections;
    }

    void displayMenu() override {
        cout << "\n===== Voter Menu =====\n";
        cout << "1. View Available Elections\n";
        cout << "2. Cast Vote\n";
        cout << "3. View Vote Status\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
    }

    bool hasVotedInElection(string electionId) {
        for (int i = 0; i < votedElectionsCount; i++) {
            if (votedElections[i] == electionId) {
                return true;
            }
        }
        return false;
    }

    void recordVote(string electionId) {
        if (votedElectionsCount < maxElections) {
            votedElections[votedElectionsCount++] = electionId;
        } else {
            cout << "Maximum election limit reached!" << endl;
        }
    }

    void viewVoteStatus() {
        cout << "\n===== Your Voting History =====\n";
        if (votedElectionsCount == 0) {
            cout << "You have not voted in any elections yet.\n";
        } else {
            cout << "You have voted in the following elections:\n";
            for (int i = 0; i < votedElectionsCount; i++) {
                cout << i+1 << ". Election ID: " << votedElections[i] << endl;
            }
        }
    }
};

// Administrator class derived from User
class Administrator : public User {
private:
    string adminName;
    string adminRole;

public:
    Administrator(string username, string password, string userId, string name = "", string role = "")
        : User(username, password, userId) {
        this->adminName = name;
        this->adminRole = role;
    }

    void displayMenu() override {
        cout << "\n===== Administrator Menu =====\n";
        cout << "1. Create Election\n";
        cout << "2. Add Candidate\n";
        cout << "3. View Election Results\n";
        cout << "4. List All Voters\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
    }

    void addCandidate() {
        string candidateId, candidateName, candidateParty, electionId;
        
        cout << "Enter Election ID: ";
        cin >> electionId;
        cout << "Enter Candidate ID: ";
        cin >> candidateId;
        cout << "Enter Candidate Name: ";
        cin.ignore();
        getline(cin, candidateName);
        cout << "Enter Party Affiliation: ";
        getline(cin, candidateParty);
        
        // Save candidate to file
        ofstream candidateFile("candidate.txt", ios::app);
        if (candidateFile.is_open()) {
            candidateFile << electionId << endl;
            candidateFile << candidateId << endl;
            candidateFile << candidateName << endl;
            candidateFile << candidateParty << endl;
            candidateFile.close();
            cout << "Candidate added successfully!" << endl;
        } else {
            cout << "Unable to open candidate file!" << endl;
        }
    }
};

// UserManager class to handle authentication and user management
class UserManager {
private:
    User* currentUser;

public:
    UserManager() {
        currentUser = nullptr;
    }

    ~UserManager() {
        if (currentUser != nullptr) {
            delete currentUser;
        }
    }

    bool authenticateAdmin(string username, string password) {
        ifstream adminFile("admin.txt");
        if (!adminFile.is_open()) {
            cout << "Admin file could not be opened!" << endl;
            return false;
        }
        
        string fileUsername, filePassword;
        getline(adminFile, fileUsername);
        getline(adminFile, filePassword);
        
        adminFile.close();
        
        if (username == fileUsername && password == filePassword) {
            currentUser = new Administrator(username, password, "admin1", "Administrator", "SuperAdmin");
            currentUser->setLoginStatus(true); // Explicitly set login status to true
            return true;
        }
        
        return false;
    }

    bool authenticateVoter(string username, string password) {
        ifstream voterFile("voter.txt");
        if (!voterFile.is_open()) {
            cout << "Voter file could not be opened!" << endl;
            return false;
        }
        
        string fileUsername, filePassword;
        while (getline(voterFile, fileUsername)) {
            if (!getline(voterFile, filePassword)) {
                break; // If we can't read a password, file format is wrong
            }
            
            if (username == fileUsername && password == filePassword) {
                voterFile.close();
                // Create voter with a unique ID (using username for simplicity)
                currentUser = new Voter(username, password, username, username, "");
                currentUser->setLoginStatus(true); // Explicitly set login status to true
                return true;
            }
        }
        
        voterFile.close();
        return false;
    }

    User* getCurrentUser() {
        return currentUser;
    }
    
    void logout() {
        if (currentUser != nullptr) {
            currentUser->logout();
            delete currentUser;
            currentUser = nullptr;
        }
    }
};

// Main function to demonstrate user authentication
int main() {
    UserManager userManager;
    string userType, username, password;
    int choice;
    
    cout << "Welcome to Online Voting System" << endl;
    cout << "Are you an admin or a voter? (admin/voter): ";
    cin >> userType;
    
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    
    bool loginSuccess = false;
    
    if (userType == "admin") {
        loginSuccess = userManager.authenticateAdmin(username, password);
        if (loginSuccess) {
            cout << "Admin login successful!" << endl;
            
            // Cast to Administrator to access specific methods
            Administrator* admin = dynamic_cast<Administrator*>(userManager.getCurrentUser());
            
            bool continueLoop = true;
            while (continueLoop && admin != nullptr && admin->getLoginStatus()) {
                admin->displayMenu();
                cin >> choice;
                
                switch (choice) {
                    case 1:
                        cout << "Create Election functionality will be implemented in Election Management part" << endl;
                        break;
                    case 2:
                        admin->addCandidate();
                        break;
                    case 3:
                        cout << "View Election Results functionality will be implemented in Election Management part" << endl;
                        break;
                    case 4:
                        cout << "List All Voters functionality will be implemented in Voting System part" << endl;
                        break;
                    case 5:
                        cout << "Logging out..." << endl;
                        userManager.logout();
                        continueLoop = false;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            }
        } else {
            cout << "Admin login failed!" << endl;
        }
    } else if (userType == "voter") {
        loginSuccess = userManager.authenticateVoter(username, password);
        if (loginSuccess) {
            cout << "Voter login successful!" << endl;
            
            // Cast to Voter to access specific methods
            Voter* voter = dynamic_cast<Voter*>(userManager.getCurrentUser());
            
            bool continueLoop = true;
            while (continueLoop && voter != nullptr && voter->getLoginStatus()) {
                voter->displayMenu();
                cin >> choice;
                
                switch (choice) {
                    case 1:
                        cout << "View Available Elections functionality will be implemented in Election Management part" << endl;
                        break;
                    case 2:
                        cout << "Cast Vote functionality will be implemented in Voting System part" << endl;
                        break;
                    case 3:
                        voter->viewVoteStatus();
                        break;
                    case 4:
                        cout << "Logging out..." << endl;
                        userManager.logout();
                        continueLoop = false;
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                }
            }
        } else {
            cout << "Voter login failed!" << endl;
        }
    } else {
        cout << "Invalid user type!" << endl;
    }
    
    cout << "Thank you for using Online Voting System" << endl;
    
    return 0;
}