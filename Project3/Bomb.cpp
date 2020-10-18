#include "Bomb.h"

void Bomb::fly(){
    setPos(x(), y() - 10);
    if(y() < 30){
        this->scene()->removeItem(this);
        delete this;
    }
}
