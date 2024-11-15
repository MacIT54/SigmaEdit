#include "line.h"
#include <QPainter>
#include <QtMath>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "line.h"
#include <QPainter>
#include <QtMath>
#include <QGraphicsScene>

line::line(qreal length, qreal angle, const QPen &borderColor)
    : length(length), angle(angle), borderColor(borderColor), isMoving(false) {
    setFlag(ItemIsMovable);
    setFlag(ItemSendsScenePositionChanges);
    setAcceptedMouseButtons(Qt::RightButton);
}

QRectF line::boundingRect() const {
    qreal extra = 5; // Дополнительное пространство вокруг линии для захвата
    return QRectF(-extra, -extra, length + extra * 2, extra * 2);
}

void line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Не рисуем, если линия в режиме перемещения
    if (isMoving) {
        return;
    }

    painter->save();
    painter->translate(0, 0);
    painter->rotate(qRadiansToDegrees(angle));
    painter->setPen(borderColor);
    painter->drawLine(0, 0, length, 0);
    painter->restore();
}

QVariant line::itemChange(GraphicsItemChange change, const QVariant &value) {
    return QGraphicsItem::itemChange(change, value);
}

// Обработка нажатия правой кнопки мыши
void line::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        if (scene() && !scene()->views().isEmpty()) {
            scene()->views().first()->setCursor(Qt::OpenHandCursor);
        }
        event->accept();
        isMoving = true; // Устанавливаем режим перемещения
    } else {
        QGraphicsItem::mousePressEvent(event);
    }
}

// Обработка движения мыши
void line::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (event->buttons() & Qt::RightButton) {
        // Перемещение линии
        moveBy(event->pos().x() - event->lastPos().x(), event->pos().y() - event->lastPos().y());
        event->accept();
    } else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

// Обработка отпускания кнопки мыши
void line::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        if (scene() && !scene()->views().isEmpty()) {
            scene()->views().first()->setCursor(Qt::ArrowCursor);
        }
        isMoving = false; // Выход из режима перемещения
        update(); // Обновляем линию для перерисовки
        event->accept();
    } else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}
