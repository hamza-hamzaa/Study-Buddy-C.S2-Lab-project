#include "clientcontroller.h"
#include "mainwindow.h"
#include "courseselectionwindow.h"
#include "chatselectionwindow.h"
#include "chatwindow.h"
#include <QMessageBox>
#include <QJsonObject>
#include <QApplication>
#include <QRegularExpression>

ClientController::ClientController(NetworkClient* network, QObject *parent)
    : QObject(parent), m_network(network),
      m_mainWindow(new MainWindow()),
      m_courseWindow(new CourseSelectionWindow()),
      m_chatSelectionWindow(new ChatSelectionWindow()),
      m_chatWindow(new chatWindow())
{
    connect(m_mainWindow, &MainWindow::loginRequested, this, &ClientController::onLoginRequested);
    connect(m_courseWindow, &CourseSelectionWindow::coursesSelected, this, &ClientController::onCoursesSelected);
    connect(m_courseWindow, &CourseSelectionWindow::backToLogin, this, &ClientController::onBackToLogin);
    connect(m_chatSelectionWindow, &ChatSelectionWindow::joinRoomRequested, this, &ClientController::onJoinRoomRequested);
    connect(m_chatSelectionWindow, &ChatSelectionWindow::backToCourses, this, &ClientController::onBackToCourses);
    connect(m_chatWindow, &chatWindow::chatMessageSent, this, &ClientController::onChatMessageSent);
    connect(m_chatWindow, &chatWindow::backToChatSelection, this, &ClientController::onBackToChatSelection);
    connect(m_network, &NetworkClient::messageReceived, this, &ClientController::onMessageReceived);
}

ClientController::~ClientController() {
    delete m_mainWindow;
    delete m_courseWindow;
    delete m_chatSelectionWindow;
    delete m_chatWindow;
}

void ClientController::start() {
    m_mainWindow->show();
}

void ClientController::onLoginRequested(const QString& name, const QString& email, int id, const QString& major) {
    if (validateLogin(name, email, id, major)) {
        m_username = name;
        m_major = major;
        m_courseWindow->setUserInfo(name, major);
        m_courseWindow->show();
        m_mainWindow->hide();
    } else {
        QMessageBox::warning(m_mainWindow, "Invalid Login", "Please check your details.");
    }
}

void ClientController::onCoursesSelected(const QList<QString>& courses) {
    if (validateCourses(courses)) {
        m_selectedCourses = courses;
        m_chatSelectionWindow->setUserInfo(m_username, m_major, courses);
        m_chatSelectionWindow->show();
        m_courseWindow->hide();
    } else {
        QMessageBox::warning(m_courseWindow, "Invalid Selection", "Please select up to 6 courses.");
    }
}

void ClientController::onBackToLogin() {
    m_mainWindow->show();
    m_courseWindow->hide();
}

void ClientController::onJoinRoomRequested(const QString& roomId) {
    m_currentRoomId = roomId;
    m_chatWindow->setRoomInfo(roomId, m_username);
    m_chatWindow->show();
    m_chatSelectionWindow->hide();
    // Send join message
    QJsonObject joinMsg;
    joinMsg["action"] = "JOIN_GROUP";
    joinMsg["username"] = m_username;
    joinMsg["room_id"] = roomId;
    m_network->sendMessage(joinMsg);
}

void ClientController::onBackToCourses() {
    m_courseWindow->show();
    m_chatSelectionWindow->hide();
}

void ClientController::onChatMessageSent(const QString& content) {
    QJsonObject msg;
    msg["action"] = "CHAT_MSG";
    msg["room_id"] = m_currentRoomId;
    msg["sender"] = m_username;
    msg["content"] = content;
    m_network->sendMessage(msg);
}

void ClientController::onBackToChatSelection() {
    m_chatSelectionWindow->show();
    m_chatWindow->hide();
}

void ClientController::onMessageReceived(const QJsonObject& message) {
    QString action = message["action"].toString();
    if (action == "CHAT_MSG") {
        // Display in chat window
        // Assuming chatWindow has a method to add message
        // For now, just print or something
    }
}

bool ClientController::validateLogin(const QString& name, const QString& email, int id, const QString& major) {
    if (name.isEmpty()) return false;
    if (!email.endsWith("@aucegypt.edu")) return false;
    if (id / 10000 <= 90019 || id / 10000 >= 90026) return false;
    if (major == "Major") return false;
    return true;
}

bool ClientController::validateCourses(const QList<QString>& courses) {
    return courses.size() <= 6 && !courses.isEmpty();
}

QString ClientController::generateRoomId(const QString& course, bool focused) {
    QString simplified = course;
    simplified.remove(QRegularExpression("\\s+"));
    QString mode = focused ? "FOCUSED" : "CASUAL";
    return simplified + "_" + mode;
}