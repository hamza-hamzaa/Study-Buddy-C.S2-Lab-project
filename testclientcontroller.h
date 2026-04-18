#ifndef TESTCLIENTCONTROLLER_H
#define TESTCLIENTCONTROLLER_H

#include <QObject>
#include <QtTest/QtTest>
#include "clientcontroller.h"
#include "mocknetworkclient.h"

class TestClientController : public QObject {
    Q_OBJECT

private slots:
    void init();
    void cleanup();

    void testValidateLoginValid();
    void testValidateLoginInvalidName();
    void testValidateLoginInvalidEmail();
    void testValidateLoginInvalidId();
    void testValidateLoginInvalidMajor();

    void testValidateCoursesValid();
    void testValidateCoursesTooMany();
    void testValidateCoursesEmpty();

    void testGenerateRoomId();

    void testLoginFlow();
    void testCourseSelectionFlow();
    void testJoinRoomFlow();
    void testSendChatMessage();

private:
    MockNetworkClient* m_mockNetwork;
    ClientController* m_controller;
};

#endif // TESTCLIENTCONTROLLER_H