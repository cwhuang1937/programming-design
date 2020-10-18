#ifndef BOSS_H
#define BOSS_H
#include "Enemy.h"

class Boss : public Enemy{
public:
    Boss();

public slots:
    virtual void move();
    virtual void shoot();
private:

};
#endif // BOSS_H
