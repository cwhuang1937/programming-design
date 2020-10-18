#include "Tool1.h"

Tool1::Tool1(){}

void Tool1::fly(){
    setPos(x(), y() + 10);
    if(y() > 830){
        this->scene()->removeItem(this);
        delete this;
    }
}

