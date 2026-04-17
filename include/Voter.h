
#ifndef VOTER_H
#define VOTER_H

#include <QString>

class Voter {
private:
    QString cnin;
    QString name;
    QString username;
    QString password;

public:
    Voter(const QString &cnin, const QString &name, const QString &username, const QString &password)
        : cnin(cnin), name(name), username(username), password(password) {}

    QString getCnin() const { return cnin; }
    QString getName() const { return name; }
    QString getUsername() const { return username; }
    QString getPassword() const { return password; }
};



#endif // VOTER_H
