#ifndef TABSCRIPTEDITOR_H
#define TABSCRIPTEDITOR_H

#include <QWidget>
#include <QTabWidget>

#include "scriptEditor.h"
#include "highlighter.h"

class TabScriptEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TabScriptEditor(QWidget *parent = nullptr);
    CodeEditor *currentEditor() const;


public slots:
    void newTab();


private:
    QTabWidget *tabWidget;
    Highlighter *highlighter;

};

#endif // TABSCRIPTEDITOR_H
