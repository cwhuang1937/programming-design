#ifndef ENEMY_1_H
#define ENEMY_1_H
#include "Enemy.h"


class Enemy_1 : public Enemy{

public:
    Enemy_1();

public slots:
    virtual void move();
    virtual void shoot();

private:

};

#endif // ENEMY_1_H
