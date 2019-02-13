#ifndef TAGDIALOG_H
#define TAGDIALOG_H

#include <QDialog>
#include "bibliotheque.h"
namespace Ui {
class tagDialog;
}

class tagDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tagDialog(QWidget *parent = nullptr);

    tagDialog(Bibliotheque bibliotheque);
    ~tagDialog();

    Bibliotheque biblio_;
    std::vector<string> tags;
    QString chosen_tag = "";

    void init();
private:
    Ui::tagDialog *ui;

public slots:

    void on_click_button();
};

#endif // TAGDIALOG_H
