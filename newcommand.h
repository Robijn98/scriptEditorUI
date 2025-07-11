#ifndef NEWCOMMAND_H
#define NEWCOMMAND_H

#include <QDialog>

namespace Ui {
class NewCommand;
}

class NewCommand : public QDialog
{
    Q_OBJECT

public:
    explicit NewCommand(QWidget *parent = nullptr);
    ~NewCommand();

private slots:
    void on_saveButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::NewCommand *ui;
};

#endif // NEWCOMMAND_H
