#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTest>

#include "chatwindow.h"

class TestChatWindow : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void constructor_setsRoomTitle();
    void chatMessages_isReadOnly();
    void sendButton_addsMessage();
    void sendButton_clearsInput();
    void emptyMessage_isIgnored();
    void whitespaceMessage_isIgnored();
    void multipleMessages_arePrepended();

private:
    chatwindow *window = nullptr;

    QTextEdit *chatMessages() const
    {
        return window->findChild<QTextEdit *>("ChatMessages");
    }

    QLineEdit *inputBox() const
    {
        return window->findChild<QLineEdit *>("Inputbox");
    }

    QPushButton *sendButton() const
    {
        return window->findChild<QPushButton *>("sendButton");
    }

    QLabel *chatRoomLabel() const
    {
        return window->findChild<QLabel *>("Chatroom");
    }
};

void TestChatWindow::init()
{
    window = new chatwindow("Student_01", "ROOM1", nullptr);
    window->show();

    QVERIFY(chatMessages() != nullptr);
    QVERIFY(inputBox() != nullptr);
    QVERIFY(sendButton() != nullptr);
    QVERIFY(chatRoomLabel() != nullptr);
}

void TestChatWindow::cleanup()
{
    delete window;
    window = nullptr;
}

void TestChatWindow::constructor_setsRoomTitle()
{
    QCOMPARE(chatRoomLabel()->text(), QString("ROOM1"));
}

void TestChatWindow::chatMessages_isReadOnly()
{
    QVERIFY(chatMessages()->isReadOnly());
}

void TestChatWindow::sendButton_addsMessage()
{
    inputBox()->setText("Hello everyone");

    QTest::mouseClick(sendButton(), Qt::LeftButton);

    QCOMPARE(chatMessages()->toPlainText(), QString("Student_01: Hello everyone"));
}

void TestChatWindow::sendButton_clearsInput()
{
    inputBox()->setText("Testing clear");

    QTest::mouseClick(sendButton(), Qt::LeftButton);

    QVERIFY(inputBox()->text().isEmpty());
}

void TestChatWindow::emptyMessage_isIgnored()
{
    inputBox()->setText("");

    const QString before = chatMessages()->toPlainText();
    QTest::mouseClick(sendButton(), Qt::LeftButton);

    QCOMPARE(chatMessages()->toPlainText(), before);
}

void TestChatWindow::whitespaceMessage_isIgnored()
{
    inputBox()->setText("     ");

    const QString before = chatMessages()->toPlainText();
    QTest::mouseClick(sendButton(), Qt::LeftButton);

    QCOMPARE(chatMessages()->toPlainText(), before);
}

void TestChatWindow::multipleMessages_arePrepended()
{
    inputBox()->setText("First");
    QTest::mouseClick(sendButton(), Qt::LeftButton);

    inputBox()->setText("Second");
    QTest::mouseClick(sendButton(), Qt::LeftButton);

    QCOMPARE(chatMessages()->toPlainText(), QString("Student_01: Second\nStudent_01: First"));
}

QTEST_MAIN(TestChatWindow)
#include "test_chatwindow.moc"
