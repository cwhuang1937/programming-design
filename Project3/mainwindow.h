#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QDebug>
#include <QBrush>
#include <QPushButton>
#include <QSignalMapper>
#include <unistd.h>
#include <QLabel>
#include <QString>
#include <QSignalBlocker>
#include <QMessageBox>
#include <QLCDNumber>
#include <QProgressBar>
#include "Bullet_p1.h"
#include "Bullet_e1.h"
#include "Bullet_e2.h"
#include "Bullet_boss1.h"
#include "Enemy_1.h"
#include "Enemy_2.h"
#include "Boss.h"
#include "Player.h"
#include "Tool1.h"
#include "Tool2.h"
#include "Bomb.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
   virtual void keyPressEvent(QKeyEvent *e);
   virtual void keyReleaseEvent(QKeyEvent *e);
   virtual void mousePressEvent(QMouseEvent *e);

private:
    void setting();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QProgressBar *boss_pro, *unique_skill_pro;
    Player *player;
    QTimer *timer_fly, *timer_auto, *timer_detect, *timer_detect_wait, *timer_detect_enemy, *Timer, *timer_player_move;
    QTimer *timer_enemy_gen[3], *timer_enemy_move[3], *timer_detect_boss, *timer_life_gen, *timer_tool_fly, *timer_unique_skill_add;
    QTimer *timer_unique_skill;
    QPushButton *Button_auto, *Button_bomb;
    QSignalMapper *signalMapper_enemy_gen[3];
    QMessageBox *Game_over;
    QLCDNumber *LCD, *score_record;
    QLabel *life_icon, *life, *score, *kills, *skill_icon, *skill;
    QLabel *e1, *e1_rec, *e2, *e2_rec, *e3, *e3_rec;
    Boss *boss;
    QString secstr, minstr, life_num_str, e1_num_str, e2_num_str, e3_num_str, skill_num_str;
    int sec, min;
    int auto_index;
    int life_num, score_num, e1_num, e2_num, e3_num, skill_num, unique_skill_num;
    int boss_hp, boss_hp_bar;
    int up, down, left, right;
    void push_bomb();
    void use_unique_skill();
    int shoot_num;




private slots:
    void player_shoot();
    void Button_auto_push();
    void Button_bomb_push();
    void generate_enemy(int index);
    void detect_player();
    void enemy_detect_attack();
    void revive();
    void invincible();
    void boss_detect_attack();
    void showTime();
    void life_gen();
    void move_player();
    void unique_skill_add();
    void use_unique_skill_end();

};

#endif // MAINWINDOW_H
