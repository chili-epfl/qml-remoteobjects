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
 * @file RemoteObjectClient.cpp
 * @brief QML wrapper source for QRemoteObjectNode
 * @author Ayberk Özgür
 * @date 2018-08-02
 */

#include "RemoteObjectClient.h"

namespace QMLRemoteObjects {

RemoteObjectClient::RemoteObjectClient(QQuickItem* parent) : QQuickItem(parent)
{
    connect(&remoteObjectNode, SIGNAL(error(QRemoteObjectNode::ErrorCode)), this, SLOT(processError(QRemoteObjectNode::ErrorCode)));
    remoteObjectNode.setHeartbeatInterval(heartbeatInterval);
}

RemoteObjectClient::~RemoteObjectClient(){
}

void RemoteObjectClient::processError(QRemoteObjectNode::ErrorCode errorCode){
    //TODO: DOESN'T WORK YET AS OF QT 5.11.0??
    emit error(QMetaEnum::fromType<QRemoteObjectNode::ErrorCode>().valueToKey(errorCode));
}

void RemoteObjectClient::setPeer(QString peer){
    if(peer != this->peer){
        this->peer = peer;
        emit peerChanged();
    }
}

void RemoteObjectClient::setPort(int port){
    if(port < 0){
        qWarning() << "RemoteObjectClient::setPort(): Port given was negative, setting to 0.";
        port = 0;
    }
    else if(port > 0xFFFF){
        qWarning() << "RemoteObjectClient::setPort(): Port given was larger than 65535, setting to 65535.";
        port = 0xFFFF;
    }

    if(port != this->port){
        this->port = port;
        emit portChanged();
    }
}

void RemoteObjectClient::setHeartbeatInterval(int heartbeatInterval){
    if(heartbeatInterval < 0){
        qWarning() << "RemoteObjectClient::setHeartbeatInterval(): Heartbeat interval given was negative, setting to 0 to disable.";
        heartbeatInterval = 0;
    }

    if(heartbeatInterval != this->heartbeatInterval){
        this->heartbeatInterval = heartbeatInterval;
        emit heartbeatIntervalChanged();
    }
}

bool RemoteObjectClient::connectToNode(){
    QString url = "tcp://" + peer + ":" + QString::number(port);
    qDebug() << "RemoteObjectClient::connectToNode(): Connecting to node at: " << url;
    return remoteObjectNode.connectToNode(QUrl(url));
}

QMLRemoteObjects::RemoteObjectReplica* RemoteObjectClient::acquire(QString name){
    QRemoteObjectDynamicReplica* dyreplica = remoteObjectNode.acquireDynamic(name);
    RemoteObjectReplica* replica = new RemoteObjectReplica();
    replica->setReplica(dyreplica);
    return replica;
}

/*void RemoteObjectClient::setText(){
    const QMetaObject* metaObject = replica->metaObject();
    QMetaProperty textProp = metaObject->property(metaObject->indexOfProperty("text"));
    textProp.write(replica, "asdasdasd");
}*/

}
