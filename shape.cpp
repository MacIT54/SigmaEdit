#include "shape.h"

shape::shape() : isMoving(false) {
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable); // Разрешаем выделение и перемещение
}

void shape::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isMoving = true;
        lastMousePosition = event->scenePos();  // Запоминаем позицию при нажатии мыши
    }
    QGraphicsItem::mousePressEvent(event); // Вызов базового класса для обработки выделения
}

void shape::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (isMoving) {
        QPointF offset = event->scenePos() - lastMousePosition;  // Смещение мыши
        setPos(pos() + offset);  // Перемещаем объект на новое место
        lastMousePosition = event->scenePos();  // Обновляем позицию
    }
}

void shape::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        isMoving = false;  // Завершаем перемещение при отпускании кнопки
    }
}
