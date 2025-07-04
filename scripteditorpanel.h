#pragma once

#include "highlighter.h"
#include "scripteditor.h"
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
    void copy();
    void paste();
    void cut();

private:
    CodeEditor *editor;
    Highlighter *highlighter;

};




