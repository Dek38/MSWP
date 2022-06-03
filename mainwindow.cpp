#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVector"
#include "QPushButton"
#include "QVector"
#include <cstdlib>
#include <time.h>

/**
 * @brief MainWindow::MainWindow - конструктор основного окна
 * @param parent
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    gameField = new QGridLayout(this);
    ui->setupUi(this);
    gameField->setSpacing(0);

    // создания поля кнопок
    for (int i = 0; i < sizeOfFieldX; i++)
    {
        for (int j = 0; j < sizeOfFieldY; j++)
        {
            buttonArray.push_back(new Buttons(i, j));
            gameField->addWidget(dynamic_cast<QPushButton*>(buttonArray[i * sizeOfFieldX + j]), i, j);
            buttonArray[i * sizeOfFieldX + j]->installEventFilter(this);
            connect(dynamic_cast<QPushButton*>(buttonArray[i * sizeOfFieldX + j]), &QPushButton::clicked,
                    this, &MainWindow::buttonClicked);
        }
    }

    srand(time(0));
    fillTheField();


    ui->centralwidget->setLayout(gameField);
    ui->centralwidget->setFixedSize(440, 440);
    QAction *Clear = new QAction("Clear", this);
    ui->menubar->addAction(Clear);
    m_winLoseState.setText("");
    ui->menubar->addAction(&m_winLoseState);
    connect(Clear, &QAction::triggered, this, &MainWindow::clearTheField);
}

/**
 * @brief MainWindow::~MainWindow - деструктор основного окна
 */

MainWindow::~MainWindow()
{
    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        delete *it;
    }
    delete ui;
}

/**
 * @brief MainWindow::eventFilter - метод для фильтрации событий
 * @param obj - объект, который возбудил событие
 * @param event - возбужденное собтие
 * @return возвращает состояние обработки осбытия
 */

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            Buttons* currentButton = dynamic_cast<Buttons*>(obj);

            // обработка нажатия правой кнопки мыши
            if(mouseEvent->button() == Qt::RightButton)
            {
                if ((!currentButton->getFlag()) && (currentButton->isEnabled()))
                {
                    currentButton->setFlag();
                    m_numberOfFlags++;
                    for (auto it = m_mineCoord.begin(); it < m_mineCoord.end(); it++)
                    {
                        if ((currentButton->getCoordX() * sizeOfFieldX + currentButton->getCoordY()) == *it)
                        {
                            m_numberOfCorrectedFlags++;
                            break;
                        }

                    }
                    if ((m_numberOfMines == m_numberOfCorrectedFlags) &&
                        (m_numberOfFlags == m_numberOfCorrectedFlags))
                    {
                        m_winLoseState.setText("Win");
                        emit openAllField();
                    }
                }
                else if (currentButton->isEnabled())
                {
                    currentButton->clearFlag();
                    m_numberOfFlags--;
                    for (auto it = m_mineCoord.begin(); it < m_mineCoord.end(); it++)
                    {
                        if ((currentButton->getCoordX() * sizeOfFieldX + currentButton->getCoordY()) == *it)
                        {
                            m_numberOfCorrectedFlags--;
                            break;
                        }
                    }
                    if ((m_numberOfMines == m_numberOfCorrectedFlags) &&
                        (m_numberOfFlags == m_numberOfCorrectedFlags))
                    {
                        m_winLoseState.setText("Win");
                        emit openAllField();
                    }
                }
                return true;
            }
            // обработка нажатия левой кнопки мыши
            else if(mouseEvent->button() == Qt::LeftButton)
            {
                if ((!currentButton->getFlag()) && (currentButton->isEnabled()))
                {
                    currentButton->clicked();
                }
                return true;
            }
            else
            {
                return QObject::eventFilter(obj, event);
            }

    }
    // запрет работы двойного нажатия
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        return true;
    }
    // обработка всех остальных событий
    else
    {
        return QObject::eventFilter(obj, event);
    }
}

/**
 * @brief MainWindow::buttonClicked - слот для обработки нажатия левой кнопки мыши
 */

