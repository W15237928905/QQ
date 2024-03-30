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
    srcFile/AiSrc/AI.cpp \
    srcFile/AiSrc/AiThread.cpp \
    srcFile/FileSrc/FileThread.cpp \
    srcFile/HOST.cpp \
    srcFile/SQL.cpp \
    srcFile/USER.cpp \
    uiFile/AiChat.cpp \
    uiFile/AiInfo.cpp \
    uiFile/Chatbubble/recvbox.cpp \
    uiFile/Chatbubble/sendFilebox.cpp \
    uiFile/Chatbubble/sendbox.cpp \
    uiFile/Emotion.cpp \
    uiFile/FriendChat.cpp \
    uiFile/FriendInfo.cpp \
    uiFile/GroupChat.cpp \
    uiFile/GroupInfo.cpp \
    uiFile/Logon.cpp \
    uiFile/Register.cpp \
    uiFile/SetUp/AiSetup.cpp \
    uiFile/SetUp/FileSetup.cpp \
    uiFile/SetUp/SetUp.cpp \
    uiFile/SetUp/UserSetup.cpp \
    uiFile/UserInfo.cpp

HEADERS += \
    mainwindow.h \
    modelFile/AiList_Model.h \
    modelFile/FriendList_Model.h \
    modelFile/GroupList_Model.h \
    srcFile/AiSrc/AI.h \
    srcFile/AiSrc/AiThread.h \
    srcFile/FileSrc/FileThread.h \
    srcFile/HOST.h \
    srcFile/SQL.h \
    srcFile/USER.h \
    uiFile/AiChat.h \
    uiFile/AiInfo.h \
    uiFile/Chatbubble/recvbox.h \
    uiFile/Chatbubble/sendFilebox.h \
    uiFile/Chatbubble/sendbox.h \
    uiFile/Emotion.h \
    uiFile/FriendChat.h \
    uiFile/FriendInfo.h \
    uiFile/GroupChat.h \
    uiFile/GroupInfo.h \
    uiFile/Logon.h \
    uiFile/Register.h \
    uiFile/SetUp/AiSetup.h \
    uiFile/SetUp/FileSetup.h \
    uiFile/SetUp/SetUp.h \
    uiFile/SetUp/UserSetup.h \
    uiFile/UserInfo.h

FORMS += \
    mainwindow.ui \
    uiFile/AiChat.ui \
    uiFile/AiInfo.ui \
    uiFile/Chatbubble/recvbox.ui \
    uiFile/Chatbubble/sendFilebox.ui \
    uiFile/Chatbubble/sendbox.ui \
    uiFile/Emotion.ui \
    uiFile/FriendChat.ui \
    uiFile/FriendInfo.ui \
    uiFile/GroupChat.ui \
    uiFile/GroupInfo.ui \
    uiFile/Logon.ui \
    uiFile/Register.ui \
    uiFile/SetUp/AiSetup.ui \
    uiFile/SetUp/FileSetup.ui \
    uiFile/SetUp/SetUp.ui \
    uiFile/SetUp/UserSetup.ui \
    uiFile/UserInfo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/Image.qrc
