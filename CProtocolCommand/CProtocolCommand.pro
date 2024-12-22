QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG -= release

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CCommand.cpp \
    CCommandBtn.cpp \
    CCommandBtnLibrary.cpp \
    CCommandExcuteHandler.cpp \
    CCommandExecuteThread.cpp \
    CCommandLibrary.cpp \
    CCommandParam.cpp \
    CCommandStackElement.cpp \
    CConstantCommand.cpp \
    CConstantCommandBtn.cpp \
    CEventCommand.cpp \
    CExpressionCommand.cpp \
    CNumberConstantCommandBtnView.cpp \
    CObjectRepr.cpp \
    CSprite.cpp \
    CVarIable.cpp \
    Commands/bool/CForCommandBtn.cpp \
    Commands/bool/CIfCommandBtn.cpp \
    Commands/bool/CIfElseCommandBtn.cpp \
    Commands/bool/CWhileCommandBtn.cpp \
    Commands/number/CDivideCommand.cpp \
    Commands/number/CEqualNumberCommand.cpp \
    Commands/number/CGreaterThanNumberCommand.cpp \
    CMessage.cpp \
    CSignal.cpp \
    CStartCommand.cpp \
    CStatementCommand.cpp \
    CStatementsCommand.cpp \
    CValue.cpp \
    CVarCommand.cpp \
    CVarCommandBtn.cpp \
    CVarTable.cpp \
    Commands/number/CLessThanNumberCommand.cpp \
    Commands/number/CMinusCommand.cpp \
    Commands/number/CMultiplyCommand.cpp \
    Commands/number/CNumberRassignment.cpp \
    Commands/number/CPlusCommand.cpp \
    main.cpp \
    CProtocolCommand.cpp

HEADERS += \
    CCommand.h \
    CCommandBtn.h \
    CCommandBtnLibrary.h \
    CCommandExcuteHandler.h \
    CCommandExecuteThread.h \
    CCommandLibrary.h \
    CCommandParam.h \
    CCommandStackElement.h \
    CConstantCommand.h \
    CConstantCommandBtn.h \
    CEventCommand.h \
    CExpressionCommand.h \
    CNumberConstantCommandBtnView.h \
    CObjectRepr.h \
    CSprite.h \
    CVarIable.h \
    Commands/bool/CForCommandBtn.h \
    Commands/bool/CIfCommandBtn.h \
    Commands/bool/CIfElseCommandBtn.h \
    Commands/bool/CWhileCommandBtn.h \
    Commands/number/CDivideCommand.h \
    Commands/number/CEqualNumberCommand.h \
    Commands/number/CGreaterThanNumberCommand.h \
    CMessage.h \
    CProtocolCommand.h \
    CSignal.h \
    CStartCommand.h \
    CStatementCommand.h \
    CStatementsCommand.h \
    CValue.h \
    CVarCommand.h \
    CVarCommandBtn.h \
    CVarTable.h \
    Commands/number/CLessThanNumberCommand.h \
    Commands/number/CMinusCommand.h \
    Commands/number/CMultiplyCommand.h \
    Commands/number/CNumberRassignment.h \
    Commands/number/CPlusCommand.h

FORMS += \
    CProtocolCommand.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
