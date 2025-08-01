#include "buttonBar.h"
#include "ui_buttonBar.h"
#include "style.h"

ButtonBar::ButtonBar(TabScriptEditor* tabEditor, QWidget *parent)
    : QWidget(parent), ui(new Ui::ButtonBar), tabEditor(tabEditor)
{
    ui->setupUi(this);
    ui->saveButton->setStyleSheet(Style::iconButtonStyle);
    ui->clearButton->setStyleSheet(Style::iconButtonStyle);
    ui->runButton->setStyleSheet(Style::iconButtonStyle);
    ui->searchAndReplaceButton->setStyleSheet(Style::iconButtonStyle);
    ui->templateButton->setStyleSheet(Style::iconButtonStyle);

    editfile = new EditFile(tabEditor);  // Works on current editor
    searchandreplace = new SearchAndReplace(tabEditor->currentEditor());
    edittemplate = new EditTemplate();
}

ButtonBar::~ButtonBar()
{
    delete ui;
}

CodeEditor* ButtonBar::currentEditor() const
{
    return qobject_cast<CodeEditor*>(tabWidget->currentWidget());
}

void ButtonBar::on_saveButton_clicked()
{
    editfile->saveFile();
}

void ButtonBar::on_clearButton_clicked()
{
    editfile->newFile();
}

void ButtonBar::on_searchAndReplaceButton_clicked()
{
    searchandreplace->show();
    searchandreplace->raise();
    searchandreplace->setFocus();
}

void ButtonBar::on_templateButton_clicked()
{
    edittemplate->show();
    edittemplate->raise();
    edittemplate->setFocus();
}
