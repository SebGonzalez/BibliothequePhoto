#ifndef AJOUTTAG_H
#define AJOUTTAG_H

#include <QDialog>

namespace Ui {
class AjoutTag;
}

class AjoutTag : public QDialog
{
    Q_OBJECT

public:
    explicit AjoutTag(QWidget *parent = 0);
    ~AjoutTag();
    std::string tagName;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AjoutTag *ui;
};

#endif // AJOUTTAG_H
