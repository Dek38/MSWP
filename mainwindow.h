#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QGridLayout"
#include "QPushButton"
#include "QVector"
#include "buttons.h"
#include "QMouseEvent"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void fillTheField();
private:
    QGridLayout *Grid;
    Ui::MainWindow *ui;
    QVector<Buttons*> buttonArray;
    bool eventFilter(QObject *obj, QEvent *event);
private slots:
    void buttonClicked();
    void openAllField();
    void clearTheField();
};
#endif // MAINWINDOW_H
