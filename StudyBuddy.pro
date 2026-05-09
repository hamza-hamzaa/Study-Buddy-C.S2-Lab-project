QT += widgets network testlib

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatselectionwindow.cpp \
    inputvalidation.cpp \
    chatwindow.cpp \
    courseselectionwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    chatcontroller.h \
    chatselectionwindow.h \
    chatwindow.h \
    courseselectionwindow.h \
    ichatclient.h \
    inputvalidation.h \
    mainwindow.h

FORMS += \
    chatselectionwindow.ui \
    chatwindow.ui \
    courseselectionwindow.ui \
    mainwindow.ui

OTHER_FILES += \
    fakeit.hpp \
    test_chatcontroller.cpp \
    test_chatwindow.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
