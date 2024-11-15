#include "movabletextitem.h"

movabletextitem::movabletextitem(const QString &text, QGraphicsItem *parent)
    : QGraphicsTextItem(text, parent), isMoving(false) {
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void movabletextitem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isMoving = true;
        lastMousePosition = event->scenePos();
        event->accept();
    } else {
        QGraphicsTextItem::mousePressEvent(event);
    }
}

void movabletextitem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isMoving) {
        QPointF offset = event->scenePos() - lastMousePosition;
        setPos(pos() + offset);
        lastMousePosition = event->scenePos();
    } else {
        QGraphicsTextItem::mouseMoveEvent(event);
    }
}

void movabletextitem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isMoving = false;
        event->accept();
    } else {
        QGraphicsTextItem::mouseReleaseEvent(event);
    }
}

void movabletextitem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setTextInteractionFlags(Qt::TextEditorInteraction);
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}
