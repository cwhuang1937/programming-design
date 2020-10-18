#include "Bullet_e2.h"

void Bullet_e2::fly(){
    if(x()<450)
        setPos(x()+2, y() + 8);
    else
        setPos(x()-2, y() + 8);
    if(y() > 830){
        this->scene()->removeItem(this);
        delete this;
    }
}



