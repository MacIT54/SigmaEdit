#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QMenuBar>
#include <QInputDialog>
#include <QClipboard>
#include <QApplication>
#include <QCloseEvent>
#include <QStandardPaths>
#include <QToolBar>
#include <QStyle>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QColorDialog>
#include <QPushButton>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    textEdit(new QTextEdit(this)),
    currentRtfFileName(""),
    tempFileName(""),
    isTextChanged(false),
    cellPadding(0)
{
    ui->setupUi(this);
    loadSettings();

    // Подключение слота отслеживания изменений текста
    connect(textEdit, &QTextEdit::textChanged, this, &MainWindow::onTextChanged);

    // Создание меню
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *fileMenu = new QMenu("Файл", this);
    QMenu *editMenu = new QMenu("Правка", this);

    QAction *openRtfAction = new QAction("Открыть .rtf", this);
    openRtfAction->setShortcut(QKeySequence::Open);  // Горячая клавиша Ctrl+O
    openRtfAction->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));

    QAction *createRtfAction = new QAction("Создать .rtf", this);
    createRtfAction->setShortcut(QKeySequence::New);  // Горячая клавиша Ctrl+N
    createRtfAction->setIcon(style()->standardIcon(QStyle::SP_FileIcon));

    saveRtfAction = new QAction("Сохранить .rtf", this);
    saveRtfAction->setShortcut(QKeySequence::Save);  // Горячая клавиша Ctrl+S
    saveRtfAction->setIcon(style()->standardIcon(QStyle::SP_DriveFDIcon));
    saveRtfAction->setEnabled(false);

    QAction *findAction = new QAction("Найти", this);
    findAction->setShortcut(QKeySequence::Find);  // Горячая клавиша Ctrl+F
    findAction->setIcon(style()->standardIcon(QStyle::SP_FileDialogContentsView));

    QAction *replaceAction = new QAction("Заменить", this);
    replaceAction->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    QAction *clearAction = new QAction("Очистить", this);
    clearAction->setIcon(style()->standardIcon(QStyle::SP_TrashIcon));

    QAction *undoAction = new QAction("Вернуть", this);
    undoAction->setShortcut(QKeySequence::Undo);  // Горячая клавиша Ctrl+Z
    undoAction->setIcon(style()->standardIcon(QStyle::SP_ArrowBack));

    QAction *copyAction = new QAction("Копировать", this);
    copyAction->setShortcut(QKeySequence::Copy);  // Горячая клавиша Ctrl+C
    copyAction->setIcon(style()->standardIcon(QStyle::SP_FileIcon));

    QAction *pasteAction = new QAction("Вставить", this);
    pasteAction->setShortcut(QKeySequence::Paste);  // Горячая клавиша Ctrl+V
    pasteAction->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));

    QAction *insertTableAction = new QAction(QIcon::fromTheme("insert-table", style()->standardIcon(QStyle::SP_DialogApplyButton)), tr("Вставить таблицу"), this);
    connect(insertTableAction, &QAction::triggered, this, &MainWindow::insertTable);


    fileMenu->addAction(openRtfAction);
    fileMenu->addAction(createRtfAction);
    fileMenu->addAction(saveRtfAction);

    editMenu->addAction(findAction);
    editMenu->addAction(replaceAction);
    editMenu->addAction(clearAction);
    editMenu->addAction(undoAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(insertTableAction);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(editMenu);
    setMenuBar(menuBar);

    // Панель инструментов с иконками
    QToolBar *toolBar = addToolBar("Основные действия");
    toolBar->addAction(openRtfAction);
    toolBar->addAction(createRtfAction);
    toolBar->addAction(saveRtfAction);
    toolBar->addSeparator();
    toolBar->addAction(findAction);
    toolBar->addAction(replaceAction);
    toolBar->addAction(clearAction);
    toolBar->addSeparator();
    toolBar->addAction(undoAction);
    toolBar->addAction(copyAction);
    toolBar->addAction(pasteAction);
    toolBar->addAction(insertTableAction);

    setCentralWidget(textEdit);
    textEdit->setVisible(false);

    // Панель управления
    QToolBar *controlPanel = addToolBar("Панель управления");

    // Выбор размера шрифта
    QComboBox *fontSizeComboBox = new QComboBox(this);
    fontSizeComboBox->addItems({"8", "10", "12", "14", "16", "18", "20", "24", "28", "32"});
    connect(fontSizeComboBox, &QComboBox::currentTextChanged, [this](const QString &size) {
        textEdit->setFontPointSize(size.toFloat());
    });

    controlPanel->addWidget(new QLabel("Размер шрифта:"));
    controlPanel->addWidget(fontSizeComboBox);

    // Кнопка для выбора цвета
    QPushButton *colorButton = new QPushButton("Выбрать цвет", this);
    connect(colorButton, &QPushButton::clicked, this, [this]() {
        QColor color = QColorDialog::getColor(textEdit->textColor(), this, "Выберите цвет текста");
        if (color.isValid()) {
            textEdit->setTextColor(color);
        }
    });

    controlPanel->addWidget(new QLabel("Цветовая схема:"));
    controlPanel->addWidget(colorButton);

    // Выбор отступов в ячейках (пока не реализовано)
    QSpinBox *paddingSpinBox = new QSpinBox(this);
    paddingSpinBox->setRange(0, 50);
    paddingSpinBox->setValue(0);

    connect(paddingSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this](int padding) {
        cellPadding = padding; // Сохраняем значение отступа
    });

    controlPanel->addWidget(new QLabel("Отступы в ячейках:"));
    controlPanel->addWidget(paddingSpinBox);

    // Подключение сигналов к слотам
    connect(openRtfAction, &QAction::triggered, this, &MainWindow::openRtfFile);
    connect(createRtfAction, &QAction::triggered, this, &MainWindow::createRtfFile);
    connect(saveRtfAction, &QAction::triggered, this, &MainWindow::saveRtfFile);
    connect(findAction, &QAction::triggered, this, &MainWindow::findText);
    connect(replaceAction, &QAction::triggered, this, &MainWindow::replaceText);
    connect(clearAction, &QAction::triggered, this, &MainWindow::clearText);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undoText);
    connect(copyAction, &QAction::triggered, this, &MainWindow::copyText);
    connect(pasteAction, &QAction::triggered, this, &MainWindow::pasteText);
    connect(insertTableAction, &QAction::triggered, this, &MainWindow::insertTable);

    loadSettings();
}

