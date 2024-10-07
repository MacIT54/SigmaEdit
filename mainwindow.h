#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QSettings>  // Добавлено для работы с настройками

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
    void clearText();
    void undoText();
    void copyText();
    void pasteText();
    void onTextChanged(); // Слот для отслеживания изменений текста
    void insertTable();  // Объявляем функцию insertTable
    QString createTableHtml(int rows, int col);

private:
    void loadSettings();  // Загрузить настройки
    void saveSettings();  // Сохранить настройки
    void closeEvent(QCloseEvent *event) override; // Переопределение события закрытия окна

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QString currentRtfFileName;
    QString tempFileName;
    bool isTextChanged;  // Флаг для отслеживания изменений текста
    QAction *saveRtfAction;  // Указатель на действие сохранения
    int cellPadding;
};


#endif // MAINWINDOW_H
