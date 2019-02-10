#ifndef MAINWINDOWREDESIGNED_H
#define MAINWINDOWREDESIGNED_H

#include <QMainWindow>

namespace Ui {
class MainWindowRedesigned;
}

class MainWindowRedesigned : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowRedesigned(QWidget *parent = nullptr);
    ~MainWindowRedesigned();

private:
    Ui::MainWindowRedesigned *ui;

private slots:

    void load_selection_on_click();
    void import_on_click();


};

#endif // MAINWINDOWREDESIGNED_H
