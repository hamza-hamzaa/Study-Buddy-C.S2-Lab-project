#include "mainwindow.h"
#include"CourseSelectionWindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>


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
    QMessageBox msg;
    QMessageBox msg1;
    QMessageBox msg2;
    QMessageBox msg3;
    msg3.setText("please enter a name");
    msg1.setText("Invalid ID");
    msg.setText("invalid Email");
    msg2.setText("Please Choose an actual major");
    msg.setStyleSheet(
        "QMessageBox { background-color: white; }"
        "QLabel { color: #1F2933; font-size: 12px; }"
        "QPushButton { background-color: #1E71A8; border-radius: 17px;}");
    msg1.setStyleSheet(
        "QMessageBox { background-color: white; }"
        "QLabel { color: #1F2933; font-size: 12px; }"
        "QPushButton { background-color: #1E71A8;  }");
    msg2.setStyleSheet(
        "QMessageBox { background-color: white; }"
        "QLabel { color: #1F2933; font-size: 12px; }"
        "QPushButton { background-color: #1E71A8;  }");
    msg3.setStyleSheet(
        "QMessageBox { background-color: white; }"
        "QLabel { color: #1F2933; font-size: 12px; }"
        "QPushButton { background-color: #1E71A8;  }");


    int ID =ui->IDEdit->text().toInt();
    QString Email=ui->EmailEdit->text();
    if(ui->nameEdit->text()!=""){
        if(checkEmail(Email)){
                if(checkID(ID)){
                    if(Major!="Major"){
                        this->hide();
                        CourseSelectionWindow * CSW = new CourseSelectionWindow(ui->nameEdit->text(),Major, this);
                        CSW -> show();
                    }
                else{
                    msg2.exec();
                }
            }
            else{
                msg1.exec();
            }

        }
        else{
            msg.exec();
        }
    }
    else{
        msg3.exec();
    }


}



bool MainWindow::checkID(int ID){
    if(ID/10000<90026&&ID/10000>90019){
        return true;
    }
    return false;
}
bool MainWindow::checkEmail(QString email)
{
    return email.endsWith("@aucegypt.edu");
}

