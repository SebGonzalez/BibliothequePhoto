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
    QString chosenDeletedtag = "";

    void init();
    void graphicsEffects(QPushButton *button);

private:
    Ui::tagDialog *ui;

public slots:

    void on_clickButton();
    void on_DeleteButton();
};

#endif // TAGDIALOG_H
