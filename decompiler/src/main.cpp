#include <memory>

#include "udm/UDM.h"
#include "codeGen/CodeGeneration.h"
#include "settings/CodegenSettings.h"
#include "frontendQT/MainWindowQT.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    frontend::MainWindowQT mainWindow;
    mainWindow.show();

    return app.exec();
}
