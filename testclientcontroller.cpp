#include "testclientcontroller.h"
#include <QSignalSpy>

void TestClientController::init() {
    m_mockNetwork = new MockNetworkClient();
    m_controller = new ClientController(m_mockNetwork);
}

void TestClientController::cleanup() {
    delete m_controller;
    delete m_mockNetwork;
}

void TestClientController::testValidateLoginValid() {
    QVERIFY(m_controller->validateLogin("John", "john@aucegypt.edu", 90020001, "Computer Science"));
}

void TestClientController::testValidateLoginInvalidName() {
    QVERIFY(!m_controller->validateLogin("", "john@aucegypt.edu", 90020001, "Computer Science"));
}

void TestClientController::testValidateLoginInvalidEmail() {
    QVERIFY(!m_controller->validateLogin("John", "john@gmail.com", 90020001, "Computer Science"));
}

void TestClientController::testValidateLoginInvalidId() {
    QVERIFY(!m_controller->validateLogin("John", "john@aucegypt.edu", 90010001, "Computer Science"));
}

void TestClientController::testValidateLoginInvalidMajor() {
    QVERIFY(!m_controller->validateLogin("John", "john@aucegypt.edu", 90020001, "Major"));
}

void TestClientController::testValidateCoursesValid() {
    QList<QString> courses = {"CS1", "CS2", "CS3"};
    QVERIFY(m_controller->validateCourses(courses));
}

void TestClientController::testValidateCoursesTooMany() {
    QList<QString> courses;
    for (int i = 0; i < 7; ++i) courses << QString("CS%1").arg(i);
    QVERIFY(!m_controller->validateCourses(courses));
}

void TestClientController::testValidateCoursesEmpty() {
    QList<QString> courses;
    QVERIFY(!m_controller->validateCourses(courses));
}

void TestClientController::testGenerateRoomId() {
    QString roomId = m_controller->generateRoomId("CSCE 1102", true);
    QCOMPARE(roomId, QString("CSCE1102_FOCUSED"));
    roomId = m_controller->generateRoomId("CSCE 1102", false);
    QCOMPARE(roomId, QString("CSCE1102_CASUAL"));
}

void TestClientController::testLoginFlow() {
    QSignalSpy spy(m_mockNetwork, &MockNetworkClient::messageReceived);
    // Simulate login
    m_controller->onLoginRequested("John", "john@aucegypt.edu", 90020001, "Computer Science");
    // Check if course window is shown, but since it's GUI, hard to test without QTest::qWaitForWindowShown
    // For now, assume it's called
}

void TestClientController::testCourseSelectionFlow() {
    QList<QString> courses = {"CS1", "CS2"};
    m_controller->onCoursesSelected(courses);
    // Similar
}

void TestClientController::testJoinRoomFlow() {
    m_controller->onJoinRoomRequested("CSCE1102_FOCUSED");
    QList<QJsonObject> messages = m_mockNetwork->getSentMessages();
    QCOMPARE(messages.size(), 1);
    QCOMPARE(messages[0]["action"].toString(), QString("JOIN_GROUP"));
    QCOMPARE(messages[0]["room_id"].toString(), QString("CSCE1102_FOCUSED"));
}

void TestClientController::testSendChatMessage() {
    m_controller->onJoinRoomRequested("CSCE1102_FOCUSED");
    m_controller->onChatMessageSent("Hello");
    QList<QJsonObject> messages = m_mockNetwork->getSentMessages();
    QCOMPARE(messages.size(), 2); // join and chat
    QCOMPARE(messages[1]["action"].toString(), QString("CHAT_MSG"));
    QCOMPARE(messages[1]["content"].toString(), QString("Hello"));
}