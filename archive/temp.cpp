#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

// Forward declarations
class Candidate;
class Election;

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

// Candidate class
class Candidate 
{
private:
    string candidateId;
    string name;
    string party;
    string electionId;
    int voteCount;
    
public:
    Candidate() 
    {
        candidateId = "";
        name = "";
        party = "";
        electionId = "";
        voteCount = 0;
    }
    
    Candidate(string id, string n, string p, string eId) 
    {
        candidateId = id;
        name = n;
        party = p;
        electionId = eId;
        voteCount = 0;
    }
    
    string getCandidateId() const { return candidateId; }
    string getName() const { return name; }
    string getParty() const { return party; }
    string getElectionId() const { return electionId; }
    int getVoteCount() const { return voteCount; }
    void incrementVoteCount() { voteCount++; }
    
    void display() const 
    {
        cout << "Candidate ID: " << candidateId << endl;
        cout << "Name: " << name << endl;
        cout << "Party: " << party << endl;
        cout << "Votes: " << voteCount << endl;
    }
};

// election class
class Election
{
private:
    string electionId;
    string electionName;
    string electionType; // "National" or "Local"
    bool isActive;
    Candidate* candidates[20]; // Array to store up to 20 candidates
    int candidateCount;

public:
    // Default constructor
    Election() : electionId(""), electionName(""), electionType(""), isActive(false), candidateCount(0) {}

    // Parameterized constructor
    Election(string id, string name, string type) : electionId(id), electionName(name), electionType(type), isActive(true), candidateCount(0) {}

    string getElectionId() const
    {
        return electionId;
    }

    string getElectionName() const
    {
        return electionName;
    }

    string getElectionType() const
    {
        return electionType;
    }

    bool getIsActive() const
    {
        return isActive;
    }

    void setIsActive(bool active)
    {
        isActive = active;
    }

    void display() const
    {
        cout << "\n----- Election Details -----" << endl;
        cout << "Election ID: " << electionId << endl;
        cout << "Election Name: " << electionName << endl;
        cout << "Election Type: " << electionType << endl;
        cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    }

    bool addCandidate(Candidate* candidate) 
    {
        if (candidateCount >= 20) {
            return false; // Cannot add more candidates
        }
        candidates[candidateCount++] = candidate;
        return true;
    }

    Candidate** getCandidatesArray() const 
    {
        return (Candidate**)candidates;
    }

    int getCandidateCount() const 
    {
        return candidateCount;
    }

    Candidate* getCandidateById(string candidateId) const 
    {
        for (int i = 0; i < candidateCount; i++) {
            if (candidates[i]->getCandidateId() == candidateId) {
                return candidates[i];
            }
        }
        return nullptr;
    }

    void displayCandidates() const 
    {
        cout << "\n----- Candidates for Election: " << electionName << " -----" << endl;
        if (candidateCount == 0) {
            cout << "No candidates registered for this election." << endl;
            return;
        }

        for (int i = 0; i < candidateCount; i++) {
            cout << i+1 << ". " << candidates[i]->getName() << " (" << candidates[i]->getParty() << ") - ID: " << candidates[i]->getCandidateId() << endl;
        }
    }

