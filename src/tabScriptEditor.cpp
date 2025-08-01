#include "tabScriptEditor.h"
#include <QVBoxLayout>
#include <QTabBar>
#include "style.h"

TabScriptEditor::TabScriptEditor(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    tabWidget = new QTabWidget(this);
    tabWidget->setTabsClosable(true);
    layout->addWidget(tabWidget);

    // Initial editor
    newTab();

    // "+" dummy tab
    QWidget *plusTab = new QWidget();
    tabWidget->addTab(plusTab, "+");

    connect(tabWidget, &QTabWidget::tabCloseRequested, this, [=](int index) {
        if (tabWidget->tabText(index) != "+") {
            QWidget *w = tabWidget->widget(index);
            tabWidget->removeTab(index);
            delete w;
        }
    });

    connect(tabWidget, &QTabWidget::currentChanged, this, [=](int index) {
        if (tabWidget->tabText(index) == "+") {
            newTab();
        }
    });

    this->setStyleSheet(Style::tabStyle);

    int plusTabIndex = tabWidget->count() - 1;
    tabWidget->tabBar()->setTabButton(plusTabIndex, QTabBar::RightSide, nullptr);
}

void TabScriptEditor::newTab()
{
    CodeEditor *editor = new CodeEditor();
    Highlighter *highlighter = new Highlighter(editor->document());
    int index = tabWidget->count() - 1;
    tabWidget->insertTab(index, editor, tr("%1").arg(index + 1));
    tabWidget->setCurrentIndex(index);
}

CodeEditor* TabScriptEditor::currentEditor() const
{
    return qobject_cast<CodeEditor*>(tabWidget->currentWidget());
}
