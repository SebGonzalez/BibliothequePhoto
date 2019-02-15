#ifndef CONFIRMDELETE_H
#define CONFIRMDELETE_H

#include <QDialog>

namespace Ui {
class confirmDelete;
}

class confirmDelete : public QDialog
{
    Q_OBJECT

public:
    explicit confirmDelete(QWidget *parent = nullptr);
    ~confirmDelete();
    bool getValue();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::confirmDelete *ui;
    bool confirm;
};

#endif // CONFIRMDELETE_H