    // Load candidates from file
    void loadCandidates() 
    {
        ifstream candidateFile("candidate.txt");
        if (!candidateFile.is_open()) {
            return;
        }

        string fileElectionId, candidateId, candidateName, candidateParty;
        
        while (getline(candidateFile, fileElectionId) && 
               getline(candidateFile, candidateId) &&
               getline(candidateFile, candidateName) &&
               getline(candidateFile, candidateParty)) {
            
            if (fileElectionId == electionId && candidateCount < 20) {
                candidates[candidateCount++] = new Candidate(candidateId, candidateName, candidateParty, electionId);
            }
        }
        
        candidateFile.close();
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

    string getVoterName() const
    {
        return voterName;
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
        loadElections(); // Load elections from file when admin is created
    }

    void displayMenu() override
    {
        cout << "\n===== Administrator Menu =====" << endl;
        cout << "1. Create Election" << endl;
        cout << "2. Add Candidate" << endl;
        cout << "3. Add Voter" << endl;
        cout << "4. View Election Results" << endl;
        cout << "5. List All Voters" << endl;
        cout << "6. List All Elections" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";
    }

    void addCandidate()
    {
        string candidateId, candidateName, candidateParty, electionId;

        cout << "\n===== Add Candidate =====\n";
        // Display available elections
        cout << "Available Elections:" << endl;
        for (int i = 0; i < electionCount; i++) {
            cout << i+1 << ". ID: " << elections[i].getElectionId() 
                 << " - Name: " << elections[i].getElectionName() << endl;
        }

        cout << "Enter Election ID: ";
        cin >> electionId;
        
        // Find the election
        int electionIndex = -1;
        for (int i = 0; i < electionCount; i++) {
            if (elections[i].getElectionId() == electionId) {
                electionIndex = i;
                break;
            }
        }
        
        if (electionIndex == -1) {
            cout << "Election not found!" << endl;
            return;
        }

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
            
            // Add candidate to election object
            Candidate* newCandidate = new Candidate(candidateId, candidateName, candidateParty, electionId);
            elections[electionIndex].addCandidate(newCandidate);
        }
        else
        {
            cout << "Unable to open candidate file!" << endl;
        }
    }

    void addVoter()
    {
        string CNIC, Name, address, username, password;

        cout << "\n===== Add Voter =====\n";
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

        cout << "\n===== Create Election =====\n";
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
        if (electionCount == 0) {
            cout << "No elections available." << endl;
            return;
        }

        // Display available elections
        cout << "\n===== Available Elections =====\n";
        for (int i = 0; i < electionCount; i++) {
            cout << i+1 << ". " << elections[i].getElectionName() 
                << " (ID: " << elections[i].getElectionId() << ")" << endl;
        }

        string electionId;
        cout << "Enter Election ID to view results: ";
        cin >> electionId;

        // Find the election
        int electionIndex = -1;
        for (int i = 0; i < electionCount; i++) {
            if (elections[i].getElectionId() == electionId) {
                electionIndex = i;
                break;
            }
        }
        
        if (electionIndex == -1) {
            cout << "Election not found!" << endl;
            return;
        }

        // Load vote counts from file
        loadVotes(electionId);

        // Display results
        cout << "\n===== Election Results: " << elections[electionIndex].getElectionName() << " =====\n";
        
        Candidate** candidates = elections[electionIndex].getCandidatesArray();
        int candidateCount = elections[electionIndex].getCandidateCount();
        
        if (candidateCount == 0) {
            cout << "No candidates in this election." << endl;
            return;
        }
        
        for (int i = 0; i < candidateCount; i++) {
            cout << candidates[i]->getName() << " (" << candidates[i]->getParty() 
                 << ") - Votes: " << candidates[i]->getVoteCount() << endl;
        }
    }

    void loadVotes(string electionId) 
    {
        // Find the election
        int electionIndex = -1;
        for (int i = 0; i < electionCount; i++) {
            if (elections[i].getElectionId() == electionId) {
                electionIndex = i;
                break;
            }
        }
        
        if (electionIndex == -1) {
            return;
        }

        // Load vote counts from file
        ifstream voteFile("votes.txt");
        if (!voteFile.is_open()) {
            return;
        }

        string voteId, voterId, fileElectionId, candidateId, timestamp;
        
        while (getline(voteFile, voteId) && 
               getline(voteFile, voterId) &&
               getline(voteFile, fileElectionId) &&
               getline(voteFile, candidateId) &&
               getline(voteFile, timestamp)) {
            
            if (fileElectionId == electionId) {
                Candidate* candidate = elections[electionIndex].getCandidateById(candidateId);
                if (candidate != nullptr) {
                    candidate->incrementVoteCount();
                }
            }
        }
        
        voteFile.close();
    }

