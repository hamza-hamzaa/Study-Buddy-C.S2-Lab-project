#include "mainwindow.h"
#include"CourseSelectionWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_NextButton_clicked()
{
    QString Major=ui->MajorComboBox->currentText();
    this->hide();
    CourseSelectionWindow * CSW = new CourseSelectionWindow(Major, this);

    CSW -> show();
}

