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
 * @file RemoteObjectHost.cpp
 * @brief QML wrapper source for QRemoteObjectHost
 * @author Ayberk Özgür
 * @date 2018-08-02
 */

#include "RemoteObjectHost.h"

#include <QHostAddress>

namespace QMLRemoteObjects{

RemoteObjectHost::RemoteObjectHost(QQuickItem* parent):
    QQuickItem(parent)
{
    host = "0.0.0.0";
    port = 12345;
    setHostAndPort();
}

RemoteObjectHost::~RemoteObjectHost(){

}

void RemoteObjectHost::setHostAndPort(){
    QString url("tcp://");
    url.append(host);
    url.append(":");
    url.append(port);
    remoteObjectHost.setHostUrl(QUrl(url));
}

void RemoteObjectHost::setHost(QString host){
    if(host != this->host){
        this->host = host;
        setHostAndPort();
        emit hostChanged();
    }
}

void RemoteObjectHost::setPort(int port){
    if(port < 0){
        qWarning() << "RemoteObjectHost::setPort(): Port given was negative, setting to 0.";
        port = 0;
    }
    else if(port > 0xFFFF){
        qWarning() << "RemoteObjectHost::setPort(): Port given was larger than 65535, setting to 65535.";
        port = 0xFFFF;
    }

    if(port != this->port){
        this->port = port;
        setHostAndPort();
        emit portChanged();
    }
}

bool RemoteObjectHost::enableRemoting(QObject* object, QString const& name){
    return remoteObjectHost.enableRemoting(object, name);
}

bool RemoteObjectHost::disableRemoting(QObject* object){
    return remoteObjectHost.disableRemoting(object);
}

}
