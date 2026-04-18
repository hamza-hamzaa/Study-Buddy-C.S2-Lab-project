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
    ~CourseSelectionWindow();

    void setUserInfo(const QString& name, const QString& major);
    QList<QString> getSelectedCourses() const;

signals:
    void coursesSelected(const QList<QString>& courses);
    void backToLogin();

private slots:
    void on_BackButton_clicked();
    void on_NextButton_clicked();

private:
    Ui::CourseSelectionWindow *ui;
    QString m_name;
    QString m_major;
    void loadCourses();
};

#endif // COURSESELECTIONWINDOW_H
