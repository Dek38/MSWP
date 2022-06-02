#ifndef BUTTONS_H
#define BUTTONS_H
#include <QPushButton>
#include <memory>

class Buttons: public QPushButton
{
    bool m_isItMine;        // true - mine
    bool m_flagIsSeted;
    QString m_hidenValue;

public:
    Buttons(bool mine, unsigned int X, unsigned int Y);
    void showHidenValue();
    bool getMine() const;
    void setOrUnsetMine(bool mine);
    void setHidenValue(QString hidenValue);
    void setFlag();
    void clearFlag();
    bool getFlag() const;
    unsigned int m_coordX;
    unsigned int m_coordY;
};

#endif // BUTTONS_H
