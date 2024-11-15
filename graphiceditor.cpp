#include "graphiceditor.h"
#include "circle.h"
#include "line.h"
#include "triangle.h"
#include "rectangle.h"
#include <QGraphicsView>
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QInputDialog>
#include <QColorDialog>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QFontDialog>
#include <QGraphicsPixmapItem>
#include <QComboBox>
#include <objecteditor.h>
#include "movabletextitem.h"
#include "QtMath"
#include "objectclass.h"
#include "bird.h"
#include "phone.h"
#include "mrikhletters.h"
#include "ledinletters.h"

graphiceditor::graphiceditor(QWidget *parent)
    : QMainWindow(parent), scene(new QGraphicsScene(this)),
    currentBrushSize(10), isEraserMode(false), currentBrushStyle(Qt::SolidPattern) {

    QGraphicsView *view = new customgraphicsview(scene, this);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("QGraphicsView { border: 3px solid black; background-color: white; }");

    setCentralWidget(view);
    setWindowTitle("Graphics Editor");

    setMinimumSize(900, 700);
    setMaximumSize(1600, 1600);
    setAcceptDrops(true);

    QToolBar *toolbar = addToolBar("Shapes");

    QAction *addTextAction = new QAction(QIcon(":/icons/note.png"),"Вставить текст", this);
    toolbar->addAction(addTextAction);
    connect(addTextAction, &QAction::triggered, this, &graphiceditor::addText);

    QAction *addLineAction = new QAction(QIcon(":/icons/minus.png"),"Вставить линию", this);
    toolbar->addAction(addLineAction);
    connect(addLineAction, &QAction::triggered, this, &graphiceditor::addLine);

    QAction *addRectangleAction = new QAction(QIcon(":/icons/rectangle.png"),"Вставить прямоугольник", this);
    toolbar->addAction(addRectangleAction);
    connect(addRectangleAction, &QAction::triggered, this, &graphiceditor::addRectangle);

    QAction *addTriangleAction = new QAction(QIcon(":/icons/triangle.png"),"Вставить треугольник", this);
    toolbar->addAction(addTriangleAction);
    connect(addTriangleAction, &QAction::triggered, this, &graphiceditor::addTriangle);

    QAction *addCircleAction = new QAction(QIcon(":/icons/button.png"),"Вставить круг", this);
    toolbar->addAction(addCircleAction);
    connect(addCircleAction, &QAction::triggered, this, &graphiceditor::addCircle);

    QAction *deleteAction = new QAction(QIcon(":/icons/delete.png"),"Удалить", this);
    toolbar->addAction(deleteAction);
    connect(deleteAction, &QAction::triggered, this, &graphiceditor::deleteSelectedItem);


    QAction *importAction = new QAction(QIcon(":/icons/.png"),"Вставить изображение", this);
    toolbar->addAction(importAction);
    connect(importAction, &QAction::triggered, this, &graphiceditor::importImage);

    QAction *saveAction = new QAction(QIcon(":/icons/save.png"),"Сохранить", this);
    toolbar->addAction(saveAction);
    connect(saveAction, &QAction::triggered, this, &graphiceditor::saveImage);

    QAction *backgroundAction = new QAction(QIcon(":/icons/a.png"),"Цвет фона", this);
    toolbar->addAction(backgroundAction);
    connect(backgroundAction, &QAction::triggered, this, &graphiceditor::changeBackgroundColor);

    QAction *brushSizeAction = new QAction(QIcon(":/icons/paint-brush.png"),"Размер кисти", this);
    toolbar->addAction(brushSizeAction);
    connect(brushSizeAction, &QAction::triggered, this, &graphiceditor::setBrushSize);

    QAction *brushColorAction = new QAction(QIcon(":/icons/art-and-design.png"),"Цвет кисти", this);
    toolbar->addAction(brushColorAction);
    connect(brushColorAction, &QAction::triggered, this, &graphiceditor::setBrushColor);

    QAction *eraserAction = new QAction(QIcon(":/icons/eraser.png"),"Стереть", this);
    toolbar->addAction(eraserAction);
    connect(eraserAction, &QAction::triggered, this, &graphiceditor::setEraser);


    QComboBox *brushStyleComboBox = new QComboBox(this);
    brushStyleComboBox->addItem("Bold", QVariant::fromValue(Qt::SolidPattern));
    brushStyleComboBox->addItem("Dense 1", QVariant::fromValue(Qt::Dense5Pattern));
    brushStyleComboBox->addItem("Dense 2", QVariant::fromValue(Qt::Dense6Pattern));
    brushStyleComboBox->addItem("Dense 3", QVariant::fromValue(Qt::Dense7Pattern));
    brushStyleComboBox->addItem("Cross", QVariant::fromValue(Qt::CrossPattern));
    brushStyleComboBox->addItem("Horizontal", QVariant::fromValue(Qt::HorPattern));
    brushStyleComboBox->addItem("Vertical", QVariant::fromValue(Qt::VerPattern));
    toolbar->addWidget(brushStyleComboBox);
    connect(brushStyleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &graphiceditor::setBrushStyle);

    QTimer *timer = new QTimer(this);
    timer->start(16);


    bird *Bird = new bird();
    Bird->setPos(300, 300);
    connect(timer, &QTimer::timeout, [Bird, view]() { Bird->move(view); });
    scene->addItem(Bird);


    phone *Phone = new phone();
    Phone->setPos(100, 100);
    connect(timer, &QTimer::timeout, [Phone, view]() { Phone->move(view); });
    scene->addItem(Phone);

    mrikhletters* mrikhLetters = new mrikhletters();
    scene->addItem(mrikhLetters);
    connect(timer, &QTimer::timeout, [mrikhLetters, view]() { mrikhLetters->move(view); });
    mrikhLetters->setPos(400, 400);

}

