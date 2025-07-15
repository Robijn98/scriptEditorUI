#include "newCommand.h"
#include "ui_newCommand.h"

#include <QTextStream>
#include <QFileDialog>
#include <qmessagebox.h>

NewCommand::NewCommand(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCommand)
{
    ui->setupUi(this);
    this->setWindowTitle("New rigging command");
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

}

NewCommand::~NewCommand()
{
    delete ui;
}

void NewCommand::on_saveButton_clicked()
{
    // Get the file name from the line edit
    QString fileNamed = ui->fileNameLine->text().trimmed();
    if (fileNamed.isEmpty()) {
        QMessageBox::warning(this, "Invalid Filename", "Please enter a file name");
        return;
    }

    // FIX PREDEFINED
    QString baseDir = "C:/Users/robin/OneDrive/Documents/ScriptEditor/riggingCommands/";
    QString filePath = baseDir + fileNamed;

    // Check if the file already exists
    if (QFile::exists(filePath)) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "File Exists",
                                      "A file with that name already exists. Overwrite?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply != QMessageBox::Yes)
            return;
    }

    // Write to the file
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << ui->editor->toPlainText();
        file.close();
        QMessageBox::information(this, "Saved", "File saved successfully to:\n" + filePath);
    } else {
        QMessageBox::critical(this, "Error", "Could not open file for writing:\n" + filePath);
    }
    this->close();
}


void NewCommand::on_cancelButton_clicked()
{
    this->close();
}

