#include "buttons.h"

Buttons::Buttons(bool mine, unsigned int X, unsigned int Y)
       : QPushButton(""), m_isItMine(mine), m_coordX(X), m_coordY(Y)
{
    this->setFixedSize(40, 40);
    QFont pushButtonFont = this->font();
    pushButtonFont.setPointSize(20);
    this->setFont(pushButtonFont);
    m_flagIsSeted = false;
}

void Buttons::showHidenValue()
{
    setStyleSheet("QPushButton {color: red;}");
    switch (m_hidenValue.toInt()) {
    case 1:
        setStyleSheet("QPushButton {color: blue;}");
        break;
    case 2:
        setStyleSheet("QPushButton {color: green;}");
        break;
    case 3:
        setStyleSheet("QPushButton {color: red;}");
        break;
    case 4:
        setStyleSheet("QPushButton {color: purple;}");
        break;
    case 5:
        setStyleSheet("QPushButton {color: brown;}");
        break;
    case 6:
        setStyleSheet("QPushButton {color: pink;}");
        break;
    case 7:
        setStyleSheet("QPushButton {color: black;}");
        break;
    case 8:
        setStyleSheet("QPushButton {color: white;}");
        break;
    default:
        setStyleSheet("QPushButton {color: yellow;}");
        break;
    }
    if (m_hidenValue == "1")
    {

    }
    this->setText(m_hidenValue);
}

bool Buttons::getMine() const
{
    return m_isItMine;
}

void Buttons::setOrUnsetMine(bool mine)
{
    m_isItMine = mine;
}

void Buttons::setHidenValue(QString hidenValue)
{
    m_hidenValue = hidenValue;
}

void Buttons::setFlag()
{
    m_flagIsSeted = true;
    setStyleSheet("QPushButton {color: orange;}");
    this->setText("l");
}

void Buttons::clearFlag()
{
    m_flagIsSeted = false;
    this->setText("");
}

bool Buttons::getFlag() const
{
    return m_flagIsSeted;
}