graphiceditor::~graphiceditor() {
    delete scene;
}


void graphiceditor::addCircle() {
    bool ok;
    qreal radius = QInputDialog::getDouble(this, "Circle Radius", "Enter circle radius:", 50, 1, 200, 1, &ok);
    if (!ok) return;

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Select Fill Color");
    if (!fillColor.isValid()) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2);

    circle *Circle = new circle(radius, brush, pen);
    scene->addItem(Circle);
    Circle->setPos(100, 200);
}

void graphiceditor::saveImage() {
    QString filePath = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Files (*.png)");

    if (!filePath.isEmpty()) {
        QPixmap pixmap(scene->sceneRect().size().toSize());

        QPainter painter(&pixmap);

        scene->render(&painter);

        pixmap.save(filePath, "PNG");
    }
}

void graphiceditor::importImage() {
    QString filePath = QFileDialog::getOpenFileName(this, "Import Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");

    if (!filePath.isEmpty()) {
        QPixmap pixmap(filePath);

        if (!pixmap.isNull()) {
            QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
            item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
            item->setPos(0, 0);
            scene->addItem(item);
        }
    }
}



void graphiceditor::setBrushStyle() {
    QComboBox *brushStyleComboBox = qobject_cast<QComboBox*>(sender());
    if (brushStyleComboBox) {
        Qt::BrushStyle style = static_cast<Qt::BrushStyle>(brushStyleComboBox->currentData().toInt());
        currentBrushStyle = style;
        static_cast<customgraphicsview*>(centralWidget())->setBrushStyle(currentBrushStyle);
    }
}

void graphiceditor::setBrushSize() {
    bool ok;
    qreal size = QInputDialog::getDouble(this, "Brush Size", "Enter brush size:", currentBrushSize, 1, 50, 1, &ok);
    if (ok) {
        currentBrushSize = size;
        static_cast<customgraphicsview*>(centralWidget())->setBrushSize(currentBrushSize);
    }
}

