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
    explicit CourseSelectionWindow(QString name,QString major, QWidget *parent = nullptr);
    ~CourseSelectionWindow();

private slots:
    void on_BackButton_clicked();
    void on_NextButton_clicked();


private:
    Ui::CourseSelectionWindow *ui;
    std::vector<QString> names;
    QString selectedMajor;
    QString name;
    void loadCourses();
    void limitSelection();


};

#endif // COURSESELECTIONWINDOW_H
