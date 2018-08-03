/*
 * Copyright (C) 2016 EPFL
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see http://www.gnu.org/licenses/.
 */

/**
 * @file QMLRemoteObjectsPlugin.h
 * @brief Object that exposes the QMLRemoteObjects plugin components as QML objects
 * @author Ayberk Özgür
 * @date 2018-08-02
 */

#include "QMLRemoteObjectsPlugin.h"

#include "RemoteObjectHost.h"

namespace QMLRemoteObjects{

void QMLRemoteObjectsPlugin::registerTypes(const char* uri){
    qmlRegisterType<RemoteObjectHost>(uri, 1, 0, "RemoteObjectHost");
}

}
