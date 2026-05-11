#ifndef COURSESELECTIONWINDOW_H
#define COURSESELECTIONWINDOW_H

#include <QDialog>
#include<QString>
#include<QListWidgetItem>
namespace Ui {
class CourseSelectionWindow;
}

class CourseSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CourseSelectionWindow(QString name,
                                   QString major,
                                   QWidget *previousWindow = nullptr,
                                   QWidget *parent = nullptr);
    ~CourseSelectionWindow();

private slots:
    void on_BackButton_clicked();
    void on_NextButton_clicked();


private:
    Ui::CourseSelectionWindow *ui;
    QWidget *previousWindow;
    std::vector<QString> names;
    QString selectedMajor;
    QString name;
    bool limitWarningPending = false;
    void loadCourses();
    void limitSelection();


};

#endif // COURSESELECTIONWINDOW_H
