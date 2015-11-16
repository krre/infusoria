#include <QCoreApplication>
#include <QtCore>
#include "global/app.h"
#include "global/macro.h"
#include "database/init.h"
#include "mind/mind.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(App::name());
    QCoreApplication::setApplicationVersion(App::version());

    QCommandLineParser parser;
    parser.setApplicationDescription(QString("Simulator of %1 AI units").arg(App::name()));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "AI unit to create or run"));
    parser.addOptions({
        {{"r", "repl"}, QCoreApplication::translate("main", "Interactive mode")},
        {{"n", "new"}, QCoreApplication::translate("main", "Create new AI unit")}

    });

    parser.process(app);

    if (argc == 1) {
        parser.showHelp();
    } else {
        const QStringList args = parser.positionalArguments();
        if (args.count() == 0) {
            console("Unknown source file");
        } else {
            QString filePath = args.at(0);
            qDebug() << filePath;

            if (parser.isSet("new")) {
                Init::create(filePath);
            } else if (parser.isSet("repl")) {
                qDebug() << "repl";
            } else {
                Mind mind(filePath);
                mind.run();
                return app.exec();
            }
        }
    }

    return EXIT_SUCCESS;
}
