#pragma once

#include <QWidget>
#include <QPushButton>
#include <QToolButton>

namespace Ui {
class ButtonBar;
}

class ButtonBar : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonBar(QWidget *parent = nullptr);
    ~ButtonBar();


private slots:
    // void on_saveButton_clicked();

private:
    Ui::ButtonBar *ui;

};

