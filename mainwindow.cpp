#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMenuBar>
#include <QInputDialog>

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
    QMenu *editMenu = new QMenu("Правка", this); // Меню для редактирования

    QAction *openRtfAction = new QAction("Открыть .rtf", this);
    QAction *createRtfAction = new QAction("Создать .rtf", this);
    saveRtfAction = new QAction("Сохранить .rtf", this);
    saveRtfAction->setEnabled(false); // Неактивное до открытия или создания файла

    QAction *findAction = new QAction("Найти", this);      // Поиск
    QAction *replaceAction = new QAction("Заменить", this); // Замена

    fileMenu->addAction(openRtfAction);
    fileMenu->addAction(createRtfAction);
    fileMenu->addAction(saveRtfAction);

    editMenu->addAction(findAction);
    editMenu->addAction(replaceAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);  // Добавляем меню редактирования
    setMenuBar(menuBar);

    setCentralWidget(textEdit);
    textEdit->setVisible(false); // Скрываем редактор в начале

    // Подключение действий меню к слотам
    connect(openRtfAction, &QAction::triggered, this, &MainWindow::openRtfFile);
    connect(createRtfAction, &QAction::triggered, this, &MainWindow::createRtfFile);
    connect(saveRtfAction, &QAction::triggered, this, &MainWindow::saveRtfFile);
    connect(findAction, &QAction::triggered, this, &MainWindow::findText);     // Подключение поиска
    connect(replaceAction, &QAction::triggered, this, &MainWindow::replaceText); // Подключение замены
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

void MainWindow::findText() {
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Поиск"), tr("Введите текст для поиска:"), QLineEdit::Normal, "", &ok);

    if (ok && !searchText.isEmpty()) {
        // Приводим текст для поиска и документ к нижнему регистру для регистронезависимого поиска
        QString lowerSearchText = searchText.toLower();
        QString lowerDocumentText = textEdit->toPlainText().toLower();

        int index = lowerDocumentText.indexOf(lowerSearchText);

        if (index != -1) {
            // Создаем курсор и устанавливаем его на найденный текст
            QTextCursor cursor = textEdit->textCursor();
            cursor.setPosition(index);
            cursor.setPosition(index + searchText.length(), QTextCursor::KeepAnchor); // Выделяем найденное словосочетание

            textEdit->setTextCursor(cursor); // Устанавливаем курсор на найденный текст
            textEdit->ensureCursorVisible(); // Прокручиваем текст для видимости
        } else {
            QMessageBox::information(this, tr("Результаты поиска"), tr("Текст не найден."));
        }
    }
}



void MainWindow::replaceText() {
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Замена"), tr("Введите текст для поиска:"), QLineEdit::Normal, "", &ok);
    if (ok && !searchText.isEmpty()) {
        QString replaceText = QInputDialog::getText(this, tr("Замена"), tr("Введите текст для замены:"), QLineEdit::Normal, "", &ok);
        if (ok) {
            QString content = textEdit->toPlainText();
            content.replace(searchText, replaceText);
            textEdit->setPlainText(content);
        }
    }
}
