#include "buttonBar.h"
#include "ui_buttonBar.h"

#include "style.h"

ButtonBar::ButtonBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ButtonBar)
{
    ui->setupUi(this);
    ui->saveButton->setStyleSheet(Style::iconButtonStyle);
    ui->clearButton->setStyleSheet(Style::iconButtonStyle);
    ui->runButton->setStyleSheet(Style::iconButtonStyle);
    ui->searchAndReplaceButton->setStyleSheet(Style::iconButtonStyle);
    ui->templateButton->setStyleSheet(Style::iconButtonStyle);



}


ButtonBar::~ButtonBar()
{
    delete ui;
}

