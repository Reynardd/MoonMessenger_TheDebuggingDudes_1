QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatbutton.cpp \
    chatlistpage.cpp \
    chatthread.cpp \
    conversation.cpp \
    conversationwindow.cpp \
    infodialog.cpp \
    joinconversationwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    messagerect.cpp \
    newconversationwindow.cpp \
    request.cpp \
    signupwindow.cpp \
    user.cpp \
    yesnodialog.cpp

HEADERS += \
    chatbutton.h \
    chatlistpage.h \
    chatthread.h \
    conversation.h \
    conversationwindow.h \
    infodialog.h \
    joinconversationwindow.h \
    mainwindow.h \
    message.h \
    messagerect.h \
    newconversationwindow.h \
    request.h \
    signupwindow.h \
    user.h \
    yesnodialog.h

FORMS += \
    chatlistpage.ui \
    conversationwindow.ui \
    infodialog.ui \
    joinconversationwindow.ui \
    mainwindow.ui \
    newconversationwindow.ui \
    signupwindow.ui \
    yesnodialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources/Resource.qrc \
    Resources/Resource.qrc
