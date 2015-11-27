#include <QApplication>
#include <QtCore>
#include <QtQml>
#include "global/app.h"
#include "global/macro.h"
#include "database/init.h"
#include "repl/repl.h"
#include "mind/mind.h"
#include "logger/logger.h"
#include "base/settings.h"

QPointer<Settings> settings;

int main(int argc, char *argv[])
{
    QApplication appication(argc, argv);
    appication.setApplicationName(App::name());
    appication.setApplicationVersion(App::version());

    QSharedPointer<Mind> mind;
    QSharedPointer<Repl> repl;
    ::settings = new Settings();

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

            QQmlApplicationEngine engine;
            engine.rootContext()->setContextProperty("APP", &app);
            engine.rootContext()->setContextProperty("SETTINGS", settings);
            engine.load(QUrl(QStringLiteral("qrc:/gui/main.qml")));

            return appication.exec();
        }

        const QStringList args = parser.positionalArguments();
        if (args.count() == 0) {
            console("Unknown source file");
        } else {
            QString filePath = args.at(0);

            if (parser.isSet("new")) {
                Init::create(filePath);
                return EXIT_SUCCESS;
            }

            QFileInfo fileInfo(filePath);
            if (!(fileInfo.exists() && fileInfo.isFile())) {
                console("File " << filePath.toStdString() << " not found");
                return EXIT_SUCCESS;
            }

            Logger& logger = Logger::instance();
            logger.setInfuFile(fileInfo);

            if (parser.isSet("repl")) {
                repl = repl.create(filePath);
                repl->run();
            } else {
                mind = mind.create(filePath);
                mind->run();
            }

            return appication.exec();
        }
    }

    return EXIT_SUCCESS;
}
