#include "Enemy_1.h"

Enemy_1::Enemy_1(){
    timer_enemy_fly = new QTimer;
    timer_enemy_shoot = new QTimer;
    timer_enemy_fly->start(20);
    timer_enemy_shoot->start(1500);
    connect(timer_enemy_shoot, SIGNAL(timeout()), this, SLOT(shoot()));
}

void Enemy_1::move(){
    int xx = rand()%100-50;
    if((this->x()+xx)<0 || (this->x()+xx)>840)
        setPos(x()-xx, y());
    else
        setPos(x()+xx, y());
}
void Enemy_1::shoot(){
    Bullet *b;
    b = new Bullet_e1;
    b->setPixmap(QPixmap(":/resource/picture/bullet_e1.png").scaled(130, 130));
    b->setPos(this->x() + this->pixmap().width() / 2 - b->pixmap().width()/2, this->y() + this->pixmap().height()/2);
    b->connect(timer_enemy_fly, SIGNAL(timeout()), b, SLOT(fly()));
    this->scene()->addItem(b);

}

