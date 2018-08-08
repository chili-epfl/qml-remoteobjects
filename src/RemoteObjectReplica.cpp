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
 * @file RemoteObjectReplica.cpp
 * @brief QML wrapper source for QRemoteObjectDynamicReplica
 * @author Ayberk Özgür
 * @date 2018-08-06
 */

#include "RemoteObjectReplica.h"

namespace QMLRemoteObjects {

RemoteObjectReplica::RemoteObjectReplica(QQuickItem* parent) : QQuickItem(parent)
{
}

RemoteObjectReplica::~RemoteObjectReplica(){
    if(replica)
        replica->deleteLater();
}

int RemoteObjectReplica::getReplicaState(){
    if(replica)
        return replica->state();
    else{
        qWarning() << "RemoteObjectReplica::getReplicaState(): Internal replica not set yet!";
        return QRemoteObjectReplica::Uninitialized;
    }
}

void RemoteObjectReplica::setReplica(QRemoteObjectDynamicReplica* replica){
    if(this->replica)
        qWarning() << "RemoteObjectReplica::setReplica(): Can only be called once, doing nothing!";
    else{
        this->replica = replica;

        connect(replica, SIGNAL(initialized()), this, SIGNAL(initialized()));
        connect(replica, SIGNAL(stateChanged(QRemoteObjectReplica::State, QRemoteObjectReplica::State)), this, SIGNAL(replicaStateChanged()));
        emit replicaStateChanged();

        connect(replica, SIGNAL(initialized()), this, SLOT(enumerateAll()));
    }
}

void RemoteObjectReplica::enumerateAll(){
    const QMetaObject* metaObject = replica->metaObject();

    qDebug() << "";
    qDebug() << "Enumerating " << metaObject->className() << ":";

    qDebug() << "";
    qDebug() << "********************************";
    qDebug() << "Properties:";
    for(int i=0;i<metaObject->propertyCount();i++){
        QMetaProperty prop = metaObject->property(i);
        qDebug() << prop.typeName() << " " << prop.name();
    }

    qDebug() << "";
    qDebug() << "********************************";
    qDebug() << "Methods:";
    for(int i=0;i<metaObject->methodCount();i++){
        QMetaMethod method = metaObject->method(i);
        qDebug() << method.methodType() << " - " << method.returnType() << " " << method.name() << " " << method.parameterTypes();
    }
    qDebug() << "";
}

}
