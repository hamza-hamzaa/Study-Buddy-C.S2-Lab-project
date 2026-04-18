// //#include <QtTest>
// #include <QTextEdit>
// #include <QLineEdit>
// #include <QPushButton>
// #include <QLabel>
// #include <QSignalSpy>

// #include "chatwindow.h"
// #include "fakeit.hpp"

// using namespace fakeit;

// // -----------------------------------------------------------------------------
// // Small mockable interface + helper class just for FakeIt tests
// // This lets you prove you used mocking without changing the rest of the project.
// // -----------------------------------------------------------------------------
// class IMessageSender
// {
// public:
//     virtual ~IMessageSender() = default;
//     virtual void sendMessage(const QString& message) = 0;
// };

// class ChatLogic
// {
// public:
//     explicit ChatLogic(IMessageSender* sender)
//         : m_sender(sender) {}

//     bool trySendMessage(const QString& message)
//     {
//         QString trimmed = message.trimmed();

//         if (trimmed.isEmpty())
//             return false;

//         m_sender->sendMessage(trimmed);
//         return true;
//     }

// private:
//     IMessageSender* m_sender;
// };

// // -----------------------------------------------------------------------------
// // Test class
// // -----------------------------------------------------------------------------
// class TestChatWindow : public QObject
// {
//     Q_OBJECT

// private slots:
//     void init();
//     void cleanup();

//     // Qt Test UI tests
//     void test_constructor_sets_room_title();
//     void test_chat_messages_is_read_only();
//     void test_send_button_adds_message();
//     void test_send_button_clears_input();
//     void test_empty_message_not_added();
//     void test_whitespace_message_not_added();
//     void test_return_pressed_sends_message();
//     void test_multiple_messages_are_appended();

//     // FakeIt mock tests
//     void test_fakeit_valid_message_calls_sender_once();
//     void test_fakeit_empty_message_does_not_call_sender();

// private:
//     chatWindow* window = nullptr;

//     QTextEdit* chatMessages() const
//     {
//         return window->findChild<QTextEdit*>("ChatMessages");
//     }

//     QLineEdit* inputBox() const
//     {
//         return window->findChild<QLineEdit*>("Inputbox");
//     }

//     QPushButton* sendButton() const
//     {
//         return window->findChild<QPushButton*>("sendMessages");
//     }

//     QLabel* chatRoomLabel() const
//     {
//         return window->findChild<QLabel*>("Chatroom");
//     }
// };

// void TestChatWindow::init()
// {
//     window = new chatWindow("Thermodynamics focus");
//     window->show();

//     QVERIFY(chatMessages() != nullptr);
//     QVERIFY(inputBox() != nullptr);
//     QVERIFY(sendButton() != nullptr);
//     QVERIFY(chatRoomLabel() != nullptr);
// }

// void TestChatWindow::cleanup()
// {
//     delete window;
//     window = nullptr;
// }

// void TestChatWindow::test_constructor_sets_room_title()
// {
//     QCOMPARE(chatRoomLabel()->text(), QString("Thermodynamics focus"));
// }

// void TestChatWindow::test_chat_messages_is_read_only()
// {
//     QVERIFY(chatMessages()->isReadOnly());
// }

// void TestChatWindow::test_send_button_adds_message()
// {
//     inputBox()->setText("Hello everyone");

//     QTest::mouseClick(sendButton(), Qt::LeftButton);

//     QString text = chatMessages()->toPlainText();
//     QVERIFY(text.contains("You: Hello everyone"));
// }

// void TestChatWindow::test_send_button_clears_input()
// {
//     inputBox()->setText("Testing clear");

//     QTest::mouseClick(sendButton(), Qt::LeftButton);

//     QCOMPARE(inputBox()->text(), QString(""));
// }

// void TestChatWindow::test_empty_message_not_added()
// {
//     inputBox()->setText("");

//     QString before = chatMessages()->toPlainText();

//     QTest::mouseClick(sendButton(), Qt::LeftButton);

//     QString after = chatMessages()->toPlainText();
//     QCOMPARE(after, before);
// }

// void TestChatWindow::test_whitespace_message_not_added()
// {
//     inputBox()->setText("     ");

//     QString before = chatMessages()->toPlainText();

//     QTest::mouseClick(sendButton(), Qt::LeftButton);

//     QString after = chatMessages()->toPlainText();
//     QCOMPARE(after, before);
// }

// void TestChatWindow::test_return_pressed_sends_message()
// {
//     inputBox()->setText("Sent with enter");

//     QTest::keyClick(inputBox(), Qt::Key_Return);

//     QString text = chatMessages()->toPlainText();
//     QVERIFY(text.contains("You: Sent with enter"));
// }

// void TestChatWindow::test_multiple_messages_are_appended()
// {
//     inputBox()->setText("First");
//     QTest::mouseClick(sendButton(), Qt::LeftButton);

//     inputBox()->setText("Second");
//     QTest::mouseClick(sendButton(), Qt::LeftButton);

//     QString text = chatMessages()->toPlainText();
//     QVERIFY(text.contains("You: First"));
//     QVERIFY(text.contains("You: Second"));
// }

// void TestChatWindow::test_fakeit_valid_message_calls_sender_once()
// {
//     Mock<IMessageSender> mockSender;

//     When(Method(mockSender, sendMessage)).AlwaysDo([](const QString&) {});

//     ChatLogic logic(&mockSender.get());

//     bool result = logic.trySendMessage("  Hello Qt  ");

//     QVERIFY(result);
//     Verify(Method(mockSender, sendMessage).Using(QString("Hello Qt"))).Once();
// }

// void TestChatWindow::test_fakeit_empty_message_does_not_call_sender()
// {
//     Mock<IMessageSender> mockSender;

//     When(Method(mockSender, sendMessage)).AlwaysDo([](const QString&) {});

//     ChatLogic logic(&mockSender.get());

//     bool result = logic.trySendMessage("     ");

//     QVERIFY(!result);
//     Verify(Method(mockSender, sendMessage)).Never();
// }

// QTEST_MAIN(TestChatWindow)
// #include "test_chatwindow.moc"
