#ifndef MAINWINDOW_APACHE_HEADER
#define MAINWINDOW_APACHE_HEADER

#include <QMainWindow>
#include <memory>
#include "ui_MainWindow.h"

namespace Ui {
    class MainWindow;  // forward declaration
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
    std::unique_ptr<Ui::MainWindow> ui;
public:
    MainWindow(QMainWindow* parent = nullptr);
    
private slots:
    void callback_calculate();
    void about();
    void mortality();
    void blank();
    
}; // class MainWindow

#endif // MAINWINDOW_APACHE_HEADER