#ifndef CHATSELECTIONWINDOW_H
#define CHATSELECTIONWINDOW_H

#include <QDialog>

namespace Ui {
class ChatSelectionWindow;
}

class ChatSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatSelectionWindow(QWidget *parent = nullptr);
    explicit ChatSelectionWindow(QStringList courses, QWidget *parent = nullptr);
    ~ChatSelectionWindow();

private slots:
    void on_BackButton_clicked();

private:
    Ui::ChatSelectionWindow *ui;
    QStringList selectedCourses;
    void createCourseButtons();
};

#endif // CHATSELECTIONWINDOW_H
