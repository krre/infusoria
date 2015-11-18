#include <QCoreApplication>
#include <QtCore>
#include "global/app.h"
#include "global/macro.h"
#include "database/init.h"
#include "repl/repl.h"
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

            if (parser.isSet("new")) {
                Init::create(filePath);
                return EXIT_SUCCESS;
            }

            QFileInfo checkFile(filePath);
            if (!(checkFile.exists() && checkFile.isFile())) {
                qDebug() << "File" << filePath << "not found";
                return EXIT_SUCCESS;
            }

            Mind* mind;
            Repl* repl;

            if (parser.isSet("repl")) {
                repl = new Repl(filePath);
                repl->run();
            } else {
                mind = new Mind(filePath);
                mind->run();
            }

            int exitCode = app.exec();
            delete mind;
            delete repl;
            return exitCode;
        }
    }

    return EXIT_SUCCESS;
}
