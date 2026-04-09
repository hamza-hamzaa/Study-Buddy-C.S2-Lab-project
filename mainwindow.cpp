#include "mainwindow.h"
#include"CourseSelectionWindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: #fcfcfc;");
    this->setWindowTitle("Login Window");
    ui->nameLabel->setStyleSheet("color: #000000;");
    ui->EmailLabel->setStyleSheet("color: #000000;");
    ui->IDLabel->setStyleSheet("color: #000000;");
    ui->majorLabel->setStyleSheet("color: #000000;");
    ui->label->setStyleSheet("color: #000000;");

    ui->nameEdit->setStyleSheet( "QLineEdit {background-color: #1E71A8;  border: 1px solid black;}");
    ui->EmailEdit->setStyleSheet( "QLineEdit {background-color: #1E71A8;  border: 1px solid black; }");
    ui->IDEdit->setStyleSheet( "QLineEdit {background-color: #1E71A8;  border: 1px solid black; }");


    ui->MajorComboBox->setStyleSheet(
        "QComboBox { background-color: #1E71a8 ; color: white; }"
        "QComboBox QAbstractItemView { background-color: #1e1e1e; color: lightblue; }"
        );
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

