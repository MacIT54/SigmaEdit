#include "objecteditor.h"
#include <QGraphicsScene>
#include <QPen>
#include <QGraphicsEllipseItem>
#include <QMimeData>
#include <QResizeEvent>

customgraphicsview::customgraphicsview(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {}

void customgraphicsview::setBrushSize(qreal size) {
    brushSize = size;
}

void customgraphicsview::setBrushColor(const QColor &color) {
    brushColor = color;
}

void customgraphicsview::setBrushStyle(Qt::BrushStyle style) {
    brushStyle = style;
}

void customgraphicsview::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = true;
        drawAt(event->pos());
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void customgraphicsview::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    } else {
        QGraphicsView::dragEnterEvent(event);
    }
}

void customgraphicsview::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(mapToScene(event->pos()));
        scene()->addItem(item);
        event->acceptProposedAction();
    } else {
        QGraphicsView::dropEvent(event);
    }
}

void customgraphicsview::mouseMoveEvent(QMouseEvent *event) {
    if (isDrawing) {
        drawAt(event->pos());
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void customgraphicsview::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        isDrawing = false;
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void customgraphicsview::drawAt(const QPoint &position) {
    QPointF scenePos = mapToScene(position);
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(
        scenePos.x() - brushSize / 2,
        scenePos.y() - brushSize / 2,
        brushSize,
        brushSize
        );

    QBrush brush(brushColor, brushStyle);
    ellipse->setBrush(brush);
    ellipse->setPen(Qt::NoPen);
    scene()->addItem(ellipse);
}

void customgraphicsview::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    if (scene()) {
        scene()->setSceneRect(rect());
    }
}
