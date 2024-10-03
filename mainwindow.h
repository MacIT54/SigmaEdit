#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openRtfFile();
    void createRtfFile();
    void saveRtfFile();
    void findText();       // Новый слот для поиска текста
    void replaceText();    // Новый слот для замены текста

private:
    Ui::MainWindow *ui;
    QTextEdit *textEdit;
    QString currentRtfFileName;
    QAction *saveRtfAction; // Добавлено: Указатель на действие "Сохранить .rtf"
};

#endif // MAINWINDOW_H
