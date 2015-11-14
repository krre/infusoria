#include <QCoreApplication>
#include <QtCore>
#include "global/macro.h"
#include "database/init.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("Infusoria");
    QCoreApplication::setApplicationVersion("0.1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Simulator of Infusoria AI units");
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
            console("Infusoria: unknown source file");
        } else {
            QString filePath = args.at(0);
            qDebug() << filePath;

            if (parser.isSet("new")) {
                Init::create(filePath);
            } else if (parser.isSet("repl")) {
                qDebug() << "repl";
            } else {
                return app.exec();
            }
        }
    }

    return EXIT_SUCCESS;
}
