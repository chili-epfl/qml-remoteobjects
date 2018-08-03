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

namespace QMLRemoteObjects {

RemoteObjectHost::RemoteObjectHost(QQuickItem* parent) :
    QQuickItem(parent)
{}

RemoteObjectHost::~RemoteObjectHost(){
    if(remoteObjectHost)
        remoteObjectHost->deleteLater();
}

void RemoteObjectHost::setupHost(){
    deleteHost();
    remoteObjectHost = new QRemoteObjectHost(QUrl("tcp://" + host + ":" + QString::number(port)), this);
}

void RemoteObjectHost::deleteHost(){
    if(remoteObjectHost)
        delete remoteObjectHost;
    remoteObjectHost = nullptr;
}

void RemoteObjectHost::setListening(bool enable){
    if(enable && !listen){
        setupHost();
        listen = enable;
        emit listeningChanged();
    }
    else if(!enable && listen){
        deleteHost();
        listen = enable;
        emit listeningChanged();
    }
}

void RemoteObjectHost::setHost(QString host){
    if(host != this->host){
        this->host = host;
        if(listen)
            setupHost();
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
        if(listen)
            setupHost();
        emit portChanged();
    }
}

bool RemoteObjectHost::enableRemoting(QObject* object, QString const& name){
    if(remoteObjectHost)
        return remoteObjectHost->enableRemoting(object, name);
    else{
        qCritical() << "bool RemoteObjectHost::enableRemoting(): Must start listening first, doing nothing.";
        return false;
    }
}

bool RemoteObjectHost::disableRemoting(QObject* object){
    if(remoteObjectHost)
        return remoteObjectHost->disableRemoting(object);
    else{
        qCritical() << "bool RemoteObjectHost::disableRemoting(): Must start listening first, doing nothing.";
        return false;
    }
}

}
