
#include "courseselectionwindow.h"
#include "chatSelectionWindow.h"
#include "ui_courseselectionwindow.h"
#include<vector>
#include<QMessageBox>
#include<QListWidgetItem>
#include<QSignalBlocker>

CourseSelectionWindow::CourseSelectionWindow(QString name,QString major, QWidget *parent): QDialog(parent), ui(new Ui::CourseSelectionWindow)
{
    ui->setupUi(this);
    selectedMajor = major;
    loadCourses();
    connect(ui->CourseListWidget, &QListWidget::itemSelectionChanged,
            this, &CourseSelectionWindow::limitSelection);

    connect(ui->CoreListWidget, &QListWidget::itemSelectionChanged,
            this, &CourseSelectionWindow::limitSelection);
    this->setWindowTitle("Course Selection");
    this->name=name;
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


    if (selectedMajor == "Computer Science") {
        ui->CourseListWidget->addItem("Fundamentals of Computing I");
        ui->CourseListWidget->addItem("Fundamentals of Computing II");
        ui->CourseListWidget->addItem("Fundamentals of Computing II Lab");
        ui->CourseListWidget->addItem("Discrete Structures");
        ui->CourseListWidget->addItem("Applied Data Structures");
        ui->CourseListWidget->addItem("Analysis and Design of Algorithms");
        ui->CourseListWidget->addItem("Analysis and Design of Algorithms Lab");
        ui->CourseListWidget->addItem("Computer Organization and Assembly Language Programming");
        ui->CourseListWidget->addItem("Fundamentals of Database Systems");
        ui->CourseListWidget->addItem("Operating Systems");
        ui->CourseListWidget->addItem("Computer Networks");
        ui->CourseListWidget->addItem("Computer Networks Lab");
        ui->CourseListWidget->addItem("Software Engineering");
        ui->CourseListWidget->addItem("Theory of Computing");
        ui->CourseListWidget->addItem("Programming Language Concepts");
        ui->CourseListWidget->addItem("Distributed Systems");
        ui->CourseListWidget->addItem("Senior Project I");
        ui->CourseListWidget->addItem("Senior Project II");
        ui->CourseListWidget->addItem("Industrial Training");
        ui->CourseListWidget->addItem("Artificial Intelligence");
        ui->CourseListWidget->addItem("Machine Learning");
        ui->CourseListWidget->addItem("Advanced Machine Learning");
        ui->CourseListWidget->addItem("Computer Vision");
        ui->CourseListWidget->addItem("Data Mining");
        ui->CourseListWidget->addItem("Artificial Neural Networks");
        ui->CourseListWidget->addItem("Introduction to Cybersecurity");
        ui->CourseListWidget->addItem("Network Security");
        ui->CourseListWidget->addItem("Digital Forensics");
        ui->CourseListWidget->addItem("Web Security");
        ui->CourseListWidget->addItem("Secure Systems Engineering");
        ui->CourseListWidget->addItem("Embedded Systems");
        ui->CourseListWidget->addItem("Internet of Things Networking Protocols");
        ui->CourseListWidget->addItem("Big Data Systems");
        ui->CourseListWidget->addItem("Compiler Design");
        ui->CourseListWidget->addItem("Design of Web-based Systems");
        ui->CourseListWidget->addItem("Digital Game Design");
        ui->CourseListWidget->addItem("Selected Topics in Computer Science");
        ui->CourseListWidget->addItem("Guided Studies in Computer Science");

    }
    else if (selectedMajor == "Computer Engineering") {
        ui->CourseListWidget->addItem("Probability and Statistics");
        ui->CourseListWidget->addItem("Physics 1: Classical Mechanics, Sound and Heat");
        ui->CourseListWidget->addItem("General Physics Laboratory I");
        ui->CourseListWidget->addItem("Physics 2: Electricity and Magnetism");
        ui->CourseListWidget->addItem("General Physics Laboratory II");
        ui->CourseListWidget->addItem("Introduction to Electronics");
        ui->CourseListWidget->addItem("Electronics Lab");
        ui->CourseListWidget->addItem("Fundamentals of Computing I");
        ui->CourseListWidget->addItem("Fundamentals of Computing II");
        ui->CourseListWidget->addItem("Fundamentals of Computing II Lab");
        ui->CourseListWidget->addItem("Analysis and Design of Algorithms");
        ui->CourseListWidget->addItem("Analysis and Design of Algorithms Lab");
        ui->CourseListWidget->addItem("Applied Data Structures");
        ui->CourseListWidget->addItem("Digital Design I");
        ui->CourseListWidget->addItem("Digital Design I Lab");
        ui->CourseListWidget->addItem("Computer Organization and Assembly Language Programming");
        ui->CourseListWidget->addItem("Fundamentals of Database Systems");
        ui->CourseListWidget->addItem("Computer Architecture");
        ui->CourseListWidget->addItem("Computer Architecture Lab");
        ui->CourseListWidget->addItem("Fundamental Microelectronics");
        ui->CourseListWidget->addItem("Digital Design II");
        ui->CourseListWidget->addItem("Computer Networks");
        ui->CourseListWidget->addItem("Computer Networks Lab");
        ui->CourseListWidget->addItem("Operating Systems");
        ui->CourseListWidget->addItem("Digital Signal Processing");
        ui->CourseListWidget->addItem("Software Engineering");
        ui->CourseListWidget->addItem("Embedded Systems");
        ui->CourseListWidget->addItem("Embedded Systems Lab");
        ui->CourseListWidget->addItem("Fundamentals of Distributed Systems");
        ui->CourseListWidget->addItem("Industrial Training");
        ui->CourseListWidget->addItem("Senior Project I");
        ui->CourseListWidget->addItem("Senior Project II");
        ui->CourseListWidget->addItem("Embedded Systems on Chip Design");
        ui->CourseListWidget->addItem("Internet of Things Networking Protocols");
        ui->CourseListWidget->addItem("Selected Topics in Computer Science and Engineering");
        ui->CourseListWidget->addItem("Fundamentals of Artificial Intelligence");
        ui->CourseListWidget->addItem("Fundamentals of Machine Learning");
        ui->CourseListWidget->addItem("Introduction to Artificial Neural Networks");
        ui->CourseListWidget->addItem("Fundamentals of Computer Vision");
        ui->CourseListWidget->addItem("Advanced Machine Learning");
        ui->CourseListWidget->addItem("Fundamentals of Data Mining");
        ui->CourseListWidget->addItem("Introduction to Cybersecurity");
        ui->CourseListWidget->addItem("Network Security");
        ui->CourseListWidget->addItem("Digital Forensics");
        ui->CourseListWidget->addItem("Web Security");
        ui->CourseListWidget->addItem("Secure Systems Engineering");
        ui->CourseListWidget->addItem("Programming Language");
        ui->CourseListWidget->addItem("Programming in Java");
        ui->CourseListWidget->addItem("Object Oriented Programming");
        ui->CourseListWidget->addItem("Concepts of Programming Languages");
        ui->CourseListWidget->addItem("Data and Computer Communications");
        ui->CourseListWidget->addItem("Compiler Design");
        ui->CourseListWidget->addItem("Theory of Computing");
        ui->CourseListWidget->addItem("Big Data Systems");
        ui->CourseListWidget->addItem("Design of Web-based Systems");


    }
    else if (selectedMajor == "Mechanical Engineering") {
        ui->CourseListWidget->addItem("Engineering Mechanics");
        ui->CourseListWidget->addItem("Engineering Analysis and Computation");
        ui->CourseListWidget->addItem("Probability and Statistics");
        ui->CourseListWidget->addItem("Physics 1: Classical Mechanics, Sound and Heat");
        ui->CourseListWidget->addItem("General Physics Laboratory I");
        ui->CourseListWidget->addItem("Physics 2: Electricity and Magnetism");
        ui->CourseListWidget->addItem("General Physics Laboratory II");
        ui->CourseListWidget->addItem("Waves and Optics");
        ui->CourseListWidget->addItem("Introduction to Electronics");
        ui->CourseListWidget->addItem("Thermodynamics");
        ui->CourseListWidget->addItem("Fluid Mechanics");
        ui->CourseListWidget->addItem("Heat Transfer");
        ui->CourseListWidget->addItem("Dynamics");
        ui->CourseListWidget->addItem("Mechanics of Materials");
        ui->CourseListWidget->addItem("System Dynamics");
        ui->CourseListWidget->addItem("Automatic Control Systems");
        ui->CourseListWidget->addItem("Manufacturing Processes");
        ui->CourseListWidget->addItem("Materials Engineering");
        ui->CourseListWidget->addItem("Machine Design");
        ui->CourseListWidget->addItem("Engineering Design");
        ui->CourseListWidget->addItem("Mechatronics Systems");
        ui->CourseListWidget->addItem("Microcontrollers and Embedded Systems");
        ui->CourseListWidget->addItem("Energy Systems Engineering");
        ui->CourseListWidget->addItem("Industrial Engineering Fundamentals");
        ui->CourseListWidget->addItem("Senior Project I");
        ui->CourseListWidget->addItem("Senior Project II");
        ui->CourseListWidget->addItem("Industrial Internship");
        ui->CourseListWidget->addItem("Solar Energy Systems");
        ui->CourseListWidget->addItem("Power Plant Engineering");
        ui->CourseListWidget->addItem("Refrigeration and Air Conditioning");
        ui->CourseListWidget->addItem("Finite Element Analysis");
        ui->CourseListWidget->addItem("Advanced Machine Design");
        ui->CourseListWidget->addItem("Composite Materials");
        ui->CourseListWidget->addItem("Manufacturing Systems");
        ui->CourseListWidget->addItem("Automation and Robotics");
        ui->CourseListWidget->addItem("Integrated Electromechanical Systems");
        ui->CourseListWidget->addItem("Robotics Design and Control");
        ui->CourseListWidget->addItem("Selected Topics in Mechanical Engineering");

    }
    else if (selectedMajor == "Electronics Engineering") {
        ui->CourseListWidget->addItem("General Chemistry I");
        ui->CourseListWidget->addItem("General Chemistry I-Laboratory");
        ui->CourseListWidget->addItem("Fundamentals of Computing I");
        ui->CourseListWidget->addItem("Descriptive Geometry and Engineering Drawing");
        ui->CourseListWidget->addItem("Engineering Mechanics");
        ui->CourseListWidget->addItem("Engineering Analysis and Computation I");
        ui->CourseListWidget->addItem("Calculus II");
        ui->CourseListWidget->addItem("Calculus III");
        ui->CourseListWidget->addItem("Differential Equations");
        ui->CourseListWidget->addItem("Probability and Statistics");
        ui->CourseListWidget->addItem("Physics 1: Classical Mechanics, Sound and Heat");
        ui->CourseListWidget->addItem("General Physics Laboratory I");
        ui->CourseListWidget->addItem("Physics 2: Electricity and Magnetism");
        ui->CourseListWidget->addItem("General Physics Laboratory II");
        ui->CourseListWidget->addItem("Waves and Optics");
        ui->CourseListWidget->addItem("Exploring Electrical Engineering");
        ui->CourseListWidget->addItem("Programming Elements for Electrical Engineering");
        ui->CourseListWidget->addItem("Digital Logic Design");
        ui->CourseListWidget->addItem("Circuit Analysis I");
        ui->CourseListWidget->addItem("Circuit Analysis II");
        ui->CourseListWidget->addItem("Digital Logic Design Lab");
        ui->CourseListWidget->addItem("Circuit Analysis Lab");
        ui->CourseListWidget->addItem("Electronics I: Basic Electronic Devices & Circuits");
        ui->CourseListWidget->addItem("Electronics II: Analog Circuits");
        ui->CourseListWidget->addItem("VLSI Design");
        ui->CourseListWidget->addItem("Electronics Lab");
        ui->CourseListWidget->addItem("Signals and Systems");
        ui->CourseListWidget->addItem("Automatic Control Systems");
        ui->CourseListWidget->addItem("Electromagnetic Theory");
        ui->CourseListWidget->addItem("Microcontroller system design");
        ui->CourseListWidget->addItem("Microcontroller system design lab");
        ui->CourseListWidget->addItem("Power and Machines");
        ui->CourseListWidget->addItem("Technological Innovation and Product Development");
        ui->CourseListWidget->addItem("Fundamentals of Communications I");
        ui->CourseListWidget->addItem("Fundamentals of Communications II");
        ui->CourseListWidget->addItem("Computer Communication Networks");
        ui->CourseListWidget->addItem("Communications Lab");
        ui->CourseListWidget->addItem("Electromagnetic Waves");
        ui->CourseListWidget->addItem("Embedded Systems for Wireless Communications");
        ui->CourseListWidget->addItem("Senior Project I");
        ui->CourseListWidget->addItem("Senior Project II");
        ui->CourseListWidget->addItem("Industrial Internship");
        ui->CourseListWidget->addItem("Solid-State Devices");
        ui->CourseListWidget->addItem("Testing of Digital Circuits");
        ui->CourseListWidget->addItem("High Level Digital ASIC Design Using CAD");
        ui->CourseListWidget->addItem("Integrated Circuit Fabrication: Materials and Processes");
        ui->CourseListWidget->addItem("Photonics and Optical Communication Laboratory");
        ui->CourseListWidget->addItem("Telecommunications Systems");
        ui->CourseListWidget->addItem("Optical Communication Systems");
        ui->CourseListWidget->addItem("Mobile Communication Systems");
        ui->CourseListWidget->addItem("Microwave Systems");
        ui->CourseListWidget->addItem("Computer Architecture");
        ui->CourseListWidget->addItem("Industrial control systems");
        ui->CourseListWidget->addItem("Computer Architecture Lab");
        ui->CourseListWidget->addItem("Fundamentals of Wireless Sensor Networks");
        ui->CourseListWidget->addItem("Selected Topics in Electronics and Communications Engineering");
        ui->CourseListWidget->addItem("Special Problems in Electronics and Communications Engineering");

    }


}

