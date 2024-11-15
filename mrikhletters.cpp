#include "mrikhletters.h"

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>

mrikhletters::mrikhletters() : ComplexObject() {
    qreal x = 0;
    qreal y = 0;
    qreal spacing = 70;

    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    pen.setWidth(2);

    // Буква "М"
    {
        QGraphicsRectItem* leftStem = new QGraphicsRectItem(x, y, 10, 60);
        leftStem->setBrush(brush);
        leftStem->setPen(pen);
        addItem(leftStem);

        QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x, y, x + 25, y + 30);
        leftDiagonal->setPen(pen);
        addItem(leftDiagonal);

        QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 25, y + 30, x + 50, y);
        rightDiagonal->setPen(pen);
        addItem(rightDiagonal);

        QGraphicsRectItem* rightStem = new QGraphicsRectItem(x + 40, y, 10, 60);
        rightStem->setBrush(brush);
        rightStem->setPen(pen);
        addItem(rightStem);
    }
    x += spacing;

    // Буква "Р"
    {
        QGraphicsRectItem* verticalStem = new QGraphicsRectItem(x, y, 10, 60);
        verticalStem->setBrush(brush);
        verticalStem->setPen(pen);
        addItem(verticalStem);

        QGraphicsEllipseItem* topLoop = new QGraphicsEllipseItem(x + 10, y, 30, 30);
        topLoop->setBrush(brush);
        topLoop->setPen(pen);
        addItem(topLoop);
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

    // Буква "Х"
    {
        QGraphicsLineItem* leftDiagonal = new QGraphicsLineItem(x, y, x + 50, y + 60);
        leftDiagonal->setPen(pen);
        addItem(leftDiagonal);

        QGraphicsLineItem* rightDiagonal = new QGraphicsLineItem(x + 50, y, x, y + 60);
        rightDiagonal->setPen(pen);
        addItem(rightDiagonal);
    }
}
