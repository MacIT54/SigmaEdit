#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMenuBar>
#include <QInputDialog>
#include <QClipboard>
#include <QApplication>
#include <QStandardPaths> // Для стандартных путей, например, к Рабочему столу

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textEdit(new QTextEdit(this)),
    currentRtfFileName(""),
    tempFileName("") // Инициализация пустым значением
{
    ui->setupUi(this);

    // Создание меню
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("Файл", this);
    QMenu *editMenu = new QMenu("Правка", this);

    QAction *openRtfAction = new QAction("Открыть .rtf", this);
    QAction *createRtfAction = new QAction("Создать .rtf", this);
    saveRtfAction = new QAction("Сохранить .rtf", this);
    saveRtfAction->setEnabled(false);

    QAction *findAction = new QAction("Найти", this);
    QAction *replaceAction = new QAction("Заменить", this);
    QAction *clearAction = new QAction("Очистить", this);
    QAction *undoAction = new QAction("Вернуть", this);
    QAction *copyAction = new QAction("Копировать", this);
    QAction *pasteAction = new QAction("Вставить", this);

    fileMenu->addAction(openRtfAction);
    fileMenu->addAction(createRtfAction);
    fileMenu->addAction(saveRtfAction);

    editMenu->addAction(findAction);
    editMenu->addAction(replaceAction);
    editMenu->addAction(clearAction);
    editMenu->addAction(undoAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    setMenuBar(menuBar);

    setCentralWidget(textEdit);
    textEdit->setVisible(false);

    // Подключение действий меню к слотам
    connect(openRtfAction, &QAction::triggered, this, &MainWindow::openRtfFile);
    connect(createRtfAction, &QAction::triggered, this, &MainWindow::createRtfFile);
    connect(saveRtfAction, &QAction::triggered, this, &MainWindow::saveRtfFile);
    connect(findAction, &QAction::triggered, this, &MainWindow::findText);
    connect(replaceAction, &QAction::triggered, this, &MainWindow::replaceText);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearText);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undoText);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyText);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteText);
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
        saveRtfAction->setEnabled(true);
    }
}

void MainWindow::createRtfFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Создать .rtf файл"), "", tr("RTF Files (*.rtf);;All Files (*)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            file.close();
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось создать файл."));
        }
        textEdit->clear();
        currentRtfFileName = fileName;
        textEdit->setVisible(true);
        saveRtfAction->setEnabled(true);
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
        QString lowerSearchText = searchText.toLower();
        QString lowerDocumentText = textEdit->toPlainText().toLower();
        int index = lowerDocumentText.indexOf(lowerSearchText);

        if (index != -1) {
            QTextCursor cursor = textEdit->textCursor();
            cursor.setPosition(index);
            cursor.setPosition(index + searchText.length(), QTextCursor::KeepAnchor);
            textEdit->setTextCursor(cursor);
            textEdit->ensureCursorVisible();
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

void MainWindow::clearText() {
    // Открываем диалог для сохранения временного файла
    QString fileName = QFileDialog::getSaveFileName(this, tr("Сохранить временный файл"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("Text Files (*.txt);;All Files (*)"));

    if (!fileName.isEmpty()) {
        // Сохраняем текст в указанный файл
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << textEdit->toPlainText();
            file.close();
            tempFileName = fileName;
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось сохранить временный файл."));
        }
    } else {
        QMessageBox::information(this, tr("Отмена"), tr("Сохранение временного файла отменено."));
    }

    // Очищаем текстовое поле
    textEdit->clear();
}

void MainWindow::undoText() {
    // Восстанавливаем текст из временного файла
    if (!tempFileName.isEmpty()) {
        QFile tempFile(tempFileName);
        if (tempFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&tempFile);
            QString restoredText = in.readAll();
            tempFile.close();
            textEdit->setPlainText(restoredText);
            tempFileName.clear();
        } else {
            QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть временный файл для восстановления."));
        }
    } else {
        QMessageBox::information(this, tr("Ошибка"), tr("Нет временного файла для восстановления."));
    }
}

void MainWindow::copyText() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textEdit->textCursor().selectedText());
}

void MainWindow::pasteText() {
    QClipboard *clipboard = QApplication::clipboard();
    textEdit->insertPlainText(clipboard->text());
}
