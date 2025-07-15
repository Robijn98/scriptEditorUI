#include "editCommand.h"
#include "ui_editCommand.h"

#include <QTextStream>
#include <QMessageBox>

EditCommand::EditCommand(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditCommand)
{
    ui->setupUi(this);
    this->setWindowTitle("Edit rigging command");
    this->setStyleSheet(
        "color:#fff5fb;"
        "background-color:#1f1f1f;"

        );
    ui->cancelButton->setStyleSheet(
        "background-color:black;"
        "border-style: solid;"
        "border-width: 2px;"
        "border-radius: 5px;"
        "border-color: #e36db4;"
        "font: bold 14px;"
        "min-width: 6em;"
        "padding: 6px;"

        );
    ui->saveButton->setStyleSheet(
        "background-color:black;"
        "border-style: solid;"
        "border-width: 2px;"
        "border-radius: 5px;"
        "border-color: #e36db4;"
        "font: bold 14px;"
        "min-width: 6em;"
        "padding: 6px;"
        );
    ui->saveButton->setStyleSheet(
        "background-color:black;"
        "border-style: solid;"
        "border-width: 2px;"
        "border-radius: 5px;"
        "border-color: #e36db4;"
        "font: bold 14px;"
        "min-width: 6em;"
        "padding: 6px;"
        );

    ui->browseButton->setStyleSheet(
        "background-color:black;"
        "border-style: solid;"
        "border-width: 2px;"
        "border-radius: 5px;"
        "border-color: #e36db4;"
        "font: bold 14px;"
        "min-width: 6em;"
        "padding: 6px;"
        );
}
EditCommand::~EditCommand()
{
    delete ui;
}

void EditCommand::on_browseButton_clicked()
{
    //FIX PREDEFINED
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "C:/Users/robin/OneDrive/Documents/ScriptEditor/riggingCommands/", "All Files (*.*)");
    if (!fileName.isEmpty()) {
        ui->label->setText(fileName);
    }
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        ui->editor->setPlainText(in.readAll());
        file.close();
    }
}



void EditCommand::on_saveButton_clicked()
{
    QString fileName = ui->label->text();
    //QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << ui->editor->toPlainText();
        file.close();
        this->close();

    }
}


void EditCommand::on_cancelButton_clicked()
{
    this->close();
}
