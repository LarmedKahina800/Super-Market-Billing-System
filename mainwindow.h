#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// -------- Product class --------
class Product {
private:
    string name;
    int price;
    int quantity;

public:
    Product() : name(""), price(0), quantity(0) {}
    void setName(string n) { name = n; }
    void setPrice(int p) { price = p; }
    void setQuantity(int q) { quantity = q; }
    string getName() { return name; }
    int getPrice() { return price; }
    int getQuantity() { return quantity; }
};

// -------- MainWindow class --------
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void addProduct();
    void printBill();

private:
    QLineEdit *nameEdit;
    QLineEdit *priceEdit;
    QLineEdit *qtyEdit;
    QTableWidget *table;
    QLabel *totalLabel;
};

#endif // MAINWINDOW_H
