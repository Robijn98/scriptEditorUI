#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    scriptEditorDock = new ScriptEditorPanel(this);
    addDockWidget(Qt::BottomDockWidgetArea, scriptEditorDock);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    scriptEditorDock->show();
    scriptEditorDock->raise();
    scriptEditorDock->setFocus();
}

