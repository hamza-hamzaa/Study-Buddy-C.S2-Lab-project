#include "chatselectionwindow.h"
#include"chatwindow.h"
#include "ui_chatselectionwindow.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<QMessageBox>
ChatSelectionWindow::ChatSelectionWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatSelectionWindow)
{
    ui->setupUi(this);
}
ChatSelectionWindow::ChatSelectionWindow(std::vector<QString> courses, QWidget *parent): QDialog(parent), ui(new Ui::ChatSelectionWindow)
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

    for (size_t i = 0; i < selectedCourses.size(); i++) {
        QString course = selectedCourses[i];

        QPushButton* btn = new QPushButton(course);

        connect(btn, &QPushButton::clicked,
                this, &ChatSelectionWindow::handleCourseButtonClick);

        layout->addWidget(btn);
    }
}

void ChatSelectionWindow::handleCourseButtonClick()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());

    if (!btn) return;

    QString course = btn->text();
    if(ui->focusRadioButton->isChecked()){
        chatWindow* window = new chatWindow(course+ "focus",this);
        window->show();
        this->hide();
    }
    else if(ui->notFocusRadioButton->isChecked()){
        chatWindow* window = new chatWindow(course+ " non focus",this);
        window->show();
        this->hide();
    }
    else{
        QMessageBox::information(this, "Error", "Please select a focus mode");
    }


}

void ChatSelectionWindow::on_BackButton_clicked()
{

    parentWidget()->show();
    this->hide();
}

