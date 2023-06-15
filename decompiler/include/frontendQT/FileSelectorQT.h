#ifndef REVERSE_ENGINEERING_TOOL_FILESELECTORQT_H
#define REVERSE_ENGINEERING_TOOL_FILESELECTORQT_H

#include <QWidget>

namespace frontend {

class FileSelectorQT : public QWidget {
Q_OBJECT

public:
    explicit FileSelectorQT(QWidget *parent = nullptr);

public slots:
    void onSelectFile();

signals:
    void selectedFile(const QString& filePath);
};

}   // end of namespace frontend

#endif //REVERSE_ENGINEERING_TOOL_FILESELECTORQT_H
