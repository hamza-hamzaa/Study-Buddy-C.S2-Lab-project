#include <QTest>
#include "chatcontroller.h"
#include "ichatclient.h"
#include "fakeit.hpp"

using namespace fakeit;

class TestChatController : public QObject
{
    Q_OBJECT

private slots:
    void send_validMessage();
    void send_emptyMessage();
    void send_spacesOnly();
    void send_nullClient();
    void json_containsAction();
    void json_containsRoom();
    void json_containsSender();
    void json_containsContent();
    void join_containsAction();
    void join_containsUserAndRoom();
};

void TestChatController::send_validMessage()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    When(Method(mockClient, sendMessage)).AlwaysReturn();

    bool result = controller.sendChatMessage("Hello");

    QVERIFY(result);
    Verify(Method(mockClient, sendMessage)).Once();
}

void TestChatController::send_emptyMessage()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    bool result = controller.sendChatMessage("");

    QVERIFY(!result);
    Verify(Method(mockClient, sendMessage)).Never();
}

void TestChatController::send_spacesOnly()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    bool result = controller.sendChatMessage("   ");

    QVERIFY(!result);
    Verify(Method(mockClient, sendMessage)).Never();
}

void TestChatController::send_nullClient()
{
    ChatController controller(nullptr, "Student_01", "ROOM1");

    bool result = controller.sendChatMessage("Hello");

    QVERIFY(!result);
}

void TestChatController::json_containsAction()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    QString json = controller.buildChatJson("Hi");

    QVERIFY(json.contains("CHAT_MSG"));
}

void TestChatController::json_containsRoom()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    QString json = controller.buildChatJson("Hi");

    QVERIFY(json.contains("ROOM1"));
}

void TestChatController::json_containsSender()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    QString json = controller.buildChatJson("Hi");

    QVERIFY(json.contains("Student_01"));
}

void TestChatController::json_containsContent()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    QString json = controller.buildChatJson("Hi");

    QVERIFY(json.contains("Hi"));
}

void TestChatController::join_containsAction()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    QString json = controller.buildJoinJson();

    QVERIFY(json.contains("JOIN_GROUP"));
}

void TestChatController::join_containsUserAndRoom()
{
    Mock<IChatClient> mockClient;
    ChatController controller(&mockClient.get(), "Student_01", "ROOM1");

    QString json = controller.buildJoinJson();

    QVERIFY(json.contains("Student_01"));
    QVERIFY(json.contains("ROOM1"));
}

QTEST_MAIN(TestChatController)
#include "test_chatcontroller.moc"
