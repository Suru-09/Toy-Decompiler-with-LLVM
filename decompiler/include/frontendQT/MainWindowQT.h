#ifndef REVERSE_ENGINEERING_TOOL_MAINWINDOWQT_H
#define REVERSE_ENGINEERING_TOOL_MAINWINDOWQT_H

#include <QApplication>
#include <QFileDialog>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QSplitter>
#include <QDir>
#include <QWidget>
#include <QMainWindow>

#include <iostream>
#include <memory>
#include "FileSelectorQT.h"

namespace frontend {

class MainWindowQT : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowQT(QMainWindow *parent = nullptr);
    ~MainWindowQT() override = default;

public slots:
    void onFileReceived(const QString& filePath);
    void onReturnButtonClicked();

private:
    QListWidget* m_fileListWidget;
    QPlainTextEdit* m_textEdit;
    QString m_currentFilePath;

    bool decompileFiles(const QString &binPath);
    frontend::FileSelectorQT *loadFileSelector();
    void resizeScreen(const double &sizePercent);
};

}   // end of namespace frontend

#endif //REVERSE_ENGINEERING_TOOL_MAINWINDOWQT_H
