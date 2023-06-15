#include "frontendQT/FileViewerQT.h"
#include "frontendQT/MySyntaxHighlighterQT.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QDir>

frontend::FileViewerQT::FileViewerQT(QWidget *parent, const QString& path)
: QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    auto splitter = new QSplitter(this);
    m_fileListWidget = new QListWidget(this);
    m_textViewer = new QPlainTextEdit(this);

    // set up syntax highlighting
    auto highlighter = new MySyntaxHighlighterQT(m_textViewer->document());

    splitter->addWidget(m_fileListWidget);
    splitter->addWidget(m_textViewer);  // Text viewer takes up remaining space
    layout->addWidget(splitter);

    // load all decompiled files in the given directory
    loadDecompiledFiles(path);

    connect(m_fileListWidget, &QListWidget::itemClicked, this, &FileViewerQT::onFileClicked);
}

void frontend::FileViewerQT::onFileClicked(QListWidgetItem* item)
{
    auto filePath = m_currentFilePath + "/" + item->text();
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        m_textViewer->setPlainText(stream.readAll());
    }
    m_textViewer->update();
}

void frontend::FileViewerQT::loadDecompiledFiles(const QString& path)
{
    // search for all files in the directory and add them to the list
    std::cout << "Loading decompiled files from " << path.toStdString() << std::endl;
    QDir dir(path);
    m_currentFilePath = path;
    QStringList files = dir.entryList(QStringList() << "*", QDir::Files);
    for(const auto& file : files)
    {
        std::cout << "Adding file " << file.toStdString() << std::endl;
        m_fileListWidget->addItem(file);
    }

    // set and update the text edit with the first file
    if(!files.empty())
    {
        QString filePath = path + "/" + files.front();
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&file);
            m_textViewer->setPlainText(stream.readAll());
        }
    }

    m_textViewer->update();
}

