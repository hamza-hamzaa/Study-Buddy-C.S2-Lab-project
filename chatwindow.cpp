#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QDesktopServices>
#include <QUrl>

chatWindow::chatWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #1e71a8;");
}

void chatWindow::setRoomInfo(const QString& roomId, const QString& username) {
    m_roomId = roomId;
    m_username = username;
    this->setWindowTitle(roomId + " chat");
}

chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::on_backButton_clicked()
{
    emit backToChatSelection();
}

void chatWindow::on_zoomButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.zoom.com"));
}

