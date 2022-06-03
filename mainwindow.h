#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGridLayout"
#include "QPushButton"
#include "QVector"
#include "buttons.h"
#include "QMouseEvent"
#include "QAction"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGridLayout *gameField;
    Ui::MainWindow *ui;
    QVector<Buttons*> buttonArray;
    bool eventFilter(QObject *obj, QEvent *event);
    int m_numberOfMines = 10;
    QVector<unsigned int> m_mineCoord;
    int m_numberOfCorrectedFlags = 0;
    int m_numberOfFlags = 0;
    QAction m_winLoseState;
    void fillTheField();

private slots:
    void buttonClicked();
    void openAllField();
    void clearTheField();
};
#endif // MAINWINDOW_H
