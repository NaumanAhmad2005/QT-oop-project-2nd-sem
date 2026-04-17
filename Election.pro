QT       += core gui
QT += core gui sql
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/addvoter.cpp \
    src/adminfunctionality.cpp \
    src/avalableelections.cpp \
    src/castvote.cpp \
    src/createcandidatedamn.cpp \
    src/createelction.cpp \
    src/damnloginadmin.cpp \
    src/databasemanager.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/viewresults.cpp \
    src/voterfunctionality.cpp \
    src/voterlogindamn.cpp

HEADERS += \
    include/Candidate.h \
    include/UserManager.h \
    include/Voter.h \
    include/addvoter.h \
    include/adminfunctionality.h \
    include/avalableelections.h \
    include/castvote.h \
    include/createcandidatedamn.h \
    include/createelction.h \
    include/damnloginadmin.h \
    include/databasemanager.h \
    include/electiondamn.h \
    include/mainwindow.h \
    include/viewresults.h \
    include/voterfunctionality.h \
    include/voterlogindamn.h

FORMS += \
    ui/addvoter.ui \
    ui/adminfunctionality.ui \
    ui/avalableelections.ui \
    ui/castvote.ui \
    ui/createcandidatedamn.ui \
    ui/createelction.ui \
    ui/damnloginadmin.ui \
    ui/mainwindow.ui \
    ui/viewresults.ui \
    ui/voterfunctionality.ui \
    ui/voterlogindamn.ui

INCLUDEPATH += $$PWD/include

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
