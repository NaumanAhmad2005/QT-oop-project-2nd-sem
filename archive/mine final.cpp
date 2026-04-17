#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

// Assuming the User, Election, and Candidate classes already exist in Abshar.cpp
// You should paste these class definitions above this code for it to compile

// ----------------- Vote Class -----------------
class Vote {
private:
    string voteId;
    string voterId;
    string electionId;
    string candidateId;
    string timestamp;

public:
    Vote(string vId, string voter, string election, string candidate)
        : voteId(vId), voterId(voter), electionId(election), candidateId(candidate) {
        time_t now = time(0);
        timestamp = ctime(&now);
        timestamp.pop_back(); // remove newline
    }

    string getVoteId() const { return voteId; }
    string getVoterId() const { return voterId; }
    string getElectionId() const { return electionId; }
    string getCandidateId() const { return candidateId; }
    string getTimestamp() const { return timestamp; }
};

// ----------------- VotingSystem Class -----------------
class VotingSystem {
private:
    User** users;
    int userCount;

    Election** elections;
    int electionCount;

    Vote** votes;
    int voteCount;

public:
    VotingSystem() {
        users = nullptr;
        userCount = 0;
        elections = nullptr;
        electionCount = 0;
        votes = nullptr;
        voteCount = 0;
    }

    void registerUser(User* user) {
        User** newUsers = new User*[userCount + 1];
        for (int i = 0; i < userCount; i++)
            newUsers[i] = users[i];
        newUsers[userCount] = user;
        delete[] users;
        users = newUsers;
        userCount++;
    }

    User* authenticateUser(string username, string password) {
        for (int i = 0; i < userCount; i++) {
            if (users[i]->getUsername() == username && users[i]->getPassword() == password)
                return users[i];
        }
        return nullptr;
    }

    void createElection(Election* election) {
        Election** newElections = new Election*[electionCount + 1];
        for (int i = 0; i < electionCount; i++)
            newElections[i] = elections[i];
        newElections[electionCount] = election;
        delete[] elections;
        elections = newElections;
        electionCount++;
    }

    void recordVote(Vote* vote) {
        Vote** newVotes = new Vote*[voteCount + 1];
        for (int i = 0; i < voteCount; i++)
            newVotes[i] = votes[i];
        newVotes[voteCount] = vote;
        delete[] votes;
        votes = newVotes;
        voteCount++;
    }

    bool hasUserVotedInElection(string userId, string electionId) {
        for (int i = 0; i < voteCount; i++) {
            if (votes[i]->getVoterId() == userId && votes[i]->getElectionId() == electionId)
                return true;
        }
        return false;
    }

    Election* getElectionById(string electionId) {
        for (int i = 0; i < electionCount; i++) {
            if (elections[i]->getElectionId() == electionId)
                return elections[i];
        }
        return nullptr;
    }

    Candidate* getCandidateById(string electionId, string candidateId) {
        Election* election = getElectionById(electionId);
        if (!election) return nullptr;

        vector<Candidate*> candidates = election->getCandidates();
        for (int i = 0; i < candidates.size(); i++) {
            if (candidates[i]->getCandidateId() == candidateId)
                return candidates[i];
        }
        return nullptr;
    }

    void displayAllElections() {
        for (int i = 0; i < electionCount; i++) {
            elections[i]->display();
        }
    }

    void displayActiveElections() {
        for (int i = 0; i < electionCount; i++) {
            if (elections[i]->isActive()) {
                elections[i]->display();
            }
        }
    }

    void displayElectionResults(string electionId) {
        Election* election = getElectionById(electionId);
        if (!election) {
            cout << "Election not found.\n";
            return;
        }

        vector<Candidate*> candidates = election->getCandidates();
        cout << "Results for Election ID: " << electionId << endl;
        for (int i = 0; i < candidates.size(); i++) {
            cout << "Candidate: " << candidates[i]->getName()
                 << " | Votes: " << candidates[i]->getVoteCount() << endl;
        }
    }
};
