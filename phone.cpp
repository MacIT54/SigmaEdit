#include "phone.h"
#include <QBrush>
#include <QPen>
#include <QRectF>
#include <QColor>

phone::phone() : ComplexObject() {
    QColor black(0, 0, 0);
    QColor gray(169, 169, 169);
    QColor silver(192, 192, 192);
    QColor iconColor1(255, 0, 0);
    QColor iconColor2(0, 255, 0);
    QColor iconColor3(0, 0, 255);

    QGraphicsRectItem* body = new QGraphicsRectItem(-40, -80, 80, 160);
    body->setBrush(QBrush(black));
    body->setPen(QPen(Qt::black));
    addItem(body);

    QGraphicsRectItem* screen = new QGraphicsRectItem(-30, -70, 60, 140);
    screen->setBrush(QBrush(gray));
    screen->setPen(QPen(Qt::black));
    addItem(screen);

    QGraphicsEllipseItem* frontCamera = new QGraphicsEllipseItem(-5, -75, 3, 3);
    frontCamera->setBrush(QBrush(silver));
    frontCamera->setPen(QPen(Qt::black));
    addItem(frontCamera);

    QGraphicsRectItem* icon1 = new QGraphicsRectItem(-27, -60, 12, 12);
    icon1->setBrush(QBrush(iconColor1));
    icon1->setPen(QPen(Qt::black));
    addItem(icon1);

    QGraphicsRectItem* icon2 = new QGraphicsRectItem(-7, -60, 12, 12);
    icon2->setBrush(QBrush(iconColor2));
    icon2->setPen(QPen(Qt::black));
    addItem(icon2);

    QGraphicsRectItem* icon3 = new QGraphicsRectItem(13, -60, 12, 12);
    icon3->setBrush(QBrush(iconColor3));
    icon3->setPen(QPen(Qt::black));
    addItem(icon3);

    QGraphicsEllipseItem* homeButton = new QGraphicsEllipseItem(-5, 70, 10, 10);
    homeButton->setBrush(QBrush(silver));
    homeButton->setPen(QPen(Qt::black));
    addItem(homeButton);
}
