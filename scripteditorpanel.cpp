#include "scripteditorpanel.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QApplication>

ScriptEditorPanel::ScriptEditorPanel(QWidget *parent)
    : QDockWidget(parent)
{
    QWidget *container = new QWidget(this);

    // Header Layout
    QHBoxLayout *headerLayout = new QHBoxLayout;


    QToolButton *fileButton = new QToolButton();
    fileButton->setText("File");
    QMenu *fileMenu = new QMenu();
    fileMenu->addAction("New", this, &ScriptEditorPanel::newFile);
    fileMenu->addAction("Open", this, &ScriptEditorPanel::openFile);
    fileMenu->addAction("Save as", this, &ScriptEditorPanel::saveFile);
    fileMenu->addAction("Exit", this, &ScriptEditorPanel::exitApp);
    fileButton->setMenu(fileMenu);
    fileButton->setPopupMode(QToolButton::InstantPopup);

    QToolButton *editButton = new QToolButton();
    editButton->setText("Edit");
    QMenu *editMenu = new QMenu();
    editMenu->addAction("Copy", this, &ScriptEditorPanel::copy);
    editMenu->addAction("Paste", this, &ScriptEditorPanel::paste);
    editMenu->addAction("Cut", this, &ScriptEditorPanel::cut);
    editButton->setMenu(editMenu);
    editButton->setPopupMode(QToolButton::InstantPopup);

    //set layout
    fileButton->setMinimumWidth(80);
    editButton->setMinimumWidth(80);

    headerLayout->addWidget(fileButton);
    headerLayout->addWidget(editButton);

    headerLayout->addStretch();

    // Editor
    editor = new QTextEdit(container);

    // Main Layout inside container widget
    QVBoxLayout *mainLayout = new QVBoxLayout(container);
    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(editor);

    container->setLayout(mainLayout);
    this->setWidget(container);

    //add highlighter
    highlighter = new Highlighter(editor->document());
}


//menu items
void ScriptEditorPanel::newFile()
{
    editor->clear();
}

void ScriptEditorPanel::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        editor->setPlainText(in.readAll());
        file.close();
    }
}

void ScriptEditorPanel::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);
        out << editor->toPlainText();
        file.close();
    }
}

void ScriptEditorPanel::exitApp()
{
    QApplication::quit();
}

void ScriptEditorPanel::copy()
{
    editor->copy();
}

void ScriptEditorPanel::paste()
{
    editor->paste();
}

void ScriptEditorPanel::cut()
{
    editor->cut();
}
