#ifndef STYLE_H
#define STYLE_H

#pragma once
#include <QString>

class Style {
public:
    inline static QString buttonStyle =
        "background-color: black;"
        "border-style: solid;"
        "border-width: 2px;"
        "border-radius: 5px;"
        "border-color: #e36db4;"
        "font: bold 14px;"
        "min-width: 6em;"
        "padding: 6px;";

    inline static QString menuStyle =
        "color:#fff5fb;"
        "background-color:#e36db4;";

    inline static QString checkBoxStyle =
        "QCheckBox {"
        "    color: #fff5fb;"
        "    font: bold 14px;"
        "}"
        "QCheckBox::indicator {"
        "    width: 16px;"
        "    height: 16px;"
        "    border: 2px solid #e36db4;"
        "    background-color: black;"
        "    border-radius: 3px;"
        "}"
        "QCheckBox::indicator:checked {"
        "    background-color: black;"
        "image: url(:/icons/icons/checkmark.png);"
        "}";

};


#endif // STYLE_H
