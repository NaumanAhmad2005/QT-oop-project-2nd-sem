#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Base User class
class User
{
protected:
    string username;
    string password;
    string userId;
    bool isLoggedIn;

public:
    User(string username, string password, string userId)
    {
        this->username = username;
        this->password = password;
        this->userId = userId;
        this->isLoggedIn = false;
    }

    bool login(string username, string password)
    {
        if (this->username == username && this->password == password)
        {
            isLoggedIn = true;
            return true;
        }
        return false;
    }

    void logout()
    {
        isLoggedIn = false;
    }

    string getUserId()
    {
        return userId;
    }

    string getUsername()
    {
        return username;
    }

    bool getLoginStatus()
    {
        return isLoggedIn;
    }

    string getPassword()
    {
        return password;
    }

    void setLoginStatus(bool status)
    {
        isLoggedIn = status;
    }

    virtual void displayMenu() = 0; // Pure virtual function
};

// election class
class Election
{
private:
    string electionId;
    string electionName;
    string electionType; // "National" or "Local"
    bool isActive;

public:
    // Default constructor
    Election() : electionId(""), electionName(""), electionType(""), isActive(false) {}

    // Parameterized constructor
    Election(string id, string name, string type) : electionId(id), electionName(name), electionType(type), isActive(true) {}

    string getElectionId()
    {
        return electionId;
    }

    string getElectionType()
    {
        return electionType;
    }

    bool getIsActive()
    {
        return isActive;
    }

    void setIsActive(bool active)
    {
        isActive = active;
    }
    void display()
    {
        cout << "Election ID: " << electionId << endl;
        cout << "Election Name: " << electionName << endl;
        cout << "Election Type: " << electionType << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    }
};

// Voter class derived from User
class Voter : public User
{
private:
    string voterName;
    string voterAddress;
    string *votedElections;  // Array of election IDs the voter has voted in
    int votedElectionsCount; // Number of elections voted in
    int maxElections;        // Maximum number of elections a voter can vote in

public:
    Voter(string username, string password, string userId, string name = "", string address = "")
        : User(username, password, userId)
    {
        this->voterName = name;
        this->voterAddress = address;
        this->maxElections = 10; // Assuming a voter can participate in maximum 10 elections
        this->votedElections = new string[maxElections];
        this->votedElectionsCount = 0;
    }

    ~Voter()
    {
        delete[] votedElections;
    }

    void displayMenu() override
    {
        cout << "\n===== Voter Menu =====\n";
        cout << "1. View Available Elections\n";
        cout << "2. Cast Vote\n";
        cout << "3. View Vote Status\n";
        cout << "4. Logout\n";
        cout << "Enter your choice: ";
    }

    bool hasVotedInElection(string electionId)
    {
        for (int i = 0; i < votedElectionsCount; i++)
        {
            if (votedElections[i] == electionId)
            {
                return true;
            }
        }
        return false;
    }

    void recordVote(string electionId)
    {
        if (votedElectionsCount < maxElections)
        {
            votedElections[votedElectionsCount++] = electionId;
        }
        else
        {
            cout << "Maximum election limit reached!" << endl;
        }
    }

    void viewVoteStatus()
    {
        cout << "\n===== Your Voting History =====\n";
        if (votedElectionsCount == 0)
        {
            cout << "You have not voted in any elections yet.\n";
        }
        else
        {
            cout << "You have voted in the following elections:\n";
            for (int i = 0; i < votedElectionsCount; i++)
            {
                cout << i + 1 << ". Election ID: " << votedElections[i] << endl;
            }
        }
    }
};

// Administrator class derived from User
class Administrator : public User
{
private:
    string adminName;
    string adminRole;
    Election elections[10]; // Array to store up to 10 elections
    int electionCount;

public:
    Administrator(string username, string password, string userId, string name = "", string role = "")
        : User(username, password, userId)
    {
        this->adminName = name;
        this->adminRole = role;
        this->electionCount = 0;
    }

    void displayMenu() override
    {
        cout << "\n===== Administrator Menu =====" << endl;
        cout << "1. Create Election" << endl;
        cout << "2. Add Candidate" << endl;
        cout << "3. Add Voter" << endl;
        cout << "4. View Election Results" << endl;
        cout << "5. List All Voters" << endl;
        cout << "6. Logout" << endl;
        cout << "Enter your choice: ";
    }