void MainWindow::buttonClicked()
{
    Buttons* currentButton = dynamic_cast<Buttons*>(sender());
    currentButton->setEnabled(false);
    currentButton->showHidenValue();
    // проверка на мины и пустые кнопки
    if (currentButton->text() == "*")
    {
        m_winLoseState.setText("Lose");
        emit openAllField();
    }
    if (currentButton->text() == "")
    {
        int i = currentButton->getCoordX();
        int j = currentButton->getCoordY();
        if (j < (sizeOfFieldY - 1))
        {
            if ((buttonArray[i * sizeOfFieldX + (j + 1)]->isEnabled()) &&
               (!buttonArray[i * sizeOfFieldX + (j + 1)]->getFlag()))
            {
                buttonArray[i * sizeOfFieldX + (j + 1)]->clicked();
            }
        }
        if (j > 0)
        {
            if (buttonArray[i * sizeOfFieldX + (j - 1)]->isEnabled() &&
              (!buttonArray[i * sizeOfFieldX + (j - 1)]->getFlag()))
            {
               buttonArray[i * 9 + (j - 1)]->clicked();
            }
        }
        if (i < (sizeOfFieldX - 1))
        {
            if (buttonArray[(i + 1) * sizeOfFieldX + j]->isEnabled() &&
              (!buttonArray[(i + 1) * sizeOfFieldX + j]->getFlag()))
            {
                buttonArray[(i + 1) * sizeOfFieldX + j]->clicked();
            }
        }
        if (i > 0)
        {
            if (buttonArray[(i - 1) * sizeOfFieldX + j]->isEnabled() &&
              (!buttonArray[(i - 1) * sizeOfFieldX + j]->getFlag()))
            {
                buttonArray[(i - 1) * sizeOfFieldX + j]->clicked();
            }
        }
        if ((i < (sizeOfFieldX - 1)) && (j < (sizeOfFieldY - 1)))
        {
            if (buttonArray[(i + 1) * sizeOfFieldX + (j + 1)]->isEnabled() &&
              (!buttonArray[(i + 1) * sizeOfFieldX + (j + 1)]->getFlag()))
            {
                buttonArray[(i + 1) * sizeOfFieldX + (j + 1)]->clicked();
            }
        }
        if ((i < (sizeOfFieldX - 1)) && (j > 0))
        {
            if (buttonArray[(i + 1) * sizeOfFieldX + (j - 1)]->isEnabled() &&
              (!buttonArray[(i + 1) * sizeOfFieldX + (j - 1)]->getFlag()))
            {
                buttonArray[(i + 1) * sizeOfFieldX + (j - 1)]->clicked();
            }
        }
        if ((i > 0) && (j < (sizeOfFieldY - 1)))
        {
            if (buttonArray[(i - 1) * sizeOfFieldX + (j + 1)]->isEnabled() &&
              (!buttonArray[(i - 1) * sizeOfFieldX + (j + 1)]->getFlag()))
            {
                buttonArray[(i - 1) * sizeOfFieldX + (j + 1)]->clicked();;
            }
        }
        if ((i > 0) && (j > 0))
        {
            if (buttonArray[(i - 1) * sizeOfFieldX + (j - 1)]->isEnabled() &&
              (!buttonArray[(i - 1) * sizeOfFieldX + (j - 1)]->getFlag()))
            {
                buttonArray[(i - 1) * sizeOfFieldX + (j - 1)]->clicked();
            }
        }
    }
}

/**
 * @brief MainWindow::openAllField - метод для открытия поля при победе или поражении
 *        При победе открывает поле полностью при поражении только блокирует поле
 */

void MainWindow::openAllField()
{
    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        (*it)->setEnabled(false);
        if ((!(*it)->getFlag()) && (m_winLoseState.text() != "Win"))
        {
            (*it)->showHidenValue();
        }
    }
}

/**
 * @brief MainWindow::clearTheField - метод для очистки поля и установки новых мин
 */

void MainWindow::clearTheField()
{
    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        (*it)->setText("");
        (*it)->setEnabled(true);
        (*it)->clearMine();
        (*it)->clearFlag();
    }
    m_winLoseState.setText("");
    m_mineCoord.clear();
    m_numberOfCorrectedFlags = 0;
    m_numberOfFlags = 0;
    srand(time(0));
    fillTheField();
}

/**
 * @brief MainWindow::fillTheField - метод для заполнения поля
 */

void MainWindow::fillTheField()
{
    int numberOfMines = m_numberOfMines;
    bool finish = true;

    // заполние минами
    while (finish)
    {
        for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
        {
            if ((std::rand() % 11) == 10)
            {
                if (!(*it)->getMine())
                {
                    m_mineCoord.push_back((*it)->getCoordX() * sizeOfFieldX + (*it)->getCoordY());
                    (*it)->setMine();
                    numberOfMines--;
                    if (numberOfMines == 0)
                    {
                        finish = false;
                        break;
                    }
                }
            }
        }
    }

    // заполнение скрытыми значениями об окрестных минах
    for (int i = 0; i < sizeOfFieldX; i++)
    {
        for (int j = 0; j < sizeOfFieldY; j++)
        {
            int mineAround = 0;
            if (buttonArray[i * sizeOfFieldX + j]->getMine() == false)
            {
                if (j < (sizeOfFieldY - 1))
                {
                    if (buttonArray[i * sizeOfFieldX + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (j > 0)
                {
                    if (buttonArray[i * sizeOfFieldX + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (i < (sizeOfFieldX - 1))
                {
                    if (buttonArray[(i + 1) * sizeOfFieldX + j]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (i > 0)
                {
                    if (buttonArray[(i - 1) * sizeOfFieldX + j]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i < (sizeOfFieldX - 1)) && (j < (sizeOfFieldY - 1)))
                {
                    if (buttonArray[(i + 1) * sizeOfFieldX + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i < (sizeOfFieldX - 1)) && (j > 0))
                {
                    if (buttonArray[(i + 1) * sizeOfFieldX + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i > 0) && (j < (sizeOfFieldY - 1)))
                {
                    if (buttonArray[(i - 1) * sizeOfFieldX + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i > 0) && (j > 0))
                {
                    if (buttonArray[(i - 1) * sizeOfFieldX + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (mineAround)
                {
                    buttonArray[i * sizeOfFieldX + j]->setHidenValue(QString::number(mineAround));
                }
                else
                {
                    buttonArray[i * sizeOfFieldX + j]->setHidenValue("");
                }
            }
            else
            {
                buttonArray[i * sizeOfFieldX + j]->setHidenValue("*");
            }
        }
    }
}
