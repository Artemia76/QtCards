#include "gui/mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QString>
#include "tools/clogger.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    CLogger* log = CLogger::instance();
    QString Prefix;
    QColor Color;
    switch (type) {
    case QtDebugMsg:
        Prefix= QObject::tr("Debug");
        Color = Qt::darkMagenta;
        break;
    case QtInfoMsg:
        Prefix= QObject::tr("Info");
        Color = Qt::darkBlue;
        break;
    case QtWarningMsg:
        Prefix= QObject::tr("Warning");
        Color = Qt::darkRed;
        break;
    case QtCriticalMsg:
        Prefix= QObject::tr("Critical");
        Color = Qt::red;
    case QtFatalMsg:
        Prefix= QObject::tr("Fatal");
        Color = Qt::red;
    }
    log->log(Prefix + QObject::tr(": %1 (%2:%3, %4)").arg(msg).arg(context.file).arg(context.line).arg(context.function),Color,LEVEL_NORMAL);
}


int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput); // Install the handler
    QCoreApplication::setOrganizationName("NuTyX");
    QCoreApplication::setOrganizationDomain("nutyx.org");
    QCoreApplication::setApplicationName("QtCards");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
