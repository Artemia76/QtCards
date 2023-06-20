#ifndef CARDSHELPER_H
#define CARDSHELPER_H

#include <QDBusConnection>
#include <QDBusContext>
#include <QDBusMessage>
#include <QCoreApplication>
#include <polkit-qt5-1/polkitqt1-authority.h>

class CardsHelper : public QCoreApplication, protected QDBusContext
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.qt.policykit.qtcards")

private:
    int writeValue(QString &strErrMsg);
public:
    CardsHelper(int &argc, char **argv);
    ~CardsHelper() override;

public Q_SLOTS:
    int write(QString &strErrMsg);
};

#endif // CARDSHELPER_H
