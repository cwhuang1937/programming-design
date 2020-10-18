#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QDebug>
#include <QString>
#include <QSignalMapper>
#include <QKeyEvent>
#include <QLabel>
#include <QLCDNumber>
#include <QTimer>
#include <QMediaPlayer>
#include "Sudoku.h"
#include "Generator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    void change_Num(int index, int num);
public slots:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void Button_Ge_H_pressed();
    void Button_Ge_N_pressed();
    void Button_Ge_E_pressed();
    void Button_Cus_pressed();
    void Button_Ans_pressed();
    void Button_Che_pressed();
    void Button_Start_pressed();
    void Button_ReStart_pressed();
    void Button_Map_pressed(int pos);
    void change_Num_Slot(int index, int num);
    void TimerStart();
    void showTime();

private:
    Ui::MainWindow *ui;
    QPushButton *Map[Sudoku::sudokuSize];
    QPushButton *Button_Ge_H, *Button_Ge_N, *Button_Ge_E, *Button_Cus;
    QPushButton *Button_Ans, *Button_Che, *Button_Start, *Button_ReStart;
    QLabel *Label;
    QLCDNumber *LCD;
    QTimer *Timer;
    QMediaPlayer bgplayer, player[9];
    void CreateMap();
    void CreateObject();
    Generator ge;
    void Restart();
    bool solve_Puzzle(Sudoku que, Sudoku & ans);
    void keyPressEvent(QKeyEvent *input);
    int Position=0;
    bool Que_Map[Sudoku::sudokuSize];
    QSignalMapper *signalMapper = new QSignalMapper(this);
    bool check_Que();
    bool check_Unity(int *number);
    void saveMap();
    Sudoku que, ans;
    void setBackground();
    int sec = 0, min = 0;
    QString secstr, minstr;
};

#endif // MAINWINDOW_H
