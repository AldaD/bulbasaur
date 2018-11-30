#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DMainWindow>
class MainWindow : public DTK_WIDGET_NAMESPACE::DMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
