#include "qtnetworkclient.h"
#include <QJsonDocument>
#include <QDataStream>

QtNetworkClient::QtNetworkClient(QObject *parent)
    : NetworkClient(parent), m_socket(new QTcpSocket(this)) {
    connect(m_socket, &QTcpSocket::connected, this, &QtNetworkClient::onConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &QtNetworkClient::onDisconnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &QtNetworkClient::onReadyRead);
    connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &QtNetworkClient::onErrorOccurred);
}

QtNetworkClient::~QtNetworkClient() {
    disconnectFromServer();
}

void QtNetworkClient::connectToServer(const QString& host, int port) {
    m_socket->connectToHost(host, port);
}

void QtNetworkClient::sendMessage(const QJsonObject& message) {
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        QJsonDocument doc(message);
        QByteArray data = doc.toJson(QJsonDocument::Compact) + "\n"; // assuming newline delimited
        m_socket->write(data);
    }
}

void QtNetworkClient::disconnectFromServer() {
    m_socket->disconnectFromHost();
}

void QtNetworkClient::onConnected() {
    emit connected();
}

void QtNetworkClient::onDisconnected() {
    emit disconnected();
}

void QtNetworkClient::onReadyRead() {
    m_buffer += m_socket->readAll();
    int pos;
    while ((pos = m_buffer.indexOf('\n')) != -1) {
        QByteArray line = m_buffer.left(pos);
        m_buffer = m_buffer.mid(pos + 1);
        QJsonDocument doc = QJsonDocument::fromJson(line);
        if (!doc.isNull() && doc.isObject()) {
            emit messageReceived(doc.object());
        }
    }
}

void QtNetworkClient::onErrorOccurred(QAbstractSocket::SocketError socketError) {
    emit errorOccurred(m_socket->errorString());
}