#include "rectangle.h"
#include <QStyleOptionGraphicsItem>

rectangle::rectangle(qreal width, qreal height, const QBrush &fillColor, const QPen &borderColor)
    : shape(), width(width), height(height), fillColor(fillColor), borderColor(borderColor) {}

QRectF rectangle::boundingRect() const {
    return QRectF(0, 0, width, height);
}

void rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) {
    painter->setBrush(fillColor);
    painter->setPen(borderColor);
    painter->drawRect(boundingRect());

    if (option->state & QStyle::State_Selected) {
        QPen selectedPen(Qt::DashLine);
        selectedPen.setColor(Qt::black);
        selectedPen.setWidth(6);
        painter->setPen(selectedPen);
        painter->drawRect(boundingRect());
    }
}