    void addCandidate()
    {
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
        if (candidateFile.is_open())
        {
            candidateFile << electionId << endl;
            candidateFile << candidateId << endl;
            candidateFile << candidateName << endl;
            candidateFile << candidateParty << endl;
            candidateFile.close();
            cout << "Candidate added successfully!" << endl;
        }
        else
        {
            cout << "Unable to open candidate file!" << endl;
        }
    }

    void addVoter()
    {
        string CNIC, Name, address, username, password;

        cout << "Enter CNIC: ";
        cin >> CNIC;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, Name);
        cout << "Enter address: ";
        getline(cin, address);
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Save voter to file
        ofstream voterFile("voter.txt", ios::app);
        if (voterFile.is_open())
        {
            voterFile << username << endl;
            voterFile << password << endl;
            voterFile << CNIC << endl;
            voterFile << Name << endl;
            voterFile << address << endl;
            voterFile.close();
            cout << "Voter added successfully!" << endl;
        }
        else
        {
            cout << "Unable to open Voter file!" << endl;
        }
    }

    void createElection()
    {
        if (electionCount >= 10)
        {
            cout << "Maximum election limit reached!" << endl;
            return;
        }

        int choice;
        string electionId, electionName;

        cout << "Enter Election ID: ";
        cin >> electionId;
        cout << "Enter Election Name: ";
        cin.ignore();
        getline(cin, electionName);

        cout << "Select Election Type:" << endl;
        cout << "1. National Election" << endl;
        cout << "2. Local Election" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        string electionType;
        if (choice == 1)
        {
            electionType = "National";
        }
        else if (choice == 2)
        {
            electionType = "Local";
        }
        else
        {
            cout << "Invalid choice. Election creation canceled." << endl;
            return;
        }

        // Create new election and add to array
        elections[electionCount] = Election(electionId, electionName, electionType);
        electionCount++;

        // Save election to file
        ofstream electionFile("elections.txt", ios::app);
        if (electionFile.is_open())
        {
            electionFile << electionId << endl;
            electionFile << electionName << endl;
            electionFile << electionType << endl;
            electionFile << "active" << endl; // Status
            electionFile.close();
            cout << "Election created successfully!" << endl;
        }
        else
        {
            cout << "Unable to open elections file!" << endl;
        }
    }

    void viewElectionResults()
    {
        string electionId;
        cout << "Enter Election ID to view results: ";
        cin >> electionId;

        // This is a placeholder. In a full implementation, this would
        // read from a votes file and calculate results
        cout << "Results for Election " << electionId << ":" << endl;
        cout << "Function not fully implemented yet." << endl;
    }

    void listAllVoters()
    {
        ifstream voterFile("voter.txt");
        if (!voterFile.is_open())
        {
            cout << "Unable to open voter file!" << endl;
            return;
        }

        cout << "\n===== Registered Voters =====\n";
        string username, password, CNIC, name, address;
        int voterCount = 0;

        // Read 5 lines at a time (username, password, CNIC, name, address)
        while (getline(voterFile, username))
        {
            if (!getline(voterFile, password) ||
                !getline(voterFile, CNIC) ||
                !getline(voterFile, name) ||
                !getline(voterFile, address))
            {
                cout << "Error: Incomplete voter record!" << endl;
                break;
            }

            voterCount++;
            cout << voterCount << ". CNIC: " << CNIC << ", Name: " << name << endl;
        }

        if (voterCount == 0)
        {
            cout << "No voters registered yet." << endl;
        }

        voterFile.close();
    }
};

// UserManager class to handle authentication and user management
class UserManager
{
private:
    User *currentUser;

public:
    UserManager()
    {
        currentUser = NULL;
    }

    ~UserManager()
    {
        if (currentUser != NULL)
        {
            delete currentUser;
        }
    }

