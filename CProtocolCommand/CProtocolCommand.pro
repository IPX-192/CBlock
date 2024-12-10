QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CCommand.cpp \
    CCommandBtn.cpp \
    CCommandStack.cpp \
    CCommandStackElement.cpp \
    CForCommandBtn.cpp \
    CIfCommandBtn.cpp \
    CIfElseCommandBtn.cpp \
    CMessage.cpp \
    CValue.cpp \
    CVarTable.cpp \
    CWhileCommandBtn.cpp \
    main.cpp \
    CProtocolCommand.cpp

HEADERS += \
    CCommand.h \
    CCommandBtn.h \
    CCommandStack.h \
    CCommandStackElement.h \
    CForCommandBtn.h \
    CIfCommandBtn.h \
    CIfElseCommandBtn.h \
    CMessage.h \
    CProtocolCommand.h \
    CValue.h \
    CVarTable.h \
    CWhileCommandBtn.h

FORMS += \
    CProtocolCommand.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
