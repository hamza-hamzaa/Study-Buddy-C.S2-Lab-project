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
    explicit CourseSelectionWindow(QWidget *parent = nullptr);
    explicit CourseSelectionWindow(QString major, QWidget *parent = nullptr);

    ~CourseSelectionWindow();

private slots:
    void on_BackButton_clicked();

    void on_NextButton_clicked();


private:
    Ui::CourseSelectionWindow *ui;
    QString selectedMajor;
    void loadCourses();
    void limitSelection();
    std::vector<QString> names;
};

#endif // COURSESELECTIONWINDOW_H
