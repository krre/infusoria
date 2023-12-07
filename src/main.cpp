#include "database/init.h"
#include "repl/repl.h"
#include "base/infucontroller.h"
#include "base/fileoperations.h"
#include "net/websocketmanager.h"
#include <app.h>
#include <utils.h>
#include <settings.h>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

QPointer<Settings> settings;
QPointer<InfuController> infuController;
QPointer<WebSocketManager> webSocketManager;

int main(int argc, char *argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName("Infusoria Manager");
    appication.setApplicationVersion("0.1.0");

    QString filePath = qApp->applicationDirPath() + "/infusoria.ini";
    ::settings = new Settings(filePath);
    if (!QFile::exists(filePath)) {
        settings->setValue("Path", "workspace", QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/infusoria");
        settings->setValue("Path", "log", qApp->applicationDirPath() + "/log");
        settings->setValue("Network", "port", 51000);
    }

    QSharedPointer<Repl> repl;
    infuController = new InfuController;
    webSocketManager = new WebSocketManager;

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOptions({
        {{"g", "gui"}, QCoreApplication::translate("main", "GUI mode")},
        {{"r", "repl"}, QCoreApplication::translate("main", "Interactive mode")},
    });

    parser.process(appication);

    if (argc == 1) {
        parser.showHelp();
    } else {
        if (parser.isSet("gui")) {
            App app;
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

            return appication.exec();

        } else if (parser.isSet("repl")) {
            repl = repl.create();
            repl->run();
            return appication.exec();
        }
    }

    return EXIT_SUCCESS;
}
