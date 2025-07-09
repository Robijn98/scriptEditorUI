#ifndef COMMANDLIST_H
#define COMMANDLIST_H

#include <QListWidget>
#include <QDir>

class CommandList : public QListWidget
{
    Q_OBJECT

public:
    explicit CommandList(QListWidget *parent = nullptr);
    QSize sizeHint() const override;

protected:
    std::list<QString> convertToList(QDir dir);

private:
    void populateList(std::list<QString> commandList);

};

#endif
