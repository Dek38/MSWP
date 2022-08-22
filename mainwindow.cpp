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
    buttonArray.reserve(30*16);
    // создания поля кнопок
    for (int i = 0; i < sizeOfBeginnerFieldX; i++)
    {
        for (int j = 0; j < sizeOfBeginnerFieldY; j++)
        {
            buttonArray.push_back(new Buttons(i, j));
            gameField->addWidget(dynamic_cast<QPushButton*>(buttonArray[i * sizeOfBeginnerFieldY + j]), i, j);
            buttonArray[i * sizeOfBeginnerFieldY + j]->installEventFilter(this);
            connect(dynamic_cast<QPushButton*>(buttonArray[i * sizeOfBeginnerFieldY + j]), &QPushButton::clicked,
                    this, &MainWindow::buttonClicked);
        }
    }

    srand(time(0));
    fillTheField();


    ui->centralwidget->setLayout(gameField);
    ui->centralwidget->setFixedSize(300, 300);
    this->setFixedSize(300, 330);

    QAction *Clear = new QAction("Clear", this);
    ui->menubar->addAction(Clear);
    m_winLoseState.setText(QString::number(m_numberOfFlags));
    ui->menubar->addAction(&m_winLoseState);

    QAction *setBeginnerMode = new QAction("9x9", this);
    QAction *setIntermediateMode = new QAction("16x16", this);
    QAction *setProfessionalMode = new QAction("30x16", this);
    ui->menubar->addAction(setBeginnerMode);
    ui->menubar->addAction(setIntermediateMode);
    ui->menubar->addAction(setProfessionalMode);

    connect(Clear, &QAction::triggered, this, &MainWindow::clearTheField);
    connect(setBeginnerMode, &QAction::triggered, this, &MainWindow::changeMode);
    connect(setIntermediateMode, &QAction::triggered, this, &MainWindow::changeMode);
    connect(setProfessionalMode, &QAction::triggered, this, &MainWindow::changeMode);
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

