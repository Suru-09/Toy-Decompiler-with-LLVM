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

namespace frontend {

class MainWindowQT : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindowQT(QMainWindow *parent = nullptr);
    ~MainWindowQT() override = default;

    void loadDecompiledFiles(const QString& path);

public slots:
    void openFile(QListWidgetItem* item);

private:
    QListWidget* m_fileListWidget;
    QPlainTextEdit* m_textEdit;
    QString m_currentFilePath;
};

}   // end of namespace frontend

#endif //REVERSE_ENGINEERING_TOOL_MAINWINDOWQT_H
