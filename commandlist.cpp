#include "commandlist.h"

#include <list>

CommandList::CommandList(QListWidget *parent)
: QListWidget(parent)

{
    std::list<QString> commandList;

    //HARD-CODED REPLACE FIX
    QDir dir("C:/Users/robin/OneDrive/Documents/ScriptEditor/riggingCommands");

    commandList = convertToList(dir);
    populateList(commandList);

    return;
}


QSize CommandList::sizeHint() const
{
    QSize hint;
    hint.setWidth(hint.width() * 0.5);
    return hint;
}



//read folder content into list
std::list<QString> CommandList::convertToList(QDir dir)
{
    std::list<QString> listOut;

    QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for(int i = 0; i < list.size(); i++)
    {
        QFileInfo fileInfo = list.at(i);
        QString name = fileInfo.fileName();

        if(name.endsWith(".py", Qt::CaseInsensitive))
        {
            name.chop(3);
        }

        listOut.push_back(name);
    }

    return listOut;
}

//turn list into listitems
void CommandList::populateList(std::list<QString> commandList)
{

    for(const QString &item : commandList)
    {
        this->addItem(item);
    }
}