MainWindow::~MainWindow() {
    saveSettings();  // Сохранить настройки перед закрытием
    delete ui;
}

void MainWindow::insertTable() {
    bool ok;
    int rows = QInputDialog::getInt(this, "Вставить таблицу", "Введите количество строк:", 2, 1, 100, 1, &ok);
    if (ok) {
        int cols = QInputDialog::getInt(this, "Вставить таблицу", "Введите количество столбцов:", 2, 1, 100, 1, &ok);
        if (ok) {
            QString tableHtml = "<table style='border-collapse: collapse;'>";
            for (int i = 0; i < rows; ++i) {
                tableHtml += "<tr>";
                for (int j = 0; j < cols; ++j) {
                    tableHtml += QString("<td style='padding: %10px; border: 10px solid black;'></td>").arg(cellPadding);
                }
                tableHtml += "</tr>";
            }
            tableHtml += "</table>";
            textEdit->append(tableHtml);
        }
    }
}

QString MainWindow::createTableHtml(int rows, int cols) {
    QString htmlTable = "<table border='10' cellspacing='10' cellpadding='5'>";
    for (int i = 0; i < rows; ++i) {
        htmlTable += "<tr>";
        for (int j = 0; j < cols; ++j) {
            htmlTable += "<td> </td>";
        }
        htmlTable += "</tr>";
    }
    htmlTable += "</table>";
    return htmlTable;
}

