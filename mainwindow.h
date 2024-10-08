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
    void createRtfFile();
    void openRtfFile();
    void saveRtfFile();

    void findText();
    void replaceText();
    void clearText();
    void undoText();
    void copyText();
    void pasteText();

    void saveTempFile();
    void restoreFromTempFile();
    void onTextChanged();

    QString createTableHtml(int rows, int col);
    void insertTable();
    void openFile(const QString &fileName);

private:
    void loadSettings();
    void saveSettings();
    void closeEvent(QCloseEvent *event) override;
    void saveFileToPath(const QString &filePath);

    Ui::MainWindow *ui;

    QTextEdit *textEdit;
    QString currentRtfFileName;
    QString tempFileName;

    bool isTextChanged;

    QAction *saveRtfAction;

    int cellPadding;

    QString currentFilePath;
    QString tempFilePath;
};


#endif // MAINWINDOW_H
