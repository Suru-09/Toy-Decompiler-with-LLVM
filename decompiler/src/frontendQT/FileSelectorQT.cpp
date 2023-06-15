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
    button->setStyleSheet(
            "QPushButton {"
            "    background-color: #666666;"
            "    color: #F5F5F5;"
            "    border: none;"
            "    padding: 8px 16px;"
            "    border-radius: 4px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #999999;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #444444;"
            "}"
    );
    connect(button, &QPushButton::clicked, this, &FileSelectorQT::onSelectFile);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(button, 0, Qt::AlignCenter);
}

void frontend::FileSelectorQT::onSelectFile() {
    QString filePath = QFileDialog::getOpenFileName(this);
    std::cout << filePath.toStdString() << std::endl;

    QString copy = filePath;
    if (!copy.isEmpty()) {
        emit selectedFile(copy);
    }
}



