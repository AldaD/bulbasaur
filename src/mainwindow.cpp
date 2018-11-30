#include "mainwindow.h"
DWIDGET_USE_NAMESPACE
MainWindow::MainWindow(QWidget *parent)
    : DMainWindow(parent)
{
    setMinimumSize(QSize(800, 600));
}

MainWindow::~MainWindow()
{

}
