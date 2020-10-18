#include "Bullet_e1.h"

void Bullet_e1::fly(){
    setPos(x(), y() + 15);
    if(y() > 830){
        this->scene()->removeItem(this);
        delete this;

    }
}


