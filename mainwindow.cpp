#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("CG2 Projekt von Björn, Elmar und Michael");

    glWidget = new GLWidget;
    setCentralWidget(glWidget);

    resize(640, 480);
}

MainWindow::~MainWindow()
{
}
