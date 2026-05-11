#include "chatselectionwindow.h"
#include "chatwindow.h"
#include "ui_chatselectionwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

ChatSelectionWindow::ChatSelectionWindow(QString major,
                                         QString name,
                                         std::vector<QString> courses,
                                         QWidget *previousWindow,
                                         QWidget *parent)
    : QDialog(parent), ui(new Ui::ChatSelectionWindow), previousWindow(previousWindow)
{
    ui->setupUi(this);
    this->name=name;
    this->major=major;
    this->setWindowTitle(name+"'s Chats");
    selectedCourses = courses;
    createCourseButtons();
    this->setStyleSheet(
        "QWidget { background-color: #F5F7FA; color: #1F2933; }"
        "QFrame#leftPanel { background-color: white; border: 1px solid #D9E1E8; border-radius: 20px; }"
        "QFrame#focusPanel { background-color: #E8F0FE; border: 1px solid #B6CCF3; border-radius: 18px; }"
        "QPushButton { background-color: #1E71A8; color: white; border-radius: 10px; padding: 10px; }"
        "QPushButton:hover { background-color: #2A85C1; }"
        "QRadioButton { color: #1F2933; }");

    ui->groupBox->setStyleSheet(
        "QGroupBox {"
        "    background-color: rgb(219,219,219);"
        "    border-radius: 8px;"
        "    margin-top: 10px;"
        "}"
        "QGroupBox::title {"
        "    background-color: transparent;"
        "    color: white;"
        "    padding: 2px 6px;"
        "}"
        );
}

ChatSelectionWindow::~ChatSelectionWindow()
{
    delete ui;
}

void ChatSelectionWindow::createCourseButtons()
{
    QVBoxLayout *layout = new QVBoxLayout(ui->buttonContainer);
    QPushButton* btn1 = new QPushButton(major);
    btn1->setFixedHeight(20);
    btn1->setStyleSheet("background-color: #1e71a8; color: white; border-radius: 10px;");
    connect(btn1, &QPushButton::clicked,this, &ChatSelectionWindow::handleCourseButtonClick);
    layout->addWidget(btn1);

    for (size_t i = 0; i < selectedCourses.size(); i++) {
        QString course = selectedCourses[i];
        QPushButton* btn = new QPushButton(course);
        btn->setFixedHeight(20);
        btn->setStyleSheet("background-color: #1e71a8; color: white; border-radius: 10px;");
        connect(btn, &QPushButton::clicked,this, &ChatSelectionWindow::handleCourseButtonClick);
        layout->addWidget(btn);
    }
}

void ChatSelectionWindow::handleCourseButtonClick()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (!btn) {
        return;
    }

    if (!ui->focusRadioButton->isChecked() && !ui->notFocusRadioButton->isChecked()) {
        QMessageBox warningBox(this);
        warningBox.setIcon(QMessageBox::Warning);
        warningBox.setWindowTitle("Focus Mode");
        warningBox.setText("Please choose a focus mode.");
        warningBox.setStyleSheet(
            "QMessageBox { background-color: white; }"
            "QLabel { color: black; }"
            "QPushButton { background-color: #0078d7; color: white; border: none; border-radius: 10px; min-width: 72px; padding: 6px 16px; }"
            "QPushButton:hover { background-color: #2A85C1; }"
        );
        warningBox.exec();
        return;
    }

    QString course = btn->text();
    QString title;

    if (ui->focusRadioButton->isChecked()) {
        title = course + " focus";
    } else {
        title = course + " non focus";
    }

    chatwindow* window = new chatwindow(name, title, nullptr, this);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
    this->hide();
}

void ChatSelectionWindow::on_BackButton_clicked()
{
    if (previousWindow) {
        previousWindow->show();
    }
    close();
}
