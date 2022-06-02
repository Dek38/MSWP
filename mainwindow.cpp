#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVector"
#include "QPushButton"
#include "QVector"
#include <cstdlib>
#include <time.h>
#include <memory>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Grid = new QGridLayout(this);
    ui->setupUi(this);
    Grid->setSpacing(0);


    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            buttonArray.push_back(new Buttons(false, i, j));
            Grid->addWidget(dynamic_cast<QPushButton*>(buttonArray[i * 10 + j]), i, j);
            buttonArray[i * 10 + j]->installEventFilter(this);
            connect(dynamic_cast<QPushButton*>(buttonArray[i * 10 + j]), &QPushButton::clicked, this, &MainWindow::buttonClicked);
        }
    }
    fillTheField();


    ui->centralwidget->setLayout(Grid);
    ui->centralwidget->setFixedSize(440, 440);
    QAction *Clear = new QAction("Clear", this);
    ui->menubar->addAction(Clear);
    connect(Clear, &QAction::triggered, this, &MainWindow::clearTheField);
}

MainWindow::~MainWindow()
{
    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        delete *it;
    }
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            Buttons* currentButton = dynamic_cast<Buttons*>(obj);
            if(mouseEvent->button() == Qt::RightButton)
            {
                if ((!currentButton->getFlag()) && (currentButton->isEnabled()))
                {
                    currentButton->setFlag();
                }
                else if (currentButton->isEnabled())
                {
                    currentButton->clearFlag();
                }
                return true;
            }
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
    else if (event->type() == QEvent::MouseButtonDblClick)
    {
        return true;
    }
    else
    {
             // standard event processing
            return QObject::eventFilter(obj, event);
    }
}

void MainWindow::buttonClicked()
{
    Buttons* currentButton = dynamic_cast<Buttons*>(sender());
    currentButton->setEnabled(false);
    currentButton->showHidenValue();
    if (currentButton->text() == "*")
    {
        emit openAllField();
    }
    if (currentButton->text() == "")
    {
        int i = currentButton->m_coordX;
        int j = currentButton->m_coordY;
        if (j < 9)
        {
            if (buttonArray[i * 10 + (j + 1)]->isEnabled())
            {
                buttonArray[i * 10 + (j + 1)]->clicked();
            }
        }
        if (j > 0)
        {
            if (buttonArray[i * 10 + (j - 1)]->isEnabled())
            {
               buttonArray[i * 10 + (j - 1)]->clicked();
            }
        }
        if (i < 9)
        {
            if (buttonArray[(i + 1) * 10 + j]->isEnabled())
            {
                buttonArray[(i + 1) * 10 + j]->clicked();
            }
        }
        if (i > 0)
        {
            if (buttonArray[(i - 1) * 10 + j]->isEnabled())
            {
                buttonArray[(i - 1) * 10 + j]->clicked();
            }
        }
        if ((i < 9) && (j < 9))
        {
            if (buttonArray[(i + 1) * 10 + (j + 1)]->isEnabled())
            {
                buttonArray[(i + 1) * 10 + (j + 1)]->clicked();
            }
        }
        if ((i < 9) && (j > 0))
        {
            if (buttonArray[(i + 1) * 10 + (j - 1)]->isEnabled())
            {
                buttonArray[(i + 1) * 10 + (j - 1)]->clicked();
            }
        }
        if ((i > 0) && (j < 9))
        {
            if (buttonArray[(i - 1) * 10 + (j + 1)]->isEnabled())
            {
                buttonArray[(i - 1) * 10 + (j + 1)]->clicked();;
            }
        }
        if ((i > 0) && (j > 0))
        {
            if (buttonArray[(i - 1) * 10 + (j - 1)]->isEnabled())
            {
                buttonArray[(i - 1) * 10 + (j - 1)]->clicked();
            }
        }
    }
}

void MainWindow::openAllField()
{
    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        (*it)->setEnabled(false);
        (*it)->showHidenValue();

    }
}

void MainWindow::clearTheField()
{
    for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
    {
        (*it)->setText("");
        (*it)->setEnabled(true);
        (*it)->setOrUnsetMine(false);
        (*it)->clearFlag();
    }
    fillTheField();
}

void MainWindow::fillTheField()
{
    int numberOfMines = 10;
    bool finish = true;
    while (finish)
    {
        for (auto it = buttonArray.begin(); it < buttonArray.end(); it++)
        {
            if ((std::rand() % 11) == 10)
            {
                if (!(*it)->getMine())
                {
                    (*it)->setOrUnsetMine(true);
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
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int mineAround = 0;
            if (buttonArray[i * 10 + j]->getMine() == false)
            {
                if (j < 9)
                {
                    if (buttonArray[i * 10 + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (j > 0)
                {
                    if (buttonArray[i * 10 + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (i < 9)
                {
                    if (buttonArray[(i + 1) * 10 + j]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (i > 0)
                {
                    if (buttonArray[(i - 1) * 10 + j]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i < 9) && (j < 9))
                {
                    if (buttonArray[(i + 1) * 10 + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i < 9) && (j > 0))
                {
                    if (buttonArray[(i + 1) * 10 + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i > 0) && (j < 9))
                {
                    if (buttonArray[(i - 1) * 10 + (j + 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if ((i > 0) && (j > 0))
                {
                    if (buttonArray[(i - 1) * 10 + (j - 1)]->getMine() == true)
                    {
                        mineAround++;
                    }
                }
                if (mineAround)
                {
                    buttonArray[i * 10 + j]->setHidenValue(QString::number(mineAround));

                }
                else
                {
                    buttonArray[i * 10 + j]->setHidenValue("");
                }
            }
            else
            {
                buttonArray[i * 10 + j]->setHidenValue("*");
            }
        }
    }
}
