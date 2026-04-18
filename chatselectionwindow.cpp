#include "chatselectionwindow.h"
#include"chatwindow.h"
#include "ui_chatselectionwindow.h"
#include<QVBoxLayout>
#include<QPushButton>
#include<QMessageBox>
#include<QRegularExpression>

ChatSelectionWindow::ChatSelectionWindow(QWidget *parent): QDialog(parent), ui(new Ui::ChatSelectionWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chat Selection");
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

void ChatSelectionWindow::setUserInfo(const QString& name, const QString& major, const QList<QString>& courses) {
    m_name = name;
    m_major = major;
    m_selectedCourses = courses;
    this->setWindowTitle(name + "'s Chats");
    createCourseButtons();
}

void ChatSelectionWindow::createCourseButtons()
{
    QVBoxLayout *layout = new QVBoxLayout(ui->buttonContainer);
    QPushButton* btn1 = new QPushButton(m_major);
    btn1->setFixedHeight(20);
    btn1->setStyleSheet("background-color: #1e71a8; color: white; border-radius: 10px;");
    connect(btn1, &QPushButton::clicked,this, &ChatSelectionWindow::handleCourseButtonClick);
    layout->addWidget(btn1);

    for (int i = 0; i < m_selectedCourses.size(); i++) {
        QString course = m_selectedCourses[i];
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
    if (!btn) return;

    if (!ui->focusRadioButton->isChecked() && !ui->notFocusRadioButton->isChecked()) {
        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Focus Mode");
        msg.setText("Please choose a focus mode.");
        msg.setStyleSheet(
            "QMessageBox { background-color: white; }"
            "QLabel { color: black; }"
            "QPushButton { background-color: #0078d7; color: white; }"
            );
        msg.exec();
        return;
    }

    QString course = btn->text();
    bool focused = ui->focusRadioButton->isChecked();
    QString roomId = generateRoomId(course, focused);
    emit joinRoomRequested(roomId);
}

QString ChatSelectionWindow::generateRoomId(const QString& course, bool focused) {
    // Simplify course name, e.g., "CSCE 1102" -> "CSCE1102"
    QString simplified = course;
    simplified.remove(QRegularExpression("\\s+"));
    QString mode = focused ? "FOCUSED" : "CASUAL";
    return simplified + "_" + mode;
}

void ChatSelectionWindow::on_BackButton_clicked()
{
    emit backToCourses();
}

