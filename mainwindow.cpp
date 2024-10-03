#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textEdit(new QTextEdit(this)),
    currentRtfFileName("")
{
    ui->setupUi(this);

    // Создание меню
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("Файл", this);

    QAction *openRtfAction = new QAction("Открыть .rtf", this);
    QAction *createRtfAction = new QAction("Создать .rtf", this);
    QAction *saveRtfAction = new QAction("Сохранить .rtf", this);
    saveRtfAction->setEnabled(false); // Делаем неактивным до открытия или создания файла

    fileMenu->addAction(openRtfAction);
    fileMenu->addAction(createRtfAction);
    fileMenu->addAction(saveRtfAction);

    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);

    setCentralWidget(textEdit);
    textEdit->setVisible(false); // Скрываем редактор текста в начале

    // Подключение действий меню к слотам
    connect(openRtfAction, &QAction::triggered, this, &MainWindow::openRtfFile);
    connect(createRtfAction, &QAction::triggered, this, &MainWindow::createRtfFile);
    connect(saveRtfAction, &QAction::triggered, this, &MainWindow::saveRtfFile);

    this->saveRtfAction = saveRtfAction; // Сохраняем указатель на действие "Сохранить"
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openRtfFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Открыть .rtf файл"), "", tr("RTF Files (*.rtf);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            textEdit->setPlainText(in.readAll());
            file.close();
        }
        currentRtfFileName = fileName;
        textEdit->setVisible(true);

        saveRtfAction->setEnabled(true); // Делаем доступной кнопку "Сохранить"
    }
}

void MainWindow::createRtfFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Создать .rtf файл"), "", tr("RTF Files (*.rtf);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.close(); // Создаем пустой файл
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось создать файл."));
        }
        textEdit->clear();
        currentRtfFileName = fileName;
        textEdit->setVisible(true);

        saveRtfAction->setEnabled(true); // Делаем доступной кнопку "Сохранить"
    }
}

void MainWindow::saveRtfFile() {
    if (currentRtfFileName.isEmpty()) {
        QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить .rtf файл"), "", tr("RTF Files (*.rtf);;All Files (*)"));
        if (!fileName.isEmpty()) {
            currentRtfFileName = fileName;
        } else {
            return;
        }
    }

    QFile file(currentRtfFileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить файл."));
    }
}
