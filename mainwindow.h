#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QStack> // Добавляем QStack для хранения состояний текста

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
    void clearText();  // Новый слот для очистки текста
    void undoText();   // Новый слот для возврата к предыдущему состоянию
    void copyText();   // Новый слот для копирования текста
    void pasteText();  // Новый слот для вставки текста

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QString currentRtfFileName;
    QString previousText; // Переменная для хранения предыдущего текста
    QAction *saveRtfAction; // Объявление переменной для действия "Сохранить .rtf"
    QStack<QString> textStack; // Стек для хранения состояний текста
};

#endif // MAINWINDOW_H
