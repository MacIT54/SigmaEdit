#ifndef OBJECTCLASS_H
#define OBJECTCLASS_H
#include "shape.h"
#include <QGraphicsItem>
#include <QList>
#include <QTimer>
#include <QGraphicsView>
#include <QSoundEffect>
#include <QMediaPlayer>

class ComplexObject : public shape
{
public:
    ComplexObject();
    ~ComplexObject();

    void addItem(QGraphicsItem* item);
    void removeItem(QGraphicsItem* item);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void move(QGraphicsView *view);

private:
    QList<QGraphicsItem*> items;
    qreal dx; // Change in x-direction
    qreal dy; // Change in y-direction
    QSoundEffect collisionSound; // Sound effect for collisions
};

#endif // OBJECTCLASS_H
