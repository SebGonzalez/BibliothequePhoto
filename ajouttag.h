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

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::AjoutTag *ui;
    bool asBeenChanged = false;
};

#endif // AJOUTTAG_H
