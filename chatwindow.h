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
    explicit chatWindow(QString course,QWidget *parent = nullptr);
    ~chatWindow();

private slots:
    void on_backButton_clicked();
    void on_zoomButton_clicked();

private:
    Ui::chatWindow *ui;
};

#endif // CHATWINDOW_H
