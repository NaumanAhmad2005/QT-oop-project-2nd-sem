#ifndef USERMANAGER_H
#define USERMANAGER_H
#include "databasemanager.h"
#include <QSqlQuery>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "QString"
#include <QMessageBox>
using namespace std;
struct Candidate {
    string candidateId;
    string candidateName;
    string candidateParty;
    string electionId;
    int votes;

    Candidate() {
        candidateId = "";
        candidateName = "";
        candidateParty = "";
        electionId = "";
        votes = 0;
    }
};
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

    virtual ~User() {} // Add virtual destructor for proper cleanup of derived classes

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
    vector<string> votedElections; // Using vector instead of fixed size array
    int maxElections; // Maximum number of elections a voter can vote in

public:
    Voter(const string& username, const string& password, const string& userId,
          const string& name = "", const string& address = "")
        : User(username, password, userId) {
        voterName = name;
        voterAddress = address;
        this->maxElections = 10; // Assuming a voter can participate in maximum 10 elections
    }

    const string& getVoterName() const {
        return voterName;
    }

    void displayMenu() override {
        cout << "\n===== Voter Menu =====\n";
        cout << "1. View Available Elections\n";
        cout << "2. Cast Vote\n";
        cout << "3. View Vote Status\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
    }

    bool hasVotedInElection(const string& electionId) {
        for (const string& votedElection : votedElections) {
            if (votedElection == electionId) {
                return true;
            }
        }
        return false;
    }

    void recordVote(const string& electionId) {
        if (votedElections.size() < maxElections) {
            votedElections.push_back(electionId);
        } else {
            cout << "Maximum election limit reached!" << endl;
        }
    }

    void viewVoteStatus() {
        cout << "\n===== Your Voting History =====\n";
        if (votedElections.empty()) {
            cout << "You have not voted in any elections yet.\n";
        } else {
            cout << "You have voted in the following elections:\n";
            for (size_t i = 0; i < votedElections.size(); i++) {
                cout << i+1 << ". Election ID: " << votedElections[i] << endl;
            }
        }
    }

    void viewAvailableElections() {
        ifstream electionFile("elections.txt");

        if (!electionFile.is_open()) {
            cout << "No elections are currently available." << endl;
            return;
        }

        string id, name, type, status;
        cout << "\n===== Available Elections =====\n";
        int count = 0;

        while (getline(electionFile, id)) {
            if (!getline(electionFile, name)) break;
            if (!getline(electionFile, type)) break;
            if (!getline(electionFile, status)) break;

            if (status == "active") {
                count++;
                cout << count << ". ID: " << id << " - " << name << " (" << type << ")" << endl;

                // Check if voter has already voted in this election
                if (hasVotedInElection(id)) {
                    cout << "   [You have already voted in this election]" << endl;
                }
            }
        }

        if (count == 0) {
            cout << "No active elections available at the moment." << endl;
        }

        electionFile.close();
    }

    void castVote() {

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
        // Hard-coded admin credentials
        if (username == "admin" && password == "admin123") {
            currentUser = new Administrator(username, password, "admin1", "Administrator", "SuperAdmin");
            currentUser->setLoginStatus(true); // Explicitly set login status to true
            return true;
        }

        return false;
    }

    bool authenticateVoter(QString username, QString password) {
        // ifstream voterFile("voter.txt");
        // if (!voterFile.is_open()) {
        //     cout << "Voter file could not be opened!" << endl;
        //     return false;
        // }

        // string fileUsername, filePassword;
        // while (getline(voterFile, fileUsername)) {
        //     if (!getline(voterFile, filePassword)) {
        //         break; // If we can't read a password, file format is wrong
        //     }

        //     if (username == fileUsername && password == filePassword) {
        //         voterFile.close();
        //         // Create voter with a unique ID (using username for simplicity)
        //         currentUser = new Voter(username, password, username, username, "");
        //         currentUser->setLoginStatus(true); // Explicitly set login status to true
        //         return true;
        //     }
        // }

        // voterFile.close();
        // return false;
        // if (!DatabaseManager::instance().connect()) {
        //     return false;
        // }



        QSqlQuery query(DatabaseManager::instance().getDatabase());
        query.prepare("SELECT * FROM voters WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);

        if (query.exec() && query.next()) {
            return true;
        }
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

#endif // USERMANAGER_H
