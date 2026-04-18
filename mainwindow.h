#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void loginRequested(const QString& name, const QString& email, int id, const QString& major);

private slots:
    void on_NextButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
