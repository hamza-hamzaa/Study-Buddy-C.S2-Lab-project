
#include "courseselectionwindow.h"
#include "chatSelectionWindow.h"
#include "ui_courseselectionwindow.h"
#include<vector>
#include<QMessageBox>
#include<QListWidgetItem>

CourseSelectionWindow::CourseSelectionWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CourseSelectionWindow)
{
    ui->setupUi(this);

}

CourseSelectionWindow::CourseSelectionWindow(QString major, QWidget *parent): QDialog(parent), ui(new Ui::CourseSelectionWindow)
{
    ui->setupUi(this);
    selectedMajor = major;
    loadCourses();
    connect(ui->CourseListWidget, &QListWidget::itemSelectionChanged,this, &CourseSelectionWindow::limitSelection);
}

CourseSelectionWindow::~CourseSelectionWindow()
{
    delete ui;
}

void CourseSelectionWindow::on_BackButton_clicked()
{
    this->hide();
    parentWidget()->show();
}

void CourseSelectionWindow::loadCourses()
{
    ui->CourseListWidget->clear();
    /*
    ui->CourseListWidget->setStyleSheet(
        "QListWidget { background-color: #452f8f; color: black; }"
        "QListWidget::item { padding: 8px; }"
        "QListWidget::item:selected { background-color: #f8f7fa; }"
        );
*/
    if (selectedMajor == "Computer Science") {
        ui->CourseListWidget->addItem("CS1");
        ui->CourseListWidget->addItem("CS2");
        ui->CourseListWidget->addItem("Physics 1");
        ui->CourseListWidget->addItem("Calculus 1");
        ui->CourseListWidget->addItem("Calculus 2");
        ui->CourseListWidget->addItem("Calculus 3");
        ui->CourseListWidget->addItem("Calculus 7");
    }
    else if (selectedMajor == "Entrepreneurship") {
        ui->CourseListWidget->addItem("Intro to Business");
        ui->CourseListWidget->addItem("Marketing");
        ui->CourseListWidget->addItem("Accounting");
    }

}
//add major button
void CourseSelectionWindow::limitSelection() {
    QListWidgetItem* item = ui->CourseListWidget->currentItem();

    QString course = item->text();

    if (item->isSelected()) {
        // ADD case
        if (names.size() >= 6) {
            item->setSelected(false); // undo selection
            QMessageBox::warning(this, "Limit", "You can select a maximum of 6 courses.");
            return;
        }

        // avoid duplicates
        if (std::find(names.begin(), names.end(), course) == names.end()) {
            names.push_back(course);
        }
    }
     else {
        // REMOVE case
        auto it = std::find(names.begin(), names.end(), course);
        if (it != names.end()) {
            names.erase(it);
        }
    }
}





void CourseSelectionWindow::on_NextButton_clicked()
{


    this->hide();
    ChatSelectionWindow * CSW = new ChatSelectionWindow(names,this);
    CSW->show();
}


