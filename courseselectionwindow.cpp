#include "courseselectionwindow.h"
#include "ui_courseselectionwindow.h"

CourseSelectionWindow::CourseSelectionWindow(QWidget *parent): QDialog(parent), ui(new Ui::CourseSelectionWindow)
{
    ui->setupUi(this);
    loadCourses();
    this->setWindowTitle("Course Selection");
}

CourseSelectionWindow::~CourseSelectionWindow()
{
    delete ui;
}

void CourseSelectionWindow::setUserInfo(const QString& name, const QString& major)
{
    m_name = name;
    m_major = major;
    loadCourses();
}

void CourseSelectionWindow::on_BackButton_clicked()
{
    emit backToLogin();
}

void CourseSelectionWindow::on_NextButton_clicked()
{
    QList<QString> selected = getSelectedCourses();
    if (!selected.isEmpty()) {
        emit coursesSelected(selected);
    }
}

void CourseSelectionWindow::loadCourses()
{
    ui->CourseListWidget->clear();
    ui->CourseListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CourseListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CourseListWidget->setStyleSheet(
        "QListWidget {background-color: rgb(219,219,219); color: black;}"
        "QListWidget::item {  border-bottom: 1px solid white;  padding: 8px;}"
        "QListWidget::item:selected{ background-color: #1e71a8; color: white;}"
        );
    ui->CoreListWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CoreListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->CoreListWidget->setStyleSheet(
        "QListWidget {background-color: rgb(219,219,219); color: black;}"
        "QListWidget::item {  border-bottom: 1px solid white;  padding: 8px;}"
        "QListWidget::item:selected{ background-color: #1e71a8; color: white;}"
        );
    ui->CoreListWidget->addItem("Rhetoric and Composition I");
    ui->CoreListWidget->addItem("Rhetoric and Composition II");
    ui->CoreListWidget->addItem("Freshman Seminar");
    ui->CoreListWidget->addItem("Critical Thinking");
    ui->CoreListWidget->addItem("Scientific Thinking");
    ui->CoreListWidget->addItem("Humanities and Arts");
    ui->CoreListWidget->addItem("Social Sciences");
    ui->CoreListWidget->addItem("Global Perspectives");
    ui->CoreListWidget->addItem("Ethics and Civic Engagement");

    // Add some courses
    ui->CourseListWidget->addItem("CSCE 1101");
    ui->CourseListWidget->addItem("CSCE 1102");
    ui->CourseListWidget->addItem("CSCE 2101");
    ui->CourseListWidget->addItem("CSCE 2102");
    ui->CourseListWidget->addItem("CSCE 3101");
    ui->CourseListWidget->addItem("CSCE 3102");
    ui->CourseListWidget->addItem("CSCE 4101");
    ui->CourseListWidget->addItem("CSCE 4102");
}

QList<QString> CourseSelectionWindow::getSelectedCourses() const {
    QList<QString> selected;
    for (QListWidgetItem* item : ui->CourseListWidget->selectedItems()) {
        selected.append(item->text());
    }
    for (QListWidgetItem* item : ui->CoreListWidget->selectedItems()) {
        selected.append(item->text());
    }
    return selected;
}