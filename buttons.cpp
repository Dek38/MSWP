#include "buttons.h"

/**
 * @brief Buttons::Buttons - конструктор кнопки
 * @param X - координата X на поле
 * @param Y - координата Y на поле
 */

Buttons::Buttons(unsigned int X, unsigned int Y)
       : QPushButton(""), m_coordX(X), m_coordY(Y)
{
    this->setFixedSize(40, 40);
    QFont pushButtonFont = this->font();
    pushButtonFont.setPointSize(20);
    this->setFont(pushButtonFont);
    m_flagIsSeted = false;
}

/**
 * @brief Buttons::showHidenValue - метод для отображения скрытых значений кнопок
 */

void Buttons::showHidenValue()
{
    QString color = "red";
    switch (m_hidenValue.toInt()) {
    case 1:
        color = "blue";
        break;
    case 2:
        color = "green";
        break;
    case 3:
        color = "red";
        break;
    case 4:
        color = "purple";
        break;
    case 5:
        color = "brown";
        break;
    case 6:
        color = "pink";
        break;
    case 7:
        color = "black";
        break;
    case 8:
        color = "white";
        break;
    default:
        color = "yellow";
        break;
    }

    setStyleSheet("QPushButton {color: " + color + ";}");

    this->setText(m_hidenValue);
}

/**
 * @brief Buttons::getMine - возвращает наличие/отсутствие мины
 * @return true - мина, false - нет мины
 */

bool Buttons::getMine() const
{
    return m_isItMine;
}

/**
 * @brief Buttons::setMine - устанавливает мину на данную кнопку
 */

void Buttons::setMine()
{
    m_isItMine = true;
}

/**
 * @brief Buttons::clearMine - убирает мину с данной кнопки
 */

void Buttons::clearMine()
{
    m_isItMine = false;
}

/**
 * @brief Buttons::setHidenValue - устанавливает скрытое значение кнопки
 * @param hidenValue - строка со значением кнопки (1-8, мина, пустая строка)
 */

void Buttons::setHidenValue(QString hidenValue)
{
    m_hidenValue = hidenValue;
}

/**
 * @brief Buttons::setFlag - устанавливает флаг на клетку
 */

void Buttons::setFlag()
{
    m_flagIsSeted = true;
    setStyleSheet("QPushButton {color: orange;}");
    this->setText("l");
}

/**
 * @brief Buttons::clearFlag - убирает флаг с клетки
 */

void Buttons::clearFlag()
{
    m_flagIsSeted = false;
    this->setText("");
}

/**
 * @brief Buttons::getFlag - проверяет установлен ли флаг на клетке
 * @return true - установлен, false - нет
 */

bool Buttons::getFlag() const
{
    return m_flagIsSeted;
}

/**
 * @brief Buttons::getCoordX - возвращает коордиату Х выбранной кнопки
 * @return значение X на поле
 */

unsigned int Buttons::getCoordX() const
{
    return m_coordX;
}

/**
 * @brief Buttons::getCoordY - возвращает коордиату Y выбранной кнопки
 * @return значение Y на поле
 */

unsigned int Buttons::getCoordY() const
{
    return m_coordY;
}