void MainWindow::openRtfFile() {
    QString fileName = QFileDialog::getOpenFileName(this, "Открыть файл .rtf", "", "Файлы .rtf (*.rtf);;Все файлы (*)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&file);
            textEdit->setHtml(in.readAll());  // Измените на setHtml
            currentRtfFileName = fileName;
            isTextChanged = false;
            saveRtfAction->setEnabled(true);
            textEdit->setVisible(true); // Показать QTextEdit
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        }
    }
}


void MainWindow::createRtfFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Создать файл .rtf", "", "Файлы .rtf (*.rtf);;Все файлы (*)");
    if (!fileName.isEmpty()) {
        // Создаем новый файл в указанном месте
        QFile file(fileName);
        if (file.open(QFile::WriteOnly)) {
            currentRtfFileName = fileName;
            textEdit->clear();  // Очистить текстовое поле для нового файла
            isTextChanged = false;
            saveRtfAction->setEnabled(true);
            textEdit->setVisible(true); // Показать QTextEdit
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось создать файл.");
        }
    }
}


void MainWindow::saveRtfFile() {
    if (currentRtfFileName.isEmpty()) {
        currentRtfFileName = QFileDialog::getSaveFileName(this, "Сохранить файл .rtf", "", "Файлы .rtf (*.rtf);;Все файлы (*)");
    }
    if (!currentRtfFileName.isEmpty()) {
        QFile file(currentRtfFileName);
        if (file.open(QFile::WriteOnly)) {
            QTextStream out(&file);
            out << textEdit->document()->toHtml();  // Сохраняем содержимое в HTML-формате
            isTextChanged = false;
            saveRtfAction->setEnabled(true);
            file.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
        }
    }
}



void MainWindow::findText() {
    bool ok;
    QString searchText = QInputDialog::getText(this, "Найти текст", "Введите текст для поиска:", QLineEdit::Normal, "", &ok);
    if (ok && !searchText.isEmpty()) {
        QTextDocument::FindFlags options;
        options |= QTextDocument::FindWholeWords;  // Опция поиска целых слов
        bool found = false;

        // Используем регулярное выражение для поиска
        QRegExp regExp(searchText, Qt::CaseInsensitive, QRegExp::Wildcard);
        textEdit->moveCursor(QTextCursor::Start);  // Начинаем поиск с начала текста

        while (textEdit->find(regExp, options)) {
            found = true; // Нашли текст
            break;        // Прерываем на первом совпадении
        }

        if (!found) {
            QMessageBox::information(this, "Результат поиска", "Текст не найден.");
        }
    }
}

void MainWindow::replaceText() {
    bool ok;
    QString searchText = QInputDialog::getText(this, "Заменить текст", "Введите текст для замены:", QLineEdit::Normal, "", &ok);
    if (ok && !searchText.isEmpty()) {
        QString replaceText = QInputDialog::getText(this, "Заменить текст", "Введите новый текст:", QLineEdit::Normal, "", &ok);
        if (ok) {
            QString content = textEdit->toPlainText();
            content.replace(searchText, replaceText);
            textEdit->setPlainText(content);
            isTextChanged = true;
        }
    }
}

void MainWindow::saveTempFile() {
    tempFileName = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/tempfile.rtf";
    QFile tempFile(tempFileName);
    if (tempFile.open(QFile::WriteOnly)) {
        QTextStream out(&tempFile);
        out << textEdit->document()->toHtml();  // Сохраняем содержимое в HTML-формате
        tempFile.close();
    }
}

void MainWindow::clearText() {
    // Открываем диалог для выбора места сохранения временного файла
    tempFilePath = QFileDialog::getSaveFileName(this, "Сохранить временный файл", "", "RTF Files (*.rtf);;All Files (*)");

    // Если пользователь выбрал файл, сохраняем текущий текст
    if (!tempFilePath.isEmpty()) {
        QFile tempFile(tempFilePath);
        if (tempFile.open(QFile::WriteOnly)) {
            QTextStream out(&tempFile);
            out << textEdit->document()->toHtml(); // Сохраняем содержимое в HTML-формате
            tempFile.close();
            textEdit->clear(); // Очищаем текстовое поле после сохранения
            isTextChanged = true;
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось сохранить временный файл.");
        }
    }
}

