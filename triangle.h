#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "shape.h"
#include <QGraphicsItem>
#include <QPainter>

class triangle : public shape {
public:
    triangle(qreal base, qreal height, const QBrush &fillColor, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) override;

private:
    qreal base;
    qreal height;
    QBrush fillColor;
    QPen borderColor;
};

#endif // TRIANGLE_H
