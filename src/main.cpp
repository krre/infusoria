#include "database/Init.h"
#include "repl/Repl.h"
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
    Application application(argc, argv);
    application.setApplicationName("Infusoria");
    application.setOrganizationName("Infusoria");
    application.setApplicationVersion("0.1.0");

    ::settings = new Settings;

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

    parser.process(application);

    if (argc == 1) {
        parser.showHelp();
    } else {
        if (parser.isSet("gui")) {
            Utils utils;
            Init init;
            FileOperations fileOperations;

            QQmlApplicationEngine engine;
            engine.rootContext()->setContextProperty("APP", &application);
            engine.rootContext()->setContextProperty("UTILS", &utils);
            engine.rootContext()->setContextProperty("Init", &init);
            engine.rootContext()->setContextProperty("Settings", settings);
            engine.rootContext()->setContextProperty("InfuController", infuController.data());
            engine.rootContext()->setContextProperty("FileOperations", &fileOperations);
            engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

            return application.exec();

        } else if (parser.isSet("repl")) {
            repl = repl.create();
            repl->run();
            return application.exec();
        }
    }

    return EXIT_SUCCESS;
}
