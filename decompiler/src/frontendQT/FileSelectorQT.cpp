#include "frontendQT/FileSelectorQT.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QVBoxLayout>
#include <QLabel>
#include <QMimeData>
#include <QPushButton>
#include <QFileSelector>
#include <QFileDialog>

#include <iostream>



frontend::FileSelectorQT::FileSelectorQT(QWidget *parent)
: QWidget(parent)
{
    auto button = new QPushButton("Select File To Decompile", this);
    connect(button, &QPushButton::clicked, this, &FileSelectorQT::onSelectFile);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(button);
}

void frontend::FileSelectorQT::onSelectFile() {
    QString filePath = QFileDialog::getOpenFileName(this);
    std::cout << filePath.toStdString() << std::endl;

    QString copy = filePath;
    if (!copy.isEmpty()) {
        emit selectedFile(copy);
    }
}