void CourseSelectionWindow::limitSelection()
{
    QList<QListWidgetItem*> selectedCourses = ui->CourseListWidget->selectedItems();
    QList<QListWidgetItem*> selectedCore = ui->CoreListWidget->selectedItems();

    int totalSelected = selectedCourses.size() + selectedCore.size();

    if (totalSelected > 6) {
        // Block BOTH widgets to avoid signal recursion
        QSignalBlocker blocker1(ui->CourseListWidget);
        QSignalBlocker blocker2(ui->CoreListWidget);

        // Figure out which widget triggered this
        QListWidget* senderWidget = qobject_cast<QListWidget*>(sender());

        if (senderWidget) {
            QListWidgetItem* item = senderWidget->currentItem();
            if (item) {
                item->setSelected(false); // undo last selection
            }
        }

        QMessageBox msg;
        msg.setIcon(QMessageBox::Warning);
        msg.setWindowTitle("Limit");
        msg.setText("You can select a maximum of 6 courses.");
        msg.setStyleSheet(
            "QMessageBox { background-color: white; }"
            "QLabel { color: black; }"
            "QPushButton { background-color: #0078d7; color: white; }"
            );
        msg.exec();
    }


    names.clear();

    for (QListWidgetItem* item : ui->CourseListWidget->selectedItems()) {
        names.push_back(item->text());
    }

    for (QListWidgetItem* item : ui->CoreListWidget->selectedItems()) {
        names.push_back(item->text());
    }
}


void CourseSelectionWindow::on_NextButton_clicked()
{
    this->hide();
    ChatSelectionWindow * CSW = new ChatSelectionWindow(selectedMajor,name,names,this);
    CSW->show();
}


