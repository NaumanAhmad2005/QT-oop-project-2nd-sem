
#ifndef CANDIDATE_H
#define CANDIDATE_H

#include <QString>

class Candidate {
private:
    QString id;
    QString name;
    int partyAffiliation;
    int vote;
    QString electionId;

public:
    Candidate(const QString &id, const QString &name, int party, const QString &electionId)
        : id(id), name(name), partyAffiliation(party), vote(0), electionId(electionId) {}

    QString getId() const { return id; }
    QString getName() const { return name; }
    int getParty() const { return partyAffiliation; }
    int getVote() const { return vote; }
    QString getElectionId() const { return electionId; }

    void incrementVote() { vote++; }
};

#endif // CANDIDATE_H


