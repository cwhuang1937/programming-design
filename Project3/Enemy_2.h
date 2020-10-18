#ifndef ENEMY_2_H
#define ENEMY_2_H
#include "Enemy.h"


class Enemy_2 : public Enemy{
public:
    Enemy_2();

public slots:
    virtual void move();
    virtual void shoot();
private:

};

#endif // ENEMY_2_H
