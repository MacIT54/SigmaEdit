#include "objectclass.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QDebug>

ComplexObject::ComplexObject() : dx(1), dy(1) {
    collisionSound.setSource(QUrl::fromLocalFile(":/sounds/am-am-am.wav"));
    collisionSound.setVolume(0.5);
}


ComplexObject::~ComplexObject() {
    qDeleteAll(items);
}

void ComplexObject::addItem(QGraphicsItem* item) {
    items.append(item);
    item->setParentItem(this);
}

void ComplexObject::removeItem(QGraphicsItem* item) {
    items.removeOne(item);
    delete item;
}

QRectF ComplexObject::boundingRect() const {
    QRectF rect;
    for (const QGraphicsItem* item : items) {
        rect = rect.united(item->boundingRect());
    }
    return rect;
}

void ComplexObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    for (QGraphicsItem* item : items) {
        item->paint(painter, option, widget);
    }
}

void ComplexObject::move(QGraphicsView *view) {
    QGraphicsScene *scene = view->scene();

    setPos(x() + dx, y() + dy);

    QRectF viewRect = view->mapToScene(view->viewport()->rect()).boundingRect();
    QRectF objectRect = boundingRect().translated(pos());

    if (objectRect.left() < viewRect.left() || objectRect.right() > viewRect.right() ||
        objectRect.top() < viewRect.top() || objectRect.bottom() > viewRect.bottom()) {
        dx = -dx;
        dy = -dy;
        collisionSound.play();
    }

    QList<QGraphicsItem *> collidingItems = scene->collidingItems(this);
    for (QGraphicsItem *item : collidingItems) {
        if ((dynamic_cast<ComplexObject*>(item) || dynamic_cast<shape*>(item)) && !items.contains(item)) {
            dx = -dx;
            dy = -dy;
            collisionSound.play();
            break;
        }
    }
}
