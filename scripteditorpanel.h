#pragma once

#include "highlighter.h"
#include "scriptEditor.h"
#include "commandList.h"
#include "newCommand.h"
#include "editCommand.h"
#include "buttonBar.h"

#include <QDockWidget>
#include <QTextEdit>
#include <QToolButton>
#include <QMenu>

class ScriptEditorPanel : public QDockWidget
{
    Q_OBJECT

public:
    explicit ScriptEditorPanel(QWidget *parent = nullptr);

private slots:
    void newFile();
    void openFile();
    void saveFile();
    void exitApp();

    void temp();
    void newCommand();
    void editCommand();

private:
    CodeEditor *editor;
    Highlighter *highlighter;
    CommandList *commandList;
    NewCommand *newcommand;
    EditCommand *editcommand;
    ButtonBar *buttonbar;

};




