#ifndef GRAPHICEDITOR_H
#define GRAPHICEDITOR_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem> // Для отображения изображений
#include <QPushButton>
#include <QComboBox>

class CustomGraphicsView;

class graphiceditor : public QMainWindow {
    Q_OBJECT

public:
    explicit graphiceditor(QWidget *parent = nullptr);
    ~graphiceditor();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;  // Обработка события входа перетаскивания
    void dropEvent(QDropEvent *event) override;  // Обработка события завершения перетаскивания

private slots:
    void addCircle();         // Слот для добавления круга
    void addRectangle();      // Слот для добавления прямоугольника
    void addTriangle();       // Слот для добавления треугольника
    void addLine();           // Слот для добавления линии
    void saveImage();         // Слот для сохранения изображения
    void importImage();       // Слот для импорта изображения
    void setBrushSize();      // Слот для изменения размера кисти
    void setBrushColor();     // Слот для изменения цвета кисти
    void setEraser();         // Слот для включения режима ластика
    void changeBackgroundColor();  // Слот для изменения фона
    void setBrushStyle();     // Слот для изменения стиля кисти
    void deleteSelectedItem(); // Слот для удаления выбранного элемента
    void addText();           // Слот для добавления текста

private:
    QGraphicsScene *scene;    // Сцена для отрисовки элементов
    QColor currentBrushColor; // Текущий цвет кисти
    qreal currentBrushSize;   // Текущий размер кисти
    Qt::BrushStyle currentBrushStyle; // Текущий стиль кисти
    bool isEraserMode;        // Режим ластика
};

#endif // GRAPHICEDITOR_H
