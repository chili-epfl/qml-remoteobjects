/*
 * Copyright (C) 2018 EPFL
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
 * @file RemoteObjectReplica.h
 * @brief QML wrapper header for QRemoteObjectDynamicReplica
 * @author Ayberk Özgür
 * @date 2018-08-06
 */

#ifndef REMOTEOBJECTREPLICA_H
#define REMOTEOBJECTREPLICA_H

#include <QQuickItem>
#include <QQmlPropertyMap>
#include <QRemoteObjectDynamicReplica>

namespace QMLRemoteObjects {

/**
 * @brief QML wrapper for QRemoteObjectDynamicReplica
 */
class RemoteObjectReplica : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
    /* *INDENT-ON* */

    /** @brief Internal replica's state, one of QRemoteObjectReplica::State */
    Q_PROPERTY(int replicaState READ getReplicaState NOTIFY replicaStateChanged)

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new RemoteObjectReplica with the given QML parent
     *
     * @param parent The QML parent
     */
    RemoteObjectReplica(QQuickItem* parent = 0);

    /**
     * @brief Destroys this RemoteObjectReplica
     */
    ~RemoteObjectReplica();

    /**
     * @brief Gets the state of the replica
     *
     * @return Replica state
     */
    int getReplicaState();

    /** @endcond */

signals:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Emitted when the replica state
     */
    void replicaStateChanged();

    /** @endcond */

    /**
     * @brief Emitted when the replica is initialized, i.e API is synchronized with the source object
     */
    void initialized();

public slots:

    /**
     * @brief Sets the internal dynamic replica, can only be done once!
     *
     * @param replica Internal dynamic replica
     */
    void setReplica(QRemoteObjectDynamicReplica* replica);

private slots:

    void enumerateAll();

private:

    QRemoteObjectDynamicReplica* replica = nullptr; ///< Internal replica

};

}

Q_DECLARE_METATYPE(QMLRemoteObjects::RemoteObjectReplica*)

#endif /* REMOTEOBJECTREPLICA_H */
