
#include "courseselectionwindow.h"
#include "chatSelectionWindow.h"
#include "ui_courseselectionwindow.h"
#include<QMessageBox>
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
void CourseSelectionWindow::limitSelection(){
    QList<QListWidgetItem*> selected = ui->CourseListWidget->selectedItems();
    if (selected.size() > 6) {
        // Get the last selected item
        QListWidgetItem* item = ui->CourseListWidget->currentItem();
        if (item) {
            item->setSelected(false); // undo selection
        }
        QMessageBox::warning(this, "Limit","You can select a maximum of 6 courses.");
    }
}





void CourseSelectionWindow::on_NextButton_clicked()
{
    QStringList selectedCourses;

    QList<QListWidgetItem*> items = ui->CourseListWidget->selectedItems();

    for (QListWidgetItem* item : items) {
        selectedCourses.append(item->text());
    }

    this->hide();
    ChatSelectionWindow * CSW = new ChatSelectionWindow(selectedCourses,this);
    CSW->show();
}

