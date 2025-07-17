#include "scriptEditorPanel.h"
#include "commandList.h"
#include "config.h"
#include "style.h"

#include <iostream>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QApplication>
#include <QSplitter>

ScriptEditorPanel::ScriptEditorPanel(QWidget *parent)
    : QDockWidget(parent)
{
    QWidget *container = new QWidget(this);

    // Header Layout
    QHBoxLayout *headerLayout = new QHBoxLayout;

    commandList = new CommandList();

    QToolButton *fileButton = new QToolButton();
    fileButton->setText("File");
    QMenu *fileMenu = new QMenu();
    fileMenu->addAction("New script", this, &ScriptEditorPanel::newFile);
    fileMenu->addAction("Open script", this, &ScriptEditorPanel::openFile);
    fileMenu->addAction("Save script as", this, &ScriptEditorPanel::saveFile);
    fileMenu->addAction("Exit", this, &ScriptEditorPanel::exitApp);
    fileButton->setMenu(fileMenu);
    fileButton->setPopupMode(QToolButton::InstantPopup);

    QToolButton *commandButton = new QToolButton();
    commandButton->setText("Commands");
    QMenu *commandMenu = new QMenu();

    QAction* addAction = commandMenu->addAction("Add new");
    connect(addAction, &QAction::triggered, this, &ScriptEditorPanel::newCommand);

    commandMenu->addAction("Edit excisting", this, &ScriptEditorPanel::editCommand);

    QAction* renameAction = commandMenu->addAction("Rename");
    connect(renameAction, &QAction::triggered, commandList, &CommandList::rename);
    connect(renameAction, &QAction::triggered, commandList, &CommandList::refreshList);

    QAction* removeAction = commandMenu->addAction("Remove");
    connect(removeAction, &QAction::triggered, commandList, &CommandList::remove);
    connect(removeAction, &QAction::triggered, commandList, &CommandList::refreshList);

    QAction* refreshAction = commandMenu->addAction("Refresh");
    connect(refreshAction, &QAction::triggered, commandList, &CommandList::refreshList);

    commandButton->setMenu(commandMenu);
    commandButton->setPopupMode(QToolButton::InstantPopup);

    QToolButton *templateButton = new QToolButton();
    templateButton->setText("Templates");
    QMenu *templateMenu = new QMenu();
    templateMenu->addAction("Load Template", this, &ScriptEditorPanel::temp);
    templateMenu->addAction("Add Template", this, &ScriptEditorPanel::temp);
    templateMenu->addAction("Edit Template", this, &ScriptEditorPanel::temp);
    templateMenu->addAction("Remove Template", this, &ScriptEditorPanel::temp);
    templateButton->setMenu(templateMenu);
    templateButton->setPopupMode(QToolButton::InstantPopup);


    //set layout header
    fileButton->setMinimumWidth(80);
    commandButton->setMinimumWidth(80);
    templateButton->setMinimumWidth(80);

    headerLayout->addWidget(fileButton);
    headerLayout->addWidget(commandButton);
    headerLayout->addWidget(templateButton);

    headerLayout->addStretch();

    // Editor
    editor = new CodeEditor(container);


    //CommandBox
    QSplitter *scriptEditorSplitter = new QSplitter;

    scriptEditorSplitter->addWidget(commandList);
    scriptEditorSplitter->addWidget(editor);
    scriptEditorSplitter->setSizes({75,250});

    //add the rig command code if it's clicked
    newcommand = new NewCommand(this);

    QDir dir(Config::riggingCommandsPath);

    connect(commandList, &CommandList::commandSelected, editor, [=](const QString &text) {
        //check if you still need to append path
        QString currentText = editor->toPlainText();
        QString sysImport = QString("sys.path.append('%1')").arg(dir.absolutePath());

        if(!currentText.contains("import sys"))
            {
                editor->appendPlainText("import sys");
            }
        if(!currentText.contains(sysImport))
            {
                editor->appendPlainText(sysImport);
                editor->appendPlainText("\n");
            }

        editor->appendPlainText(text);
    });

    //edit command
    editcommand = new EditCommand(this);


    // Main Layout inside container widget
    QVBoxLayout *mainLayout = new QVBoxLayout(container);

    //buttonbar
    buttonbar = new ButtonBar;


    mainLayout->addLayout(headerLayout);
    mainLayout->addWidget(buttonbar);
    mainLayout->addWidget(scriptEditorSplitter);


    container->setLayout(mainLayout);
    this->setWidget(container);


    //add highlighter
    highlighter = new Highlighter(editor->document());

    // style
    container->setStyleSheet(Style::containerStyle);

    //buttons
    commandButton->setStyleSheet(Style::buttonStyle);

    fileButton->setStyleSheet(Style::buttonStyle);

    templateButton->setStyleSheet(Style::buttonStyle);

    //menu
    commandMenu->setStyleSheet(Style::menuStyle);

    fileMenu->setStyleSheet(Style::menuStyle);

    templateMenu->setStyleSheet(Style::menuStyle);

    commandList->setStyleSheet(Style::listStyle);

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


void ScriptEditorPanel::temp()
{
    std::cout<<"temporary defintion/n";
}


void ScriptEditorPanel::newCommand()
{
    newcommand->show();
    newcommand->raise();
    newcommand->setFocus();
}


void ScriptEditorPanel::editCommand()
{
    editcommand->show();
    editcommand->raise();
    editcommand->setFocus();
}
