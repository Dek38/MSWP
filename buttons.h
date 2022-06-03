#ifndef BUTTONS_H
#define BUTTONS_H
#include <QPushButton>
#include <memory>

//Класс обёртка для кнопки под мину

class Buttons: public QPushButton
{
    bool m_isItMine = false;        // true - mine
    bool m_flagIsSeted = false;
    QString m_hidenValue = "";
    unsigned int m_coordX;
    unsigned int m_coordY;

public:
    Buttons(unsigned int X, unsigned int Y);

    void showHidenValue();
    void setHidenValue(QString hidenValue);

    bool getMine() const;
    void setMine();
    void clearMine();

    void setFlag();
    void clearFlag();
    bool getFlag() const;

    unsigned int getCoordX() const;
    unsigned int getCoordY() const;
};

#endif // BUTTONS_H
