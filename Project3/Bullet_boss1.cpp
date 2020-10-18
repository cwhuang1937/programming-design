#include "Bullet_boss1.h"

void Bullet_boss1::fly(){
    if(x()<450)
        setPos(x()+2, y() + 8);
    else
        setPos(x()-2, y() + 8);
    if(y() > 830){
        this->scene()->removeItem(this);
        delete this;
    }
}
