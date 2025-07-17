#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include <QWidget>

namespace Ui {
class ButtonBar;
}

class ButtonBar : public QWidget
{
    Q_OBJECT

public:
    explicit ButtonBar(QWidget *parent = nullptr);
    ~ButtonBar();

private:
    Ui::ButtonBar *ui;
};

#endif // BUTTONBAR_H
