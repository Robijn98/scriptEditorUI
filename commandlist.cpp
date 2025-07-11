#include "commandlist.h"

#include <QTextStream>
#include <QRegularExpression>

#include <list>

CommandList::CommandList(QListWidget *parent)
: QListWidget(parent)

{
    std::list<QString> commandList;

    //HARD-CODED REPLACE FIX
    QDir dir("C:/Users/robin/OneDrive/Documents/ScriptEditor/riggingCommands");

    commandList = convertToList(dir);
    populateList(commandList);

    connect(this, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item) {
        QString commandText = commandDef(item->text(), dir);
        emit commandSelected(commandText);
    });


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


QString CommandList::commandDef(QString fileName, QDir dir)
{
    QString commandDef;
    QString completeFileName = QString("%1/%2.py").arg(dir.path()).arg(fileName);
    QFile file(completeFileName);

    QRegularExpression re(R"(def\s+([a-zA-Z_][a-zA-Z0-9_]*\(.*\))\s*:)");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString importFile = QString("import %1").arg(fileName);
        commandDef.push_back((importFile));
        commandDef.push_back("\n\n");

        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QRegularExpressionMatch match = re.match(line);
            if (match.hasMatch()) {
                QString funcSignature = match.captured(1);
                commandDef.push_back(funcSignature);
            }
            if(line.contains("#INFO"))
            {
                commandDef.push_back("\n");
                commandDef.push_back(line);
            }
        }
    }

    return commandDef;
}

void CommandList::clearItemsManually()
{
    while(this->count() > 0) {
        QListWidgetItem *item = this->takeItem(0);
        delete item;
    }
}


void CommandList::refreshList()
{
    clearItemsManually();
    //HARD-CODED REPLACE FIX
    QDir dir("C:/Users/robin/OneDrive/Documents/ScriptEditor/riggingCommands");
    std::list<QString> commandList;

    commandList = convertToList(dir);
    populateList(commandList);
}