    bool authenticateAdmin(string username, string password)
    {
        ifstream adminFile("admin.txt");
        if (!adminFile.is_open())
        {
            cout << "Admin file not found. Creating default admin account..." << endl;
            // Create default admin if file doesn't exist
            ofstream createAdmin("admin.txt");
            if (createAdmin.is_open())
            {
                createAdmin << "admin" << endl
                            << "admin123" << endl;
                createAdmin.close();
                cout << "Default admin created with username 'admin' and password 'admin123'" << endl;

                if (username == "admin" && password == "admin123")
                {
                    currentUser = new Administrator(username, password, "admin1", "Administrator", "SuperAdmin");
                    currentUser->setLoginStatus(true);
                    return true;
                }
            }
            else
            {
                cout << "Admin file could not be created!" << endl;
                return false;
            }
        }

        string fileUsername, filePassword;
        if (getline(adminFile, fileUsername) && getline(adminFile, filePassword))
        {
            adminFile.close();

            cout << "Checking admin credentials..." << endl;
            cout << "Stored username: " << fileUsername << endl;

            if (username == fileUsername && password == filePassword)
            {
                currentUser = new Administrator(username, password, "admin1", "Administrator", "SuperAdmin");
                currentUser->setLoginStatus(true);
                return true;
            }
            else
            {
                cout << "Invalid admin credentials. Please check username and password." << endl;
            }
        }
        else
        {
            adminFile.close();
            cout << "Admin file format is incorrect!" << endl;
        }

        return false;
    }

    bool authenticateVoter(string username, string password)
    {
        ifstream voterFile("voter.txt");
        if (!voterFile.is_open())
        {
            cout << "Voter file could not be opened!" << endl;
            return false;
        }

        string fileUsername, filePassword, CNIC, name, address;
        // Read 5 lines at a time (username, password, CNIC, name, address)
        while (getline(voterFile, fileUsername))
        {
            if (!getline(voterFile, filePassword) ||
                !getline(voterFile, CNIC) ||
                !getline(voterFile, name) ||
                !getline(voterFile, address))
            {
                cout << "Error: Incomplete voter record!" << endl;
                break;
            }

            if (username == fileUsername && password == filePassword)
            {
                voterFile.close();
                currentUser = new Voter(username, password, CNIC, name, address);
                currentUser->setLoginStatus(true);
                return true;
            }
        }

        voterFile.close();
        return false;
    }

    User *getCurrentUser()
    {
        return currentUser;
    }

    void logout()
    {
        if (currentUser != NULL)
        {
            currentUser->logout();
            delete currentUser;
            currentUser = NULL;
        }
    }
};

//--------nauman's code---------
// ----------------- Candidate Class -----------------

// class Candidate {
//     private:
//         string candidateId;
//         string name;
//         int voteCount;
    
//     public:
//         Candidate(string id, string n) : candidateId(id), name(n), voteCount(0) {}
    
//         string getCandidateId() const { return candidateId; }
//         string getName() const { return name; }
//         int getVoteCount() const { return voteCount; }
//         void incrementVoteCount() { voteCount++; }
//     };
// // ----------------- Vote Class -----------------

class Vote
{
private:
    string voteId;
    string voterId;
    string electionId;
    string candidateId;
    string timestamp;

public:
    Vote(string vId, string voter, string election, string candidate)
        : voteId(vId), voterId(voter), electionId(election), candidateId(candidate)
    {
        timestamp = "2025-01-01 00:00:00"; // placeholder timestamp, replace if needed
    }

    string getVoteId() const { return voteId; }
    string getVoterId() const { return voterId; }
    string getElectionId() const { return electionId; }
    string getCandidateId() const { return candidateId; }
    string getTimestamp() const { return timestamp; }
};

// ----------------- VotingSystem Class -----------------
class VotingSystem
{
private:
    User **users;
    int userCount;

    Election **elections;
    int electionCount;

    Vote **votes;
    int voteCount;

public:
    VotingSystem()
    {
        users = nullptr;
        userCount = 0;
        elections = nullptr;
        electionCount = 0;
        votes = nullptr;
        voteCount = 0;
    }

    void registerUser(User *user)
    {
        User **newUsers = new User *[userCount + 1];
        for (int i = 0; i < userCount; i++)
            newUsers[i] = users[i];
        newUsers[userCount] = user;
        delete[] users;
        users = newUsers;
        userCount++;
    }

    User *authenticateUser(string username, string password)
    {
        for (int i = 0; i < userCount; i++)
        {
            if (users[i]->getUsername() == username && users[i]->getPassword() == password)
                return users[i];
        }
        return nullptr;
    }

    void createElection(Election *election)
    {
        Election **newElections = new Election *[electionCount + 1];
        for (int i = 0; i < electionCount; i++)
            newElections[i] = elections[i];
        newElections[electionCount] = election;
        delete[] elections;
        elections = newElections;
        electionCount++;
    }

