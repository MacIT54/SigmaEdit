#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textEdit(new QTextEdit(this)),
    openButton(new QPushButton("Открыть файл", this)) // Создаем кнопку
{
    ui->setupUi(this);

    // Устанавливаем основной компоновщик
    QVBoxLayout *layout = new QVBoxLayout; // Компоновщик вертикального расположения
    layout->addWidget(openButton); // Добавляем кнопку в компоновщик
    layout->addWidget(textEdit); // Добавляем текстовый редактор в компоновщик

    // Создаем виджет и устанавливаем компоновщик
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Скрываем текстовый редактор
    textEdit->setVisible(false);

    // Подключаем сигнал кнопки к слоту
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
        }
        // Показываем текстовый редактор после открытия файла
        textEdit->setVisible(true);
    }
}
