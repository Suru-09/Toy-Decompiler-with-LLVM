#include "frontendQT/FileViewerQT.h"
#include "frontendQT/MySyntaxHighlighterQT.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QFileInfo>
#include <QDir>
#include <QGuiApplication>
#include <QLabel>
#include <QHeaderView>

#include <algorithm>
#include <QPushButton>

frontend::FileViewerQT::FileViewerQT(QWidget *parent, const QString& path)
: QWidget(parent)
{
    auto layout = new QHBoxLayout(this);
    auto splitter = new QSplitter(this);
    m_fileListWidget = new QListWidget(this);
    m_textViewer = new QPlainTextEdit(this);

    const qreal scaleFactor = QGuiApplication::primaryScreen()->logicalDotsPerInch() / 96.0;
    const int baseFontSize = 26; // Base font size for 96 dpi
    const int scaledFontSize = static_cast<int>(baseFontSize * scaleFactor);
    QFont font = m_textViewer->font();
    font.setPointSize(scaledFontSize);
    m_textViewer->setFont(font);

    // set up syntax highlighting
    auto highlighter = new MySyntaxHighlighterQT(m_textViewer->document());

    splitter->addWidget(m_fileListWidget);
    splitter->addWidget(m_textViewer);

    auto backButton = new QPushButton("Back to file selector", this);
    layout->addWidget(backButton);
    layout->addWidget(splitter);

    // load all decompiled files in the given directory
    loadDecompiledFiles(path);

    unsigned long maxFileNameLength = 0;
    for(auto i = 0; i < m_fileListWidget->count(); ++i)
    {
        auto item = m_fileListWidget->item(i);
        // count characters in the file name
        auto fileName = item->text().toStdString();
        unsigned long numChars = fileName.size();
        maxFileNameLength = std::max(maxFileNameLength, numChars);

        item->setFont(font);
    }
    auto leftSideWidth = maxFileNameLength + maxFileNameLength / 2;
    // Set the width and font for the left side (m_fileListWidget)
    m_fileListWidget->setFixedWidth(leftSideWidth * 20);

    connect(m_fileListWidget, &QListWidget::itemClicked, this, &FileViewerQT::onFileClicked);
    connect(backButton, &QPushButton::clicked, this, &FileViewerQT::onBackButtonClicked);
}

void frontend::FileViewerQT::onFileClicked(QListWidgetItem* item)
{
    auto filePath = m_currentFilePath + "/" + item->text();
    // check if the file is already cached
    if(m_cachedFiles.contains(filePath))
    {
        m_textViewer->setPlainText(m_cachedFiles[filePath]);
        m_textViewer->update();
        return;
    }

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        auto plainText = stream.readAll();
        m_textViewer->setPlainText(plainText);
        m_cachedFiles[filePath] = plainText;
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

void frontend::FileViewerQT::onBackButtonClicked() {
    emit backButtonClicked();
}

