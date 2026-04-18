#ifndef CLIENTCONTROLLER_H
#define CLIENTCONTROLLER_H

#include <QObject>
#include <QString>
#include <QList>
#include "networkclient.h"
#include "mainwindow.h"
#include "courseselectionwindow.h"
#include "chatselectionwindow.h"
#include "chatwindow.h"

class ClientController : public QObject {
    Q_OBJECT
public:
    explicit ClientController(NetworkClient* network, QObject *parent = nullptr);
    ~ClientController();

    void start();

    // For testing
    bool validateLogin(const QString& name, const QString& email, int id, const QString& major);
    bool validateCourses(const QList<QString>& courses);
    QString generateRoomId(const QString& course, bool focused);

public slots:
    // From MainWindow
    void onLoginRequested(const QString& name, const QString& email, int id, const QString& major);

    // From CourseSelectionWindow
    void onCoursesSelected(const QList<QString>& courses);
    void onBackToLogin();

    // From ChatSelectionWindow
    void onJoinRoomRequested(const QString& roomId);
    void onBackToCourses();

    // From ChatWindow
    void onChatMessageSent(const QString& content);
    void onBackToChatSelection();

    // From Network
    void onMessageReceived(const QJsonObject& message);

private:
    NetworkClient* m_network;
    MainWindow* m_mainWindow;
    CourseSelectionWindow* m_courseWindow;
    ChatSelectionWindow* m_chatSelectionWindow;
    chatWindow* m_chatWindow;

    QString m_username;
    QString m_major;
    QList<QString> m_selectedCourses;
    QString m_currentRoomId;
};

#endif // CLIENTCONTROLLER_H