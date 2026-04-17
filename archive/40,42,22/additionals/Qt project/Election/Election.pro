QT       += core gui
QT += core gui sql
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addvoter.cpp \
    adminfunctionality.cpp \
    avalableelections.cpp \
    castvote.cpp \
    createcandidatedamn.cpp \
    createelction.cpp \
    damnloginadmin.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    viewresults.cpp \
    voterfunctionality.cpp \
    voterlogindamn.cpp

HEADERS += \
    Candidate.h \
    UserManager.h \
    Voter.h \
    addvoter.h \
    adminfunctionality.h \
    avalableelections.h \
    castvote.h \
    createcandidatedamn.h \
    createelction.h \
    damnloginadmin.h \
    databasemanager.h \
    electiondamn.h \
    mainwindow.h \
    viewresults.h \
    voterfunctionality.h \
    voterlogindamn.h

FORMS += \
    addvoter.ui \
    adminfunctionality.ui \
    avalableelections.ui \
    castvote.ui \
    createcandidatedamn.ui \
    createelction.ui \
    damnloginadmin.ui \
    mainwindow.ui \
    viewresults.ui \
    voterfunctionality.ui \
    voterlogindamn.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
