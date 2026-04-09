#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QDesktopServices>
#include <QUrl>

chatWindow::chatWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatWindow)
{
    ui->setupUi(this);
}
chatWindow::chatWindow(QString course ,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::chatWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: lightblue;");
    this->setWindowTitle(course+" window");

}
chatWindow::~chatWindow()
{
    delete ui;
}

void chatWindow::on_backButton_clicked()
{
    parentWidget()->show();
    this->hide();
}


void chatWindow::on_zoomButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.zoom.com"));

}

