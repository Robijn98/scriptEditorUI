#ifndef EDITFILE_H
#define EDITFILE_H

#pragma once

#include <QObject>
#include <QTabWidget>

#include "tabScriptEditor.h"

class EditFile : public QObject {
    Q_OBJECT
public:
    EditFile(TabScriptEditor* tabEditor, QObject* parent = nullptr);
    void newFile();
    void openFile();
    void saveFile();
    void exitApp();

private:
    TabScriptEditor* tabEditor;
};


#endif // EDITFILE_H
