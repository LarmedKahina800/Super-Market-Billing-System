#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include <QPalette>
#include <QFont>
#include <fstream>

// -------- MainWindow constructor --------
MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    // set main window color
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(220, 240, 255)); // light blue background
    setAutoFillBackground(true);
    setPalette(pal);

    // Main vertical layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Input fields layout
    QHBoxLayout *inputLayout = new QHBoxLayout();
    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Product Name");
    priceEdit = new QLineEdit();
    priceEdit->setPlaceholderText("Price");
    qtyEdit = new QLineEdit();
    qtyEdit->setPlaceholderText("Quantity");

    nameEdit->setFixedWidth(150);
    priceEdit->setFixedWidth(100);
    qtyEdit->setFixedWidth(100);

    inputLayout->addWidget(nameEdit);
    inputLayout->addWidget(priceEdit);
    inputLayout->addWidget(qtyEdit);

    // Buttons layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *addButton = new QPushButton("Add Product");
    QPushButton *printButton = new QPushButton("Print Bill");

    addButton->setStyleSheet("background-color: green; color: white; font-weight: bold; height: 35px;");
    printButton->setStyleSheet("background-color: orange; color: white; font-weight: bold; height: 35px;");

    addButton->setFixedWidth(150);
    printButton->setFixedWidth(150);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(printButton);

    // Table for bill
    table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels({"Product", "Price", "Qty", "Total"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QFont headerFont;
    headerFont.setBold(true);
    table->horizontalHeader()->setFont(headerFont);

    // Total label
    totalLabel = new QLabel("Total: 0");
    totalLabel->setStyleSheet("font-weight: bold; font-size: 16px; color: darkblue;");

    // Add widgets to main layout
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(table);
    mainLayout->addWidget(totalLabel);

    // Connect buttons
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addProduct);
    connect(printButton, &QPushButton::clicked, this, &MainWindow::printBill);

    // set window title and size
    setWindowTitle("Supermarket Billing System");
    resize(600, 450);
}

// -------- Add Product slot --------
void MainWindow::addProduct() {
    Product p;
    QString name = nameEdit->text();
    QString priceStr = priceEdit->text();
    QString qtyStr = qtyEdit->text();

    if (name.isEmpty() || priceStr.isEmpty() || qtyStr.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all fields!");
        return;
    }

    int price = priceStr.toInt();
    int qty = qtyStr.toInt();

    p.setName(name.toStdString());
    p.setPrice(price);
    p.setQuantity(qty);

    // save to file
    ofstream out("Bill.txt", ios::app);
    if (out.is_open()) {
        out << p.getName() << " " << p.getPrice() << " " << p.getQuantity() << "\n";
        out.close();
    }

    QMessageBox::information(this, "Success", "Product added!");

    // clear input fields
    nameEdit->clear();
    priceEdit->clear();
    qtyEdit->clear();
}

// -------- Print Bill slot --------
void MainWindow::printBill() {
    table->setRowCount(0); // clear previous table
    ifstream in("Bill.txt");
    if (!in.is_open()) {
        QMessageBox::information(this, "Bill", "No bill found!");
        return;
    }

    string name;
    int price, qty;
    int total = 0;
    int row = 0;

    while (in >> name >> price >> qty) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(name)));
        table->setItem(row, 1, new QTableWidgetItem(QString::number(price)));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(qty)));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(price * qty)));
        total += price * qty;
        row++;
    }
    in.close();
    totalLabel->setText("Total: " + QString::number(total));
}