    void loadElections() 
    {
        ifstream electionFile("elections.txt");
        if (!electionFile.is_open()) {
            return;
        }

        string electionId, electionName, electionType, status;
        
        while (getline(electionFile, electionId) && 
               getline(electionFile, electionName) &&
               getline(electionFile, electionType) &&
               getline(electionFile, status) && 
               electionCount < 10) {
            
            elections[electionCount] = Election(electionId, electionName, electionType);
            if (status != "active") {
                elections[electionCount].setIsActive(false);
            }
            
            // Load candidates for this election
            elections[electionCount].loadCandidates();
            
            electionCount++;
        }
        
        electionFile.close();
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

    void listAllElections()
    {
        cout << "\n===== All Elections =====\n";
        if (electionCount == 0)
        {
            cout << "No elections created yet." << endl;
            return;
        }

        for (int i = 0; i < electionCount; i++)
        {
            cout << i + 1 << ". ";
            elections[i].display();
        }
    }

    Election* getElectionById(string electionId)
    {
        for (int i = 0; i < electionCount; i++)
        {
            if (elections[i].getElectionId() == electionId)
            {
                return &elections[i];
            }
        }
        return nullptr;
    }

    Election* getElections()
    {
        return elections;
    }

    int getElectionCount()
    {
        return electionCount;
    }
};

// Vote class
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
        // Create a simple timestamp (YYYYMMDD-HHMMSS format)
        timestamp = "20250101-000000"; // Placeholder
    }

    string getVoteId() const { return voteId; }
    string getVoterId() const { return voterId; }
    string getElectionId() const { return electionId; }
    string getCandidateId() const { return candidateId; }
    string getTimestamp() const { return timestamp; }

    // Save vote to file
    bool saveVote() 
    {
        ofstream voteFile("votes.txt", ios::app);
        if (!voteFile.is_open()) {
            return false;
        }

        voteFile << voteId << endl;
        voteFile << voterId << endl;
        voteFile << electionId << endl;
        voteFile << candidateId << endl;
        voteFile << timestamp << endl;
        
        voteFile.close();
        return true;
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

// Function declarations
void viewAvailableElections();
void castVote(Voter* voter);

// Main function to demonstrate user authentication
int main()
{
    UserManager userManager;
    string userType, username, password;
    int choice;

    cout << "=====================================================" << endl;
    cout << "         Welcome to Online Voting System             " << endl;
    cout << "=====================================================" << endl;
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
                    admin->listAllElections();
                    break;
                case 7:
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
                    // View Available Elections
                    viewAvailableElections();
                    break;
                case 2:
                    // Cast Vote
                    castVote(voter);
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

// Function to view available elections
void viewAvailableElections()
{
    ifstream electionFile("elections.txt");
    if (!electionFile.is_open())
    {
        cout << "No elections available." << endl;
        return;
    }

    cout << "\n===== Available Elections =====\n";
    string electionId, electionName, electionType, status;
    int count = 0;

    // Read 4 lines at a time (electionId, electionName, electionType, status)
    while (getline(electionFile, electionId))
    {
        if (!getline(electionFile, electionName) ||
            !getline(electionFile, electionType) ||
            !getline(electionFile, status))
        {
            cout << "Error: Incomplete election record!" << endl;
            break;
        }

        if (status == "active")
        {
            if (!voter->hasVotedInElection(electionId))
            {
                electionsAvailable[electionCount] = electionId;
                electionCount++;
                cout << electionCount << ". Election ID: " << electionId << endl;
                cout << "   Name: " << electionName << endl;
                cout << "   Type: " << electionType << endl << endl;
            }
        ")
        {
            count++;
            cout << count << ". Election ID: " << electionId << endl;
            cout << "   Name: " << electionName << endl;
            cout << "   Type: " << electionType << endl;
            cout << "   Status: Active" << endl << endl;
        }
    }

    if (count == 0)
    {
        cout << "No active elections available." << endl;
    }

    electionFile.close();
    
    if (electionCount == 0)
    {
        cout << "No elections available for voting." << endl;
        return;
    }

    // Select an election to vote in
    int electionChoice;
    cout << "Enter the number of the election you want to vote in (1-" << electionCount << "): ";
    cin >> electionChoice;

    if (electionChoice < 1 || electionChoice > electionCount)
    {
        cout << "Invalid election choice." << endl;
        return;
    }

    string selectedElectionId = electionsAvailable[electionChoice - 1];
    
    // Display candidates for the selected election
    cout << "\n===== Candidates for Election ID: " << selectedElectionId << " =====\n";
    
    // Load candidates from file
    ifstream candidateFile("candidate.txt");
    if (!candidateFile.is_open())
    {
        cout << "No candidates available." << endl;
        return;
    }

    string fileElectionId, candidateId, candidateName, candidateParty;
    int candidateCount = 0;
    string candidatesAvailable[20]; // Store up to 20 candidate IDs

    // Read 4 lines at a time (electionId, candidateId, candidateName, candidateParty)
    while (getline(candidateFile, fileElectionId))
    {
        if (!getline(candidateFile, candidateId) ||
            !getline(candidateFile, candidateName) ||
            !getline(candidateFile, candidateParty))
        {
            cout << "Error: Incomplete candidate record!" << endl;
            break;
        }

        if (fileElectionId == selectedElectionId)
        {
            candidatesAvailable[candidateCount] = candidateId;
            candidateCount++;
            cout << candidateCount << ". Candidate ID: " << candidateId << endl;
            cout << "   Name: " << candidateName << endl;
            cout << "   Party: " << candidateParty << endl << endl;
        }
    }

    candidateFile.close();

    if (candidateCount == 0)
    {
        cout << "No candidates available for this election." << endl;
        return;
    }

    // Select a candidate to vote for
    int candidateChoice;
    cout << "Enter the number of the candidate you want to vote for (1-" << candidateCount << "): ";
    cin >> candidateChoice;

    if (candidateChoice < 1 || candidateChoice > candidateCount)
    {
        cout << "Invalid candidate choice." << endl;
        return;
    }

    string selectedCandidateId = candidatesAvailable[candidateChoice - 1];
    
    // Create and save the vote
    // Generate a simple vote ID (voterId + electionId)
    string voteId = voter->getUserId() + selectedElectionId;
    
    Vote newVote(voteId, voter->getUserId(), selectedElectionId, selectedCandidateId);
    if (newVote.saveVote())
    {
        cout << "Vote cast successfully!" << endl;
        voter->recordVote(selectedElectionId);
    }
    else
    {
        cout << "Error: Unable to cast vote." << endl;
    }
}

// Function to cast vote
void castVote(Voter* voter)
{
    if (voter == NULL)
    {
        cout << "Error: Invalid voter!" << endl;
        return;
    }

    // First display available elections
    cout << "\n===== Available Elections for Voting =====\n";
    ifstream electionFile("elections.txt");
    if (!electionFile.is_open())
    {
        cout << "No elections available." << endl;
        return;
    }

    string electionId, electionName, electionType, status;
    int electionCount = 0;
    string electionsAvailable[10]; // Store up to 10 election IDs

    // Read 4 lines at a time (electionId, electionName, electionType, status)
    while (getline(electionFile, electionId))
    {
        if (!getline(electionFile, electionName) ||
            !getline(electionFile, electionType) ||
            !getline(electionFile, status))
        {
            cout << "Error: Incomplete election record!" << endl;
            break;
        }

        if (status == "active")
        {
            electionsAvailable[electionCount] = electionId;
            electionCount++;
            cout << electionCount << ". Election ID: " << electionId << endl;
            cout << "   Name: " << electionName << endl;
            cout << "   Type: " << electionType << endl;
            cout << "   Status: Active" << endl << endl;
        }
    }