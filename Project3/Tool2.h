#ifndef TOOL2_H
#define TOOL2_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

class Tool2: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tool2();

public slots:
    void fly();

private:

private slots:

};
#endif // TOOL2_H
