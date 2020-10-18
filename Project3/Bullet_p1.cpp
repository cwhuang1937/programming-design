#include "Bullet_p1.h"

void Bullet_p1::fly(){
    setPos(x(), y() - 20);
    if(y() < 30){
        this->scene()->removeItem(this);
        delete this;
    }
}

