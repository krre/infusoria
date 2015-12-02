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

QPointer<Settings> settings;

int main(int argc, char *argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName(App::name());
    appication.setApplicationVersion(App::version());

    ::settings = new Settings();
    QSharedPointer<Repl> repl;
    QSharedPointer<InfuController> infuController = QSharedPointer<InfuController>(new InfuController);

    QCommandLineParser parser;
    parser.setApplicationDescription(App::name());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Infusoria unit to create or run"));
    parser.addOptions({
        {{"g", "gui"}, QCoreApplication::translate("main", "GUI mode")},
        {{"r", "repl"}, QCoreApplication::translate("main", "Interactive mode")},
        {{"n", "new"}, QCoreApplication::translate("main", "Create new Infusoria unit")}
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
        }

        const QStringList args = parser.positionalArguments();
        if (args.count() == 0) {
            qDebug() << "Unknown source file";
        } else {
            QString filePath = args.at(0);

            if (parser.isSet("new")) {
                Init::create(filePath);
                return EXIT_SUCCESS;
            }

            QFileInfo fileInfo(filePath);
            if (!(fileInfo.exists() && fileInfo.isFile())) {
                qDebug() << "File" << filePath << "not found";
                return EXIT_SUCCESS;
            }

            Logger& logger = Logger::instance();
            logger.setInfuFile(fileInfo);

            if (parser.isSet("repl")) {
                repl = repl.create(filePath);
                repl->run();
            }

            return appication.exec();
        }
    }

    return EXIT_SUCCESS;
}
