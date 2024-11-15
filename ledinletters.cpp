#include "ledinletters.h"

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

ledinletters::ledinletters() : ComplexObject() {
    qreal x = 0;
    qreal y = 0;
    qreal spacing = 70;

    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    pen.setWidth(2);


    // Буква "Л"
    {
        QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x, y + 60, x + 25, y);
        leftDiagonal->setPen(pen);
        addItem(leftDiagonal);

        QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 20, y, 10, 60);
        rightStem->setBrush(brush);
        rightStem->setPen(pen);
        addItem(rightStem);
    }
    x += spacing;

    // Буква "Е"
    {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsRectItem* topBar = new QGraphicsRectItem(x, y, 40, 10);
        topBar->setBrush(brush);
        topBar->setPen(pen);
        addItem(topBar);

        QGraphicsRectItem* middleBar = new QGraphicsRectItem(x, y + 25, 30, 10);
        middleBar->setBrush(brush);
        middleBar->setPen(pen);
        addItem(middleBar);

        QGraphicsRectItem* bottomBar = new QGraphicsRectItem(x, y + 50, 40, 10);
        bottomBar->setBrush(brush);
        bottomBar->setPen(pen);
        addItem(bottomBar);
    }
    x += spacing;


    // Буква "Д"
    {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x + 10, y, 10, 50);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsRectItem* base = new QGraphicsRectItem(x, y + 50, 50, 10);
        base->setBrush(brush);
        base->setPen(pen);
        addItem(base);

        QGraphicsEllipseItem* topHalfCircle = new QGraphicsEllipseItem(x + 10, y, 30, 30);
        topHalfCircle->setBrush(brush);
        topHalfCircle->setPen(pen);
        addItem(topHalfCircle);
    }
    x += spacing;

    // Буква "И"
    {
        QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
        leftStem->setBrush(brush);
        leftStem->setPen(pen);
        addItem(leftStem);

        QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
        rightStem->setBrush(brush);
        rightStem->setPen(pen);
        addItem(rightStem);

        QGraphicsLineItem* diagonalLine = new QGraphicsLineItem(x + 5, y, x + 45, y + 60);
        diagonalLine->setPen(pen);
        addItem(diagonalLine);
    }
    x += spacing;

    // Буква "Н"
    {
        QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
        leftStem->setBrush(brush);
        leftStem->setPen(pen);
        addItem(leftStem);

        QGraphicsRectItem* horizontalBar = new QGraphicsRectItem(x, y + 25, 50, 10);
        horizontalBar->setBrush(brush);
        horizontalBar->setPen(pen);
        addItem(horizontalBar);

        QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
        rightStem->setBrush(brush);
        rightStem->setPen(pen);
        addItem(rightStem);
    }
}

