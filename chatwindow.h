#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QDialog>
#include<QString>
namespace Ui {
class chatWindow;
}

class chatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit chatWindow(QWidget *parent = nullptr);
    ~chatWindow();

    void setRoomInfo(const QString& roomId, const QString& username);

signals:
    void chatMessageSent(const QString& content);
    void backToChatSelection();

private slots:
    void on_backButton_clicked();
    void on_zoomButton_clicked();

private:
    Ui::chatWindow *ui;
    QString m_roomId;
    QString m_username;
};

#endif // CHATWINDOW_H
