QT += core gui sql network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    modelFile/AiList_Model.cpp \
    modelFile/FriendList_Model.cpp \
    modelFile/GroupList_Model.cpp \
    srcFile/AiThread.cpp \
    srcFile/SQL.cpp \
    uiFile/AiChat.cpp \
    uiFile/AiInfo.cpp \
    uiFile/Chatbubble/recvbox.cpp \
    uiFile/Chatbubble/sendbox.cpp \
    uiFile/FriendChat.cpp \
    uiFile/FriendInfo.cpp \
    uiFile/GroupChat.cpp \
    uiFile/GroupInfo.cpp \
    uiFile/Logon.cpp \
    uiFile/Register.cpp \
    uiFile/Setup.cpp \
    uiFile/UserInfo.cpp

HEADERS += \
    mainwindow.h \
    modelFile/AiList_Model.h \
    modelFile/FriendList_Model.h \
    modelFile/GroupList_Model.h \
    srcFile/AiThread.h \
    srcFile/SQL.h \
    uiFile/AiChat.h \
    uiFile/AiInfo.h \
    uiFile/Chatbubble/recvbox.h \
    uiFile/Chatbubble/sendbox.h \
    uiFile/FriendChat.h \
    uiFile/FriendInfo.h \
    uiFile/GroupChat.h \
    uiFile/GroupInfo.h \
    uiFile/Logon.h \
    uiFile/Register.h \
    uiFile/Setup.h \
    uiFile/UserInfo.h

FORMS += \
    mainwindow.ui \
    uiFile/AiChat.ui \
    uiFile/AiInfo.ui \
    uiFile/Chatbubble/recvbox.ui \
    uiFile/Chatbubble/sendbox.ui \
    uiFile/FriendChat.ui \
    uiFile/FriendInfo.ui \
    uiFile/GroupChat.ui \
    uiFile/GroupInfo.ui \
    uiFile/Logon.ui \
    uiFile/Register.ui \
    uiFile/Setup.ui \
    uiFile/UserInfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/Image.qrc