void MainWindow::changeMode()
{

    auto mode = dynamic_cast<QAction*>(sender());

    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        delete *it;
    }

    buttonArray.clear();

    if (mode->text() == "16x16")
    {
        m_numberOfMines = 40;
        this->setFixedSize(540, 570);
        ui->centralwidget->setFixedSize(540, 540);
        sizeOfFieldX = sizeOfIntermediateFieldX;
        sizeOfFieldY = sizeOfIntermediateFieldY;
    }
    else if (mode->text() == "30x16")
    {
        m_numberOfMines = 99;
        this->setFixedSize(920, 570);
        ui->centralwidget->setFixedSize(920, 540);
        sizeOfFieldX = 16;
        sizeOfFieldY = 30;
    }
    else
    {
        m_numberOfMines = 10;
        ui->centralwidget->setFixedSize(300, 300);
        this->setFixedSize(300, 330);
        sizeOfFieldX = sizeOfBeginnerFieldX;
        sizeOfFieldY = sizeOfBeginnerFieldY;
    }

    for (int i = 0; i < sizeOfFieldX; i++)
    {
        for (int j = 0; j < sizeOfFieldY; j++)
        {
            buttonArray.push_back(new Buttons(i, j));
            gameField->addWidget(dynamic_cast<QPushButton*>(buttonArray[i * sizeOfFieldY + j]), i, j);
            buttonArray[i * sizeOfFieldY + j]->installEventFilter(this);
            connect(dynamic_cast<QPushButton*>(buttonArray[i * sizeOfFieldY + j]), &QPushButton::clicked,
                    this, &MainWindow::buttonClicked);
         }
    }
    emit clearTheField();
    ui->centralwidget->layout()->update();

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
            if (currentButton != nullptr)
            {
                // обработка нажатия правой кнопки мыши
                if(mouseEvent->button() == Qt::RightButton)
                {
                    if ((!currentButton->getFlag()) && (currentButton->isEnabled()))
                    {
                        currentButton->setFlag();
                        m_numberOfFlags++;
                        m_winLoseState.setText(QString::number(m_numberOfFlags));
                        if (currentButton->getMine())
                        {
                            m_numberOfCorrectedFlags++;
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
                        m_winLoseState.setText(QString::number(m_numberOfFlags));
                        if (currentButton->getMine())
                        {
                            m_numberOfCorrectedFlags--;
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
            else
            {
                return false;
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
    if (currentButton != nullptr)
    {
        currentButton->setEnabled(false);
        currentButton->showHidenValue();
        auto checkToClick = [](Buttons* buttonToCheck)
        {
            if ((buttonToCheck->isEnabled()) &&
                (!buttonToCheck->getFlag()))
            {
                buttonToCheck->clicked();
            }
        };
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
                auto buttonToCheck = buttonArray[i * sizeOfFieldY + (j + 1)];
                checkToClick(buttonToCheck);
            }
            if (j > 0)
            {
                auto buttonToCheck = buttonArray[i * sizeOfFieldY + (j - 1)];
                checkToClick(buttonToCheck);
            }
            if (i < (sizeOfFieldX - 1))
            {
                auto buttonToCheck = buttonArray[(i + 1) * sizeOfFieldY + j];
                checkToClick(buttonToCheck);
            }
            if (i > 0)
            {
                auto buttonToCheck = buttonArray[(i - 1) * sizeOfFieldY + j];
                checkToClick(buttonToCheck);
            }
            if ((i < (sizeOfFieldX - 1)) && (j < (sizeOfFieldY - 1)))
            {
                auto buttonToCheck = buttonArray[(i + 1) * sizeOfFieldY + (j + 1)];
                checkToClick(buttonToCheck);
            }
            if ((i < (sizeOfFieldX - 1)) && (j > 0))
            {
                auto buttonToCheck = buttonArray[(i + 1) * sizeOfFieldY + (j - 1)];
                checkToClick(buttonToCheck);
            }
            if ((i > 0) && (j < (sizeOfFieldY - 1)))
            {
                auto buttonToCheck = buttonArray[(i - 1) * sizeOfFieldY + (j + 1)];
                checkToClick(buttonToCheck);
            }
            if ((i > 0) && (j > 0))
            {
                auto buttonToCheck = buttonArray[(i - 1) * sizeOfFieldY + (j - 1)];
                checkToClick(buttonToCheck);
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
        else if (((*it)->getFlag()) && (m_winLoseState.text() != "Win") &&
                 (!(*it)->getMine()))
        {
            (*it)->setText("F");
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
    m_numberOfCorrectedFlags = 0;
    m_numberOfFlags = 0;
    m_winLoseState.setText(QString::number(m_numberOfFlags));
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
            if ((std::rand() % 100) == 10)
            {
                if (!(*it)->getMine())
                {
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
            if (buttonArray[i * sizeOfFieldY + j]->getMine() == false)
            {
                if (j < (sizeOfFieldY - 1))
                {
                    if (buttonArray[i * sizeOfFieldY + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (j > 0)
                {
                    if (buttonArray[i * sizeOfFieldY + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (i < (sizeOfFieldX - 1))
                {
                    if (buttonArray[(i + 1) * sizeOfFieldY + j]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (i > 0)
                {
                    if (buttonArray[(i - 1) * sizeOfFieldY + j]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i < (sizeOfFieldX - 1)) && (j < (sizeOfFieldY - 1)))
                {
                    if (buttonArray[(i + 1) * sizeOfFieldY + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i < (sizeOfFieldX - 1)) && (j > 0))
                {
                    if (buttonArray[(i + 1) * sizeOfFieldY + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i > 0) && (j < (sizeOfFieldY - 1)))
                {
                    if (buttonArray[(i - 1) * sizeOfFieldY + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i > 0) && (j > 0))
                {
                    if (buttonArray[(i - 1) * sizeOfFieldY + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (mineAround)
                {
                    buttonArray[i * sizeOfFieldY + j]->setHidenValue(QString::number(mineAround));
                }
                else
                {
                    buttonArray[i * sizeOfFieldY + j]->setHidenValue("");
                }
            }
            else
            {
                buttonArray[i * sizeOfFieldY + j]->setHidenValue("*");
            }
        }
    }
}
