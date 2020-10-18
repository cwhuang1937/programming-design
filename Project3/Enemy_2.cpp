#include "Enemy_2.h"

Enemy_2::Enemy_2(){
    timer_enemy_fly = new QTimer;
    timer_enemy_shoot = new QTimer;
    timer_enemy_fly->start(20);
    timer_enemy_shoot->start(4000);
    connect(timer_enemy_shoot, SIGNAL(timeout()), this, SLOT(shoot()));
}
void Enemy_2::move(){
    if(this->x()<450)
        setPos(x()+15,y()+30);
    else
        setPos(x()-15,y()+30);


    if(y()>810){
        this->scene()->removeItem(this);
        delete this;
    }
}
void Enemy_2::shoot(){
    Bullet *b;
    b = new Bullet_e2;
    b->setPixmap(QPixmap(":/resource/picture/bullet_e2.png").scaled(50, 50));
    b->setPos(this->x() + this->pixmap().width() / 2 - b->pixmap().width()/2, this->y() + this->pixmap().height()/2);
    b->connect(timer_enemy_fly, SIGNAL(timeout()), b, SLOT(fly()));
    this->scene()->addItem(b);
}
