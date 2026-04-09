#include "chatselectionwindow.h"
#include "ui_chatselectionwindow.h"
#include<QVBoxLayout>
#include<QPushButton>
ChatSelectionWindow::ChatSelectionWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatSelectionWindow)
{
    ui->setupUi(this);
}
ChatSelectionWindow::ChatSelectionWindow(QStringList courses, QWidget *parent): QDialog(parent), ui(new Ui::ChatSelectionWindow)
{
    ui->setupUi(this);

    selectedCourses = courses;
    createCourseButtons();
}

ChatSelectionWindow::~ChatSelectionWindow()
{
    delete ui;

}
void ChatSelectionWindow::createCourseButtons()
{
    QVBoxLayout *layout = new QVBoxLayout(ui->buttonContainer);

    for (const QString &course : selectedCourses) {
        QPushButton *btn = new QPushButton(course, this);
        layout->addWidget(btn);

    }
}

void ChatSelectionWindow::on_BackButton_clicked()
{
    parentWidget()->show();
    this->hide();
}

