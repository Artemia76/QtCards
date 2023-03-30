/****************************************************************************
**
** Copyright (C) 2023 NuTyX team.
** Contact: https://github.com/Artemia76/QtCards
**
** QtCards is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** QtCards is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** The license is as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this software. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
****************************************************************************/


/****************************************************************************
** main.cpp is part of QtCards project
**
** This is the main entry for project
****************************************************************************/

#include "gui/mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QTranslator>
#include <QString>
#include "tools/clogger.h"

///
/// \brief myMessageOutput
/// \param type
/// \param context
/// \param msg
///
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
        break;
    case QtFatalMsg:
        Prefix= QObject::tr("Fatal");
        Color = Qt::red;
        break;
    }
    log->log(Prefix + QObject::tr(": %1 (%2:%3, %4)").arg(msg).arg(context.file).arg(context.line).arg(context.function),Color,LEVEL_NORMAL);
}

///
/// \brief main
/// \param argc
/// \param argv
/// \return
///
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
