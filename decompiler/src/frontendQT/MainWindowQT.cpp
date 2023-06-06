#include "frontendQT/MainWindowQT.h"
#include "logger/LoggerManager.h"

#include "frontendQT/MySyntaxHighlighterQT.h"

frontend::MainWindowQT::MainWindowQT(QMainWindow *parent)
: QMainWindow(parent)
{
    // load the initial widgets and a splitter
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);
    QSplitter* splitter = new QSplitter(Qt::Horizontal, centralWidget);
    // set the highlighter to the text edit

    layout->addWidget(splitter);
    m_fileListWidget = new QListWidget(splitter);
    m_textEdit = new QPlainTextEdit(splitter);
    auto highlighter = new frontend::MySyntaxHighlighterQT(m_textEdit->document());
    splitter->addWidget(m_fileListWidget);
    splitter->addWidget(m_textEdit);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 4);
    setCentralWidget(centralWidget);


    // connect QListWidget's signal to slot openFile
    connect(m_fileListWidget, &QListWidget::itemClicked, this, &MainWindowQT::openFile);
}

void frontend::MainWindowQT::openFile(QListWidgetItem* item)
{
    auto filePath = m_currentFilePath + "/" + item->text();
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        m_textEdit->setPlainText(stream.readAll());
    }
    m_textEdit->update();
}

void frontend::MainWindowQT::loadDecompiledFiles(const QString& path)
{
    // search for all files in the directory and add them to the list
    QDir dir(path);
    m_currentFilePath = path;
    QStringList files = dir.entryList(QStringList() << "*", QDir::Files);
    for(const auto& file : files)
    {
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
            m_textEdit->setPlainText(stream.readAll());
        }
    }

    m_textEdit->update();
}





