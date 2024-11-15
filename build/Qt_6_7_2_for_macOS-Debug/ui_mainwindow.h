/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openRtfAction;
    QAction *createRtfAction;
    QAction *saveRtfAction;
    QAction *findAction;
    QAction *replaceAction;
    QAction *clearAction;
    QAction *undoAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *insertTableAction;
    QAction *openGraphicsEditorAction;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *graphicsEditorMenu;
    QToolBar *toolBar;
    QToolBar *controlPanel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 720);
        openRtfAction = new QAction(MainWindow);
        openRtfAction->setObjectName("openRtfAction");
        createRtfAction = new QAction(MainWindow);
        createRtfAction->setObjectName("createRtfAction");
        saveRtfAction = new QAction(MainWindow);
        saveRtfAction->setObjectName("saveRtfAction");
        saveRtfAction->setCheckable(false);
        saveRtfAction->setEnabled(true);
        findAction = new QAction(MainWindow);
        findAction->setObjectName("findAction");
        replaceAction = new QAction(MainWindow);
        replaceAction->setObjectName("replaceAction");
        clearAction = new QAction(MainWindow);
        clearAction->setObjectName("clearAction");
        undoAction = new QAction(MainWindow);
        undoAction->setObjectName("undoAction");
        copyAction = new QAction(MainWindow);
        copyAction->setObjectName("copyAction");
        pasteAction = new QAction(MainWindow);
        pasteAction->setObjectName("pasteAction");
        insertTableAction = new QAction(MainWindow);
        insertTableAction->setObjectName("insertTableAction");
        openGraphicsEditorAction = new QAction(MainWindow);
        openGraphicsEditorAction->setObjectName("openGraphicsEditorAction");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1280, 24));
        fileMenu = new QMenu(menuBar);
        fileMenu->setObjectName("fileMenu");
        editMenu = new QMenu(menuBar);
        editMenu->setObjectName("editMenu");
        graphicsEditorMenu = new QMenu(menuBar);
        graphicsEditorMenu->setObjectName("graphicsEditorMenu");
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        toolBar->setEnabled(true);
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        controlPanel = new QToolBar(MainWindow);
        controlPanel->setObjectName("controlPanel");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, controlPanel);

        menuBar->addAction(fileMenu->menuAction());
        menuBar->addAction(editMenu->menuAction());
        menuBar->addAction(graphicsEditorMenu->menuAction());
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
        graphicsEditorMenu->addAction(openGraphicsEditorAction);
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

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\242\320\265\320\272\321\201\321\202\320\276\320\262\321\213\320\271 \320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200", nullptr));
        openRtfAction->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 .rtf", nullptr));
#if QT_CONFIG(shortcut)
        openRtfAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        createRtfAction->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 .rtf", nullptr));
#if QT_CONFIG(shortcut)
        createRtfAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        saveRtfAction->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 .rtf", nullptr));
#if QT_CONFIG(shortcut)
        saveRtfAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        findAction->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\271\321\202\320\270", nullptr));
#if QT_CONFIG(shortcut)
        findAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        replaceAction->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        clearAction->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        undoAction->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\320\275\321\203\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        undoAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        copyAction->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\277\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        copyAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        pasteAction->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", nullptr));
#if QT_CONFIG(shortcut)
        pasteAction->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        insertTableAction->setText(QCoreApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214 \321\202\320\260\320\261\320\273\320\270\321\206\321\203", nullptr));
        openGraphicsEditorAction->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        fileMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", nullptr));
        editMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
        graphicsEditorMenu->setTitle(QCoreApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \321\200\320\265\320\264\320\260\320\272\321\202\320\276\321\200", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\236\321\201\320\275\320\276\320\262\320\275\321\213\320\265 \320\264\320\265\320\271\321\201\321\202\320\262\320\270\321\217", nullptr));
        controlPanel->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\320\275\320\265\320\273\321\214 \321\203\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\321\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
