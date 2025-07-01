#include "highlighter.h"
#include <list>
#include <cstdio>
#include <string>
#include <fstream>

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    //different lists for python highlighting
    std::list<QString> pythonKeywords = {
        QStringLiteral("and"), QStringLiteral("assert"), QStringLiteral("break"),
        QStringLiteral("class"), QStringLiteral("continue"), QStringLiteral("def"),
        QStringLiteral("del"), QStringLiteral("elif"), QStringLiteral("else"),
        QStringLiteral("except"), QStringLiteral("exec"), QStringLiteral("finally"),
        QStringLiteral("for"), QStringLiteral("from"), QStringLiteral("global"),
        QStringLiteral("if"), QStringLiteral("import"), QStringLiteral("in"),
        QStringLiteral("is"), QStringLiteral("lambda"), QStringLiteral("not"),
        QStringLiteral("or"), QStringLiteral("pass"), QStringLiteral("print"),
        QStringLiteral("raise"), QStringLiteral("return"), QStringLiteral("try"),
        QStringLiteral("while"), QStringLiteral("yield"), QStringLiteral("None"),
        QStringLiteral("True"), QStringLiteral("False")
    };


    keywordFormat.setForeground(QColor(197, 134, 192));
    keywordFormat.setFontWeight(QFont::Bold);


    for (const QString &pattern : pythonKeywords) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }


    //highlight cmds words
    keywordFormat.setForeground(QColor(255, 134, 50));
    keywordFormat.setFontWeight(QFont::Bold);

    std::list<QString> CMDS;
    CMDS = convertToList("C:/Users/robin/OneDrive/Documents/ScriptEditor/syntaxLists/maya_cmds_list.txt", "listName");


    for (const QString &pattern : CMDS) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
    rule.format = classFormat;
    highlightingRules.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
    rule.format = functionFormat;
    highlightingRules.append(rule);

    singleLineCommentFormat.setForeground(Qt::red);
    rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::red);

    commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
    commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void Highlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : std::as_const(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}

//read txt files into lists
std::list<QString> Highlighter::convertToList(std::string filename, std::string listname)
{
    std::list<QString> listOut;

    // if(!std::filesystem::exists(filename))
    // {
    //     if(std::filesystem::is_empty(filename))
    //     {
    //         std::cerr << "empty file\n" ;
    //         return listOut;
    //     }

    //     return listOut;
    // }

    std::string line;
    std::ifstream file(filename);

    while (std::getline(file, line))
    {
        QString qline = QString::fromStdString(line);
        if (!qline.trimmed().isEmpty()) {
            listOut.push_back(qline);
        }
    }

    return listOut;
}









