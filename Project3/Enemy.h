#ifndef ENEMY_H
#define ENEMY_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "Bullet_e1.h"
#include "Bullet_e2.h"
#include "Bullet_boss1.h"
#include <cstdlib>

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Enemy();
    virtual ~Enemy();

public slots:
    virtual void move() = 0;
    virtual void shoot() = 0;
protected:
    QTimer *timer_enemy_fly;
    QTimer *timer_enemy_shoot;
private:

};

#endif // ENEMY_H
