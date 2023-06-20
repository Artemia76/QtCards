#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "cardshelper.h"
#include "cardsadaptor.h"

CardsHelper::CardsHelper(int &argc, char **argv) : QtCoreApplication(argc, argv)
{
    (void) new CardsAdaptor(this);
    // Register the DBus service
    if (!QDBusConnection::systemBus().registerService("org.qt.policykit.qtcards"))
    {
        QTextStream ErrStream(stderr);
        ErrStream << QDBusConnection::systemBus().lastError().message();

        QTimer::singleShot(0, this, SLOT(quit()));
        return;
    }

    if (!QDBusConnection::systemBus().registerObject("/", this))
    {
        QTextStream ErrStream(stderr);
        ErrStream << "unable to register service interface to dbus";

        QTimer::singleShot(0, this, SLOT(quit()));
        return;
    }
    // Normally you will set a timeout so your application can
    // free some resources of the poor client machine ;)
    QTimer::singleShot(MINUTE, this, SLOT(quit()));
}

CardsHelper::~CardsHelper()
{
}

int CardsHelper::write(QString &strErrMsg)
{
    // message().service() is the service name of the caller
    // We can check if the caller is authorized to the following action
    PolkitQt1::Authority::Result result;
    PolkitQt1::SystemBusNameSubject subject(message().service());

    result = PolkitQt1::Authority::instance()->checkAuthorizationSync("org.qt.policykit.qtcards.write", subject , PolkitQt1::Authority::AllowUserInteraction);
    if (result == PolkitQt1::Authority::Yes)
    {   // Caller is authorized so we can perform the action
        return writeValue(strErrMsg);
    }
    else
    {   // Caller is not authorized so the action can't be performed
        return 1;
    }
}

int CardsHelper::writeValue(QString &strErrMsg)
{
    // This action must be authorized first. It will set the implicit
    // authorization for the Shout action by editing the .policy file
    try
    {
        QFileInfo FileInfo("/opt/sample.txt");

        QFile File("/opt/sample.txt");
        if(!File.open(QIODevice::WriteOnly))
        {
            strErrMsg = "File(" + FileInfo.fileName() + ") Open Error: " + File.errorString();
            return -1;
        }

        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
        QTextStream OutStream(&File);
        OutStream << current_date;

        File.close();
    }
    catch (QException &err)
    {
        strErrMsg = err.what();
    }

    return 0;
}