void graphiceditor::setBrushColor() {
    QColor color = QColorDialog::getColor(currentBrushColor, this, "Select Brush Color");
    if (color.isValid()) {
        currentBrushColor = color;
        isEraserMode = false;
        static_cast<customgraphicsview*>(centralWidget())->setBrushColor(currentBrushColor);
    }
}

void graphiceditor::setEraser() {
    isEraserMode = true;
    static_cast<customgraphicsview*>(centralWidget())->setBrushColor(scene->backgroundBrush().color());
}

void graphiceditor::changeBackgroundColor() {
    QColor color = QColorDialog::getColor(scene->backgroundBrush().color(), this, "Select Background Color");
    if (color.isValid()) {
        scene->setBackgroundBrush(color);
        if (isEraserMode) {
            static_cast<customgraphicsview*>(centralWidget())->setBrushColor(color);
        }
    }
}

void graphiceditor::addText() {
    bool ok;
    QString text = QInputDialog::getText(this, "Add Text", "Enter your text:", QLineEdit::Normal, "", &ok);
    if (!ok || text.isEmpty()) return;

    bool fontOk;
    QFont font = QFontDialog::getFont(&fontOk, QFont("Arial", 12), this, "Select Font");
    if (!fontOk) return;

    movabletextitem *textItem = new movabletextitem(text);
    textItem->setFont(font);

    scene->addItem(textItem);
    textItem->setPos(100, 200);
}


void graphiceditor::deleteSelectedItem() {
    QList<QGraphicsItem*> selectedItems = scene->selectedItems();
    if (selectedItems.isEmpty()) {
        qDebug() << "No items selected for deletion.";
        return;
    }

    for (QGraphicsItem *item : selectedItems) {
        scene->removeItem(item);
        delete item;
        qDebug() << "Item deleted.";
    }
}


void graphiceditor::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction();
    }
}

void graphiceditor::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasImage()) {
        QPixmap pixmap = qvariant_cast<QPixmap>(event->mimeData()->imageData());
        QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);
        item->setPos(event->pos());
        scene->addItem(item);
        event->acceptProposedAction();
    }
}
void graphiceditor::addLine() {
    bool ok;
    qreal length = QInputDialog::getDouble(this, "Line Length", "Enter line length:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal angle = QInputDialog::getDouble(this, "Line Angle", "Enter line angle (in degrees):", 0, -360, 360, 1, &ok);
    if (!ok) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QPen pen(borderColor);
    pen.setWidth(2);

    line *Line = new line(length, qDegreesToRadians(angle), pen);
    scene->addItem(Line);
    Line->setPos(100, 200);
}


void graphiceditor::addRectangle() {
    bool ok;
    qreal width = QInputDialog::getDouble(this, "Rectangle Width", "Enter rectangle width:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal height = QInputDialog::getDouble(this, "Rectangle Height", "Enter rectangle height:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Select Fill Color");
    if (!fillColor.isValid()) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2);

    rectangle *rect = new rectangle(width, height, brush, pen);
    scene->addItem(rect);
    rect->setPos(100, 200);
}

void graphiceditor::addTriangle() {
    bool ok;
    qreal base = QInputDialog::getDouble(this, "Triangle Base", "Enter triangle base:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    qreal height = QInputDialog::getDouble(this, "Triangle Height", "Enter triangle height:", 100, 1, 500, 1, &ok);
    if (!ok) return;

    QColor fillColor = QColorDialog::getColor(Qt::blue, this, "Select Fill Color");
    if (!fillColor.isValid()) return;

    QColor borderColor = QColorDialog::getColor(Qt::black, this, "Select Border Color");
    if (!borderColor.isValid()) return;

    QBrush brush(fillColor);
    QPen pen(borderColor);
    pen.setWidth(2);

    triangle *trian = new triangle(base, height, brush, pen);
    scene->addItem(trian);
    trian->setPos(100, 200);
}





