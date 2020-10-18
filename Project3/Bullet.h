#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Bullet : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT

public:
    Bullet();
    virtual ~Bullet();

public slots:
    virtual void fly() = 0;

};

#endif // BULLET_H
