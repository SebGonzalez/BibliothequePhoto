#ifndef VIEWER_H
#define VIEWER_H

#include <QMainWindow>

namespace Ui {
class viewer;
}

class viewer : public QMainWindow
{
    Q_OBJECT

public:
    explicit viewer(QWidget *parent = nullptr);
    ~viewer();

private slots:
    void on_zoom_clicked();

    void on_zoomOut_clicked();

    void on_rotate_clicked();

    void on_info_clicked();

private:
    Ui::viewer *ui;
};

#endif // VIEWER_H
