#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H

#include <QGraphicsView>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <QColor>

class customgraphicsview : public QGraphicsView {
    Q_OBJECT

public:
    explicit customgraphicsview(QGraphicsScene *scene, QWidget *parent = nullptr);
    void setBrushSize(qreal size);
    void setBrushColor(const QColor &color);
    void setBrushStyle(Qt::BrushStyle style);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override; // Обработка входа перетаскивания
    void dropEvent(QDropEvent *event) override;           // Обработка завершения перетаскивания
    void resizeEvent(QResizeEvent *event) override; // Override the resize event

private:
    bool isDrawing;   // Flag to indicate if drawing is in progress
    qreal brushSize;
    QColor brushColor;
    Qt::BrushStyle brushStyle;
    void drawAt(const QPoint &position);  // Function to draw at the current mouse position

};

#endif
