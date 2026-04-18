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

    explicit ChatSelectionWindow(QString major,QString name,std::vector<QString> courses, QWidget *parent = nullptr);
    ~ChatSelectionWindow();

private slots:
    void on_BackButton_clicked();
    void handleCourseButtonClick();

private:
    Ui::ChatSelectionWindow *ui;
    std::vector<QString>selectedCourses;
    QString name;
    QString major;
    void createCourseButtons();
};

#endif // CHATSELECTIONWINDOW_H