void MainWindow::restoreFromTempFile() {
    if (!tempFilePath.isEmpty()) {
        QFile tempFile(tempFilePath);
        if (tempFile.open(QFile::ReadOnly | QFile::Text)) {
            QTextStream in(&tempFile);
            textEdit->setHtml(in.readAll()); // Восстанавливаем текст из временного файла
            isTextChanged = false;
            tempFile.close();
        } else {
            QMessageBox::warning(this, "Ошибка", "Не удалось восстановить текст из временного файла.");
        }
    } else {
        QMessageBox::information(this, "Информация", "Временный файл не выбран.");
    }
}

void MainWindow::undoText() {
    restoreFromTempFile();
}

void MainWindow::copyText() {
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(textEdit->textCursor().selectedText());
}

void MainWindow::pasteText() {
    QClipboard *clipboard = QApplication::clipboard();
    textEdit->insertPlainText(clipboard->text());
}

void MainWindow::onTextChanged() {
    isTextChanged = true;
    saveRtfAction->setEnabled(true);
}



void MainWindow::loadSettings() {
    QSettings settings("MyCompany", "MyApp"); // Замените MyCompany и MyApp на свои значения
    double fontSize = settings.value("fontSize", 12).toDouble(); // Значение по умолчанию
    QString backgroundColor = settings.value("backgroundColor", "#FFFFFF").toString(); // Белый по умолчанию
    QString lastFilePath = settings.value("lastFilePath", "").toString(); // Путь по умолчанию

    // Устанавливаем загруженные настройки
    QFont font = textEdit->font();
    font.setPointSize(fontSize);
    textEdit->setFont(font);

    // Устанавливаем цвет фона
    textEdit->setStyleSheet("background-color: " + backgroundColor + ";");

    // Если есть последний файл, открываем его
    if (!lastFilePath.isEmpty()) {
        openFile(lastFilePath); // Используйте ваш метод для открытия файла
    }
}

void MainWindow::openFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Не удалось открыть файл"));
        return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
    currentFilePath = fileName; // Сохраняем текущий путь файла
    file.close();
}

void MainWindow::saveSettings() {
    QSettings settings("MyCompany", "MyApp"); // Замените MyCompany и MyApp на свои значения
    settings.setValue("fontSize", textEdit->fontPointSize());
    settings.setValue("backgroundColor", textEdit->palette().color(QPalette::Background).name());
    settings.setValue("lastFilePath", currentFilePath);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (isTextChanged) { // Если текст был изменён
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Сохранение файла",
                                      "Сохранить изменения в файле?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            // Если путь файла известен, сохраняем его
            if (!currentFilePath.isEmpty()) {
                saveFileToPath(currentFilePath);
                event->accept();
            } else {
                // Если файла нет, предлагаем сохранить как новый файл
                QString savePath = QFileDialog::getSaveFileName(this, "Сохранить файл как", "", "RTF Files (*.rtf);;All Files (*)");
                if (!savePath.isEmpty()) {
                    saveFileToPath(savePath);
                    event->accept();
                } else {
                    event->ignore(); // Отмена закрытия, если файл не выбран
                }
            }
        } else if (reply == QMessageBox::No) {
            event->accept(); // Закрыть без сохранения
        } else {
            event->ignore(); // Отменить закрытие
        }
    } else {
        event->accept(); // Закрыть без сохранения, если изменений нет
    }
}

void MainWindow::saveFileToPath(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << textEdit->document()->toHtml(); // Сохраняем содержимое как HTML
        currentFilePath = filePath; // Обновляем путь к текущему файлу
        isTextChanged = false; // Сбрасываем флаг изменений
        file.close();
    } else {
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить файл.");
    }
}
