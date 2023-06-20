#include <QCoreApplication>
#include "cardshelper.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CardsHelper helper(argc, argv);

    return a.exec();
}
