#include "Tool2.h"

Tool2::Tool2(){}

void Tool2::fly(){
    setPos(x(), y() + 20);
    if(y() > 830){
        this->scene()->removeItem(this);
        delete this;
    }
}