    void recordVote(Vote *vote)
    {
        Vote **newVotes = new Vote *[voteCount + 1];
        for (int i = 0; i < voteCount; i++)
            newVotes[i] = votes[i];
        newVotes[voteCount] = vote;
        delete[] votes;
        votes = newVotes;
        voteCount++;
    }

    bool hasUserVotedInElection(string userId, string electionId)
    {
        for (int i = 0; i < voteCount; i++)
        {
            if (votes[i]->getVoterId() == userId && votes[i]->getElectionId() == electionId)
                return true;
        }
        return false;
    }

    Election *getElectionById(string electionId)
    {
        for (int i = 0; i < electionCount; i++)
        {
            if (elections[i]->getElectionId() == electionId)
                return elections[i];
        }
        return nullptr;
    }

    Candidate *getCandidateById(string electionId, string candidateId)
    {
        Election *election = getElectionById(electionId);
        if (!election)
            return nullptr;

        Candidate **candidates = election->getCandidatesArray(); // Assuming a method returning raw array
        int candidateCount = election->getCandidateCount();

        for (int i = 0; i < candidateCount; i++)
        {
            if (candidates[i]->getCandidateId() == candidateId)
                return candidates[i];
        }
        return nullptr;
    }

    void displayAllElections()
    {
        for (int i = 0; i < electionCount; i++)
        {
            elections[i]->display();
        }
    }

    void displayActiveElections()
    {
        for (int i = 0; i < electionCount; i++)
        {
            if (elections[i]->isActive())
            {
                elections[i]->display();
            }
        }
    }

    void displayElectionResults(string electionId)
    {
        Election *election = getElectionById(electionId);
        if (!election)
        {
            cout << "Election not found.\n";
            return;
        }

        Candidate **candidates = election->getCandidatesArray();
        int candidateCount = election->getCandidateCount();

        cout << "Results for Election ID: " << electionId << endl;
        for (int i = 0; i < candidateCount; i++)
        {
            cout << "Candidate: " << candidates[i]->getName()
                 << " | Votes: " << candidates[i]->getVoteCount() << endl;
        }
    }
};

// Main function to demonstrate user authentication
int main()
{
    UserManager userManager;
    string userType, username, password;
    int choice;

    cout << "Welcome to Online Voting System" << endl;
    cout << "Are you an admin or a voter? (a/v): ";
    cin >> userType;

    // Convert input to lowercase for easier comparison
    for (int i = 0; i < userType.length(); i++)
    {
        userType[i] = tolower(userType[i]);
    }

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    bool loginSuccess = false;

    if (userType == "a" || userType == "admin")
    {
        loginSuccess = userManager.authenticateAdmin(username, password);
        if (loginSuccess)
        {
            cout << "Admin login successful!" << endl;

            // Cast to Administrator to access specific methods
            Administrator *admin = dynamic_cast<Administrator *>(userManager.getCurrentUser());

            bool continueLoop = true;
            while (continueLoop && admin != NULL && admin->getLoginStatus())
            {
                admin->displayMenu();
                cin >> choice;

                switch (choice)
                {
                case 1:
                    admin->createElection();
                    break;
                case 2:
                    admin->addCandidate();
                    break;
                case 3:
                    admin->addVoter();
                    break;
                case 4:
                    admin->viewElectionResults();
                    break;
                case 5:
                    admin->listAllVoters();
                    break;
                case 6:
                    cout << "Logging out..." << endl;
                    userManager.logout();
                    continueLoop = false;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }
        else
        {
            cout << "Admin login failed!" << endl;
        }
    }
    else if (userType == "v" || userType == "voter")
    {
        loginSuccess = userManager.authenticateVoter(username, password);
        if (loginSuccess)
        {
            cout << "Voter login successful!" << endl;

            // Cast to Voter to access specific methods
            Voter *voter = dynamic_cast<Voter *>(userManager.getCurrentUser());

            bool continueLoop = true;
            while (continueLoop && voter != NULL && voter->getLoginStatus())
            {
                voter->displayMenu();
                cin >> choice;

                switch (choice)
                {
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
        }
        else
        {
            cout << "Voter login failed!" << endl;
        }
    }
    else
    {
        cout << "Invalid user type!" << endl;
    }

    cout << "Thank you for using Online Voting System" << endl;

    return 0;
}