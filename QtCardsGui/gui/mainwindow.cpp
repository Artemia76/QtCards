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
** mainwindow.cpp is part of QtCards project
**
** This template provide safe thread calls for singletons
****************************************************************************/

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QDebug>
#include<QTextCharFormat>
#include <QDBusContext>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QMessageBox>

#include<tools/version.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_log = CLogger::instance();
    connect(m_log, SIGNAL(fireLog(QString,QColor,CL_DEBUG_LEVEL)),this,SLOT(onLog(QString,QColor,CL_DEBUG_LEVEL)));
    setWindowIcon(QIcon(":/icons/gfx/flcards.xpm"));
    m_log->log(tr("Qt Version :") + QT_VERSION_STR,Qt::blue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::onLog
/// \param Texte
/// \param pColor
/// \param pLevel
///
/// Redirect Log Text flow to Plain Text Edit on main Window
///
void MainWindow::onLog (const QString& pMessage, QColor pColor, CL_DEBUG_LEVEL)
{
    QTextCharFormat fmt;
    fmt.setForeground(QBrush(pColor));
    ui->pteLogger->mergeCurrentCharFormat(fmt);
    ui->pteLogger->appendPlainText(pMessage);
}

void MainWindow::on_actionUpgrade_All_triggered()
{
    QDBusConnection bus = QDBusConnection::systemBus();
    if (!bus.isConnected())
    {
        QMessageBox(QMessageBox::Critical, tr("D-Bus error"), tr("Cannot connect to the D-Bus session bus."), QMessageBox::Close, this).exec();
    }

    // this is our Special Action that after allowed will call the helper
    QDBusMessage message;
    message = QDBusMessage::createMethodCall("org.qt.policykit.examples", "/", "org.qt.policykit.examples", QLatin1String("write"));

    // If a method in a helper file has arguments, enter the arguments.
    //QList<QVariant> ArgsToHelper;
    //ArgsToHelper << QVariant::fromValue("foo") << QVariant::fromValue("bar");
    //message.setArguments(ArgsToHelper);

    // Send a message to DBus. (Execute the helper file.)
    QDBusMessage reply = QDBusConnection::systemBus().call(message);

    // Receive the return value (including arguments) from the helper file.
    // The methods in the helper file have two arguments, so check them.
    if (reply.type() == QDBusMessage::ReplyMessage && reply.arguments().size() == 2)
    {
        // the reply can be anything, here we receive a bool
        if (reply.arguments().at(0).toInt() == 0)
        {   // If the helper file method completes successfully after successful authentication
            QMessageBox(QMessageBox::NoIcon, tr("Successed"), tr("The file was written successfully."), QMessageBox::Close, this).exec();
        }
        else if (reply.arguments().at(0).toInt() == -1)
        {   // If the helper file method fails after successful authentication
            QString strErrMsg = reply.arguments().at(1).toString();
            QMessageBox(QMessageBox::Critical, tr("Failed"), tr("Failed to write file.\n") + strErrMsg, QMessageBox::Close, this).exec();
        }
        else
        {   // If the authentication is canceled
            QMessageBox(QMessageBox::NoIcon, tr("Cancelled"), tr("Writing of the file was canceled."), QMessageBox::Close, this).exec();
        }
    }
    else if (reply.type() == QDBusMessage::MethodCallMessage)
    {
        QMessageBox(QMessageBox::Warning, tr("Time out"), tr("Message did not receive a reply (timeout by message bus)."), QMessageBox::Close, this).exec();
    }
    else if (reply.type() == QDBusMessage::ErrorMessage)
    {
        QMessageBox(QMessageBox::Critical, tr("D-Bus error"), tr("Could not send message to D-Bus."), QMessageBox::Close, this).exec();
    }

    return;
}

