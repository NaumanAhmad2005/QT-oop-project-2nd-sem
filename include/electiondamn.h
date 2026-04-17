#ifndef ELECTIONDAMN_H
#define ELECTIONDAMN_H

#include <QString>

class Election {
protected:
    QString electionId;
    QString electionName;
    QString electionType; // "National" or "Local"
    bool isActive;

public:
    // Default constructor
    Election() : electionId(""), electionName(""), electionType(""), isActive(false) {}

    // Parameterized constructor
    Election(const QString& id, const QString& name, const QString& type)
        : electionId(id), electionName(name), electionType(type), isActive(true) {}

    QString getElectionId() const {
        return electionId;
    }

    QString getElectionName() const {
        return electionName;
    }

    QString getElectionType() const {
        return electionType;
    }

    bool getIsActive() const {
        return isActive;
    }

    void setIsActive(bool active) {
        isActive = active;
    }
    virtual QString getElectionInfo() const {
        return QString("Election: %1 - Type: %2").arg(electionName, electionType);
    }
};
class LocalElection : public Election {
private:
    QString district;

public:
    LocalElection(const QString& id, const QString& name, const QString& districtName)
        : Election(id, name, "Local"), district(districtName) {}

    QString getDistrict() const { return district; }

    QString getElectionInfo() const override {
        return QString("Local Election in %1 District - Name: %2").arg(district, electionName);
    }
};

class NationalElection : public Election {
private:
    QString country;

public:
    NationalElection(const QString& id, const QString& name, const QString& countryName)
        : Election(id, name, "National"), country(countryName) {}

    QString getCountry() const { return country; }

    QString getElectionInfo() const override {
        return QString("National Election - Country: %1, Name: %2").arg(country, electionName);
    }
};
#endif // ELECTIONDAMN_H
