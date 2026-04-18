#ifndef CHATSELECTIONWINDOW_H
#define CHATSELECTIONWINDOW_H

#include <QDialog>
#include<QString>
#include<vector>
namespace Ui {
class ChatSelectionWindow;
}

class ChatSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatSelectionWindow(QWidget *parent = nullptr);
    ~ChatSelectionWindow();

    void setUserInfo(const QString& name, const QString& major, const QList<QString>& courses);

signals:
    void joinRoomRequested(const QString& roomId);
    void backToCourses();

private slots:
    void on_BackButton_clicked();
    void handleCourseButtonClick();

private:
    Ui::ChatSelectionWindow *ui;
    QString m_name;
    QString m_major;
    QList<QString> m_selectedCourses;
    void createCourseButtons();
    QString generateRoomId(const QString& course, bool focused);
};

#endif // CHATSELECTIONWINDOW_H
