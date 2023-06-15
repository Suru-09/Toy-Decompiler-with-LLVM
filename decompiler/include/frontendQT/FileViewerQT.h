#ifndef REVERSE_ENGINEERING_TOOL_FILEVIEWER_H
#define REVERSE_ENGINEERING_TOOL_FILEVIEWER_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMap>
#include <QPlainTextEdit>

namespace frontend {

class FileViewerQT : public QWidget {
    Q_OBJECT

public:
    explicit FileViewerQT(QWidget* parent = nullptr, const QString& path="");
    ~FileViewerQT() override = default;

    void loadDecompiledFiles(const QString& path);

public slots:
    void onFileClicked(QListWidgetItem* item);
    void onBackButtonClicked();

signals:
    void backButtonClicked();

private:
    QListWidget* m_fileListWidget;
    QPlainTextEdit* m_textViewer;
    QString m_currentFilePath;
    QMap<QString, QString> m_cachedFiles;

private:
    void openFile(QListWidgetItem* item);
    void loadDecompiledFile(const QString& path);

};

}   // end of namespace frontend


#endif //REVERSE_ENGINEERING_TOOL_FILEVIEWER_H
