#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include <QGraphicsItem>
#include <QPen>
#include <QGraphicsSceneMouseEvent>

class line : public shape {
public:
    line(qreal length, qreal angle, const QPen &borderColor);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;  // Обработка нажатия мыши
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;   // Обработка движения мыши
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override; // Обработка отпускания мыши

private:
    qreal length;      // Длина линии
    qreal angle;       // Угол наклона линии в радианах
    QPen borderColor;  // Цвет и стиль обводки линии
    bool isMoving;     // Режим перемещения
};

#endif // LINE_H
