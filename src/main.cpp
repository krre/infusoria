#include <QCoreApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Simulator of AI units");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("source", QCoreApplication::translate("main", "Infusoria file to run"));

    parser.addOptions({
        {{"d", "dump"}, QCoreApplication::translate("main", "Dump IR code")},
        {{"e", "execute"}, QCoreApplication::translate("main", "Execute in memory")}
    });

    parser.process(app);

    if (argc == 1) {
        parser.showHelp();
    } else {
        const QStringList args = parser.positionalArguments();
        if (args.count() == 0) {
            qDebug() << "Infusoria: unknown source file";
            parser.showHelp();
        } else {
            QString filePath = args.at(0);
            qDebug() << filePath;
            return app.exec();
        }
    }

    return EXIT_SUCCESS;
}
