#include "database/Init.h"
#include "base/InfuController.h"
#include "base/FileOperations.h"
#include "net/WebSocketManager.h"
#include <Application.h>
#include <Utils.h>
#include <Settings.h>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

QPointer<Settings> settings;
QPointer<InfuController> infuController;
QPointer<WebSocketManager> webSocketManager;

int main(int argc, char* argv[]) {
    Application app(argc, argv);
    app.setApplicationName("Infusoria");
    app.setOrganizationName("Infusoria");
    app.setApplicationVersion("0.1.0");

    ::settings = new Settings;

    if (settings->isEmpty()) {
        settings->setValue("Path", "workspace", QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/infusoria");
        settings->setValue("Path", "log", qApp->applicationDirPath() + "/log");
        settings->setValue("Network", "port", 51000);
        settings->sync();
    }

    infuController = new InfuController;
    webSocketManager = new WebSocketManager;

    Utils utils;
    Init init;
    FileOperations fileOperations;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("APP", &app);
    engine.rootContext()->setContextProperty("UTILS", &utils);
    engine.rootContext()->setContextProperty("Init", &init);
    engine.rootContext()->setContextProperty("Settings", settings);
    engine.rootContext()->setContextProperty("InfuController", infuController.data());
    engine.rootContext()->setContextProperty("FileOperations", &fileOperations);
    engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

    return app.exec();
}
