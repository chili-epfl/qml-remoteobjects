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
 * @file RemoteObjectClient.h
 * @brief QML wrapper header for client functionality of QRemoteObjectNode
 * @author Ayberk Özgür
 * @date 2018-08-03
 */

#ifndef REMOTEOBJECTCLIENT_H
#define REMOTEOBJECTCLIENT_H

#include <QQuickItem>
#include <QRemoteObjectNode>

namespace QMLRemoteObjects {

/**
 * @brief QML wrapper for client functionality of QRemoteObjectNode
 */
class RemoteObjectClient : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
        /* *INDENT-ON* */

    /** @brief Address to listen on, default "127.0.0.1" i.e localhost */
    Q_PROPERTY(QString peer READ getPeer WRITE setPeer NOTIFY peerChanged)

    /** @brief Port to connect to, or port of the already open remote connection, must be in [0,65535], default 12345 */
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new RemoteObjectClient with the given QML parent
     *
     * @param parent The QML parent
     */
    RemoteObjectClient(QQuickItem* parent = 0);

    /**
     * @brief Destroys this RemoteObjectClient
     */
    ~RemoteObjectClient();

    /**
     * @brief Gets the current peer address
     *
     * @return Current peer address, e.g "127.0.0.1"
     */
    QString getPeer() const { return peer; }

    /**
     * @brief Sets the peer address
     *
     * @param peer The new peer address, e.g "127.0.0.1"
     */
    void setPeer(QString peer);

    /**
     * @brief Gets the current port
     *
     * @return Current port
     */
    int getPort() const { return port; }

    /**
     * @brief Sets the port
     *
     * @param port The new port, must be in [0,65535]
     */
    void setPort(int port);

    /** @endcond */

signals:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Emitted when the peer address changes
     */
    void peerChanged();

    /**
     * @brief Emitted whe the port changes
     */
    void portChanged();

    /** @endcond */

    /**
     * @brief Emitted when an error occurs
     *
     * @param errorCode One of QRemoteObjectNode::ErrorCode
     */
    void error(QString errorCode);

public slots:

    /**
     * @brief Initiates connection to the peer
     *
     * @return Whether successfully initiated connection
     */
    bool connectToNode();







    void getObj();
    void setText();

private slots:

    /**
     * @brief Redirects and emits error
     *
     * @param errorCode Original error code
     */
    void processError(QRemoteObjectNode::ErrorCode errorCode);

private:

    QRemoteObjectNode remoteObjectNode;            ///< The low level client
    QString peer = "127.0.0.1";                    ///< Peer address
    int port = 12345;                              ///< Connection port













    QRemoteObjectDynamicReplica* replica;

};

}

#endif /* REMOTEOBJECTCLIENT_H */
