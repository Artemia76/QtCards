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
** call_once.h is part of QtCards project
**
** This template provide safe thread calls for singletons
****************************************************************************/

#ifndef CALL_ONCE_H
#define CALL_ONCE_H

#include <QtGlobal>
#include <QAtomicInt>
#include <QMutex>
#include <QWaitCondition>
#include <QThreadStorage>
#include <QThread>

namespace CallOnce {
    enum ECallOnce
    {
        CO_Request,
        CO_InProgress,
        CO_Finished
    };

    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag)
}

template <class Function>
inline static void qCallOnce(Function func, QBasicAtomicInt& flag)
{
    using namespace CallOnce;

#if QT_VERSION < 0x050000
    int protectFlag = flag.fetchAndStoreAcquire(flag);
#elif QT_VERSION >= 0x050000
    int protectFlag = flag.fetchAndStoreAcquire(flag.loadRelaxed());
#endif

    if (protectFlag == CO_Finished)
        return;
    if (protectFlag == CO_Request && flag.testAndSetRelaxed(protectFlag,
                                                           CO_InProgress)) {
        func();
        flag.fetchAndStoreRelease(CO_Finished);
    }
    else {
        do {
            QThread::yieldCurrentThread();
        }
        while (!flag.testAndSetAcquire(CO_Finished, CO_Finished));
    }
}

template <class Function>
inline static void qCallOncePerThread(Function func)
{
    using namespace CallOnce;
    if (!CallOnce::once_flag()->hasLocalData()) {
        CallOnce::once_flag()->setLocalData(new QAtomicInt(CO_Request));
        qCallOnce(func, *CallOnce::once_flag()->localData());
    }
}

#endif // CALL_ONCE_H
