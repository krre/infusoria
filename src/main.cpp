#include <QApplication>
#include <QtCore>
#include <QtQml>
#include <app.h>
#include <utils.h>
#include <settings.h>
#include "database/init.h"
#include "repl/repl.h"
#include "logger/logger.h"
#include "base/infucontroller.h"
#include "net/websocketmanager.h"

QPointer<Settings> settings;
QPointer<InfuController> infuController;
QPointer<WebSocketManager> webSocketManager;

int main(int argc, char *argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName(App::name());
    appication.setApplicationVersion(App::version());

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
    parser.setApplicationDescription(App::name());
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

            QQmlApplicationEngine engine;
            engine.rootContext()->setContextProperty("APP", &app);
            engine.rootContext()->setContextProperty("UTILS", &utils);
            engine.rootContext()->setContextProperty("INIT", &init);
            engine.rootContext()->setContextProperty("SETTINGS", settings);
            engine.rootContext()->setContextProperty("INFU_CONTROLLER", infuController.data());
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
