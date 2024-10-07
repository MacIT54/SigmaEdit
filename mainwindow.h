#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QStack>
#include <QFile> // Для работы с файлами

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openRtfFile();
    void createRtfFile();
    void saveRtfFile();
    void findText();
    void replaceText();
    void clearText();  // Слот для очистки текста
    void undoText();   // Слот для восстановления текста
    void copyText();   // Слот для копирования текста
    void pasteText();  // Слот для вставки текста

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QString currentRtfFileName;
    QString tempFileName; // Путь к временному файлу
    QAction *saveRtfAction;
    QStack<QString> textStack; // Стек для хранения состояний текста
};

#endif // MAINWINDOW_H
