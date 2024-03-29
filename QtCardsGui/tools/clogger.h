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
** clogger.h is part of QtCards project
**
** This singleton provide log messaging manager
****************************************************************************/

#ifndef CLOGGER_H
#define CLOGGER_H

#include <QObject>
#include <QSettings>
#include <QColor>
#include <QRegularExpression>
#include <QMutex>

enum CL_DEBUG_LEVEL
{
    LEVEL_NONE,
    LEVEL_NORMAL,
    LEVEL_VERBOSE
};

class CLogger : public QObject
{
    Q_OBJECT

private:
                            CLogger(QObject* pParent = 0);
    static CLogger*         createInstance();
    void                    updatePattern();
    CL_DEBUG_LEVEL          m_DebugLevel;
    QSettings               m_settings;
    bool                    m_logToFile;
    QString                 m_filtreLog;
    QRegularExpression      m_rx;
    QMutex                  m_mutex;

public:
                            ~CLogger();
    const CL_DEBUG_LEVEL&   DebugLevel;
    static CLogger*         instance();
    void                    setDebugLevel (CL_DEBUG_LEVEL pLevel=LEVEL_NONE);
    void                    log (const QString& pMessage="", QColor pColor = Qt::black,CL_DEBUG_LEVEL pLevel=LEVEL_NONE);
    void                    setFilter(const QString& pFilter);
    QString                 getFilter();

signals:
    void                    fireLog (QString pMessage="", QColor pColor = Qt::black,CL_DEBUG_LEVEL pLevel=LEVEL_NONE);
};

#endif // CLOGGER_H
