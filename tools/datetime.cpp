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
** datetime.cpp is part of QtCards project
**
** These types and function provide time convertion between timestamp format
** and std::chrono tools
****************************************************************************/

#include "tools/datetime.h"

///
/// \brief Now
/// \return
///
datetime Now()
{
    return time_point_cast<milliseconds>(system_clock::now());
}

///
/// \brief fromTimeStamp
/// \param pTS
/// \return
///
datetime fromTimeStamp(uint64_t pTS)
{
    auto epoch = time_point<system_clock>();
    auto since_epoch = milliseconds(pTS);
    return time_point_cast<std::chrono::milliseconds>(epoch + since_epoch);
}

///
/// \brief toTimeStamp
/// \param pTime
/// \return
///
uint64_t toTimeStamp(datetime pTime)
{
    auto epoch = time_point<system_clock>();
    return static_cast<uint64_t>(duration_cast<milliseconds>(pTime-epoch).count());
}
