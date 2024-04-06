QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    srcFile/threadFile/SqlThread.cpp \
    srcFile/threadFile/TcpThread.cpp \
    uiFile/FileInfo.cpp \
    uiFile/GroupInfo.cpp \
    uiFile/SqlInfo.cpp \
    uiFile/UserInfo.cpp \
    uiFile/mainWidget.cpp

HEADERS += \
    mainwindow.h \
    srcFile/threadFile/SqlThread.h \
    srcFile/threadFile/TcpThread.h \
    uiFile/FileInfo.h \
    uiFile/GroupInfo.h \
    uiFile/SqlInfo.h \
    uiFile/UserInfo.h \
    uiFile/mainWidget.h

FORMS += \
    mainwindow.ui \
    uiFile/FileInfo.ui \
    uiFile/GroupInfo.ui \
    uiFile/SqlInfo.ui \
    uiFile/UserInfo.ui \
    uiFile/mainWidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image/icons.qrc
