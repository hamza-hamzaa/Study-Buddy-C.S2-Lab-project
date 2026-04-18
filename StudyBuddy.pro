QT += core widgets network testlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatselectionwindow.cpp \
    chatwindow.cpp \
    courseselectionwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qtnetworkclient.cpp \
    clientcontroller.cpp \
    testclientcontroller.cpp

HEADERS += \
    chatselectionwindow.h \
    chatwindow.h \
    courseselectionwindow.h \
    mainwindow.h \
    networkclient.h \
    qtnetworkclient.h \
    clientcontroller.h \
    mocknetworkclient.h \
    testclientcontroller.h

FORMS += \
    chatselectionwindow.ui \
    chatwindow.ui \
    courseselectionwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
