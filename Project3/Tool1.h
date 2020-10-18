#ifndef TOOL1_H
#define TOOL1_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Tool1: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tool1();

public slots:
    void fly();

private:

private slots:

};

#endif // TOOL1_H
