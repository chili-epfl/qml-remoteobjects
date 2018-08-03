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
 * @file RemoteObjectHost.h
 * @brief QML wrapper header for QRemoteObjectHost
 * @author Ayberk Özgür
 * @date 2018-08-02
 */

#ifndef REMOTEOBJECTHOST_H
#define REMOTEOBJECTHOST_H

#include <QQuickItem>
#include <QRemoteObjectHost>

namespace QMLRemoteObjects {

/**
 * @brief QML wrapper for QRemoteObjectHost
 */
class RemoteObjectHost : public QQuickItem {
    /* *INDENT-OFF* */
    Q_OBJECT
        /* *INDENT-ON* */

    /** @brief Address to listen on, default "0.0.0.0" i.e any address */
    Q_PROPERTY(QString host READ getHost WRITE setHost NOTIFY hostChanged)

    /** @brief Port to connect to, or port of the already open remote connection , must be in [0,65535], default 12345 */
    Q_PROPERTY(int port READ getPort WRITE setPort NOTIFY portChanged)

public:

    /** @cond DO_NOT_DOCUMENT */

    /**
     * @brief Creates a new RemoteObjectHost with the given QML parent
     *
     * @param parent The QML parent
     */
    RemoteObjectHost(QQuickItem* parent = 0);

    /**
     * @brief Destroys this TcpSocket
     */
    ~RemoteObjectHost();

    /**
     * @brief Gets the current host name
     *
     * @return Current host name, e.g "127.0.0.1"
     */
    QString getHost() const { return host; }

    /**
     * @brief Sets the host name
     *
     * @param host The new host name, e.g "127.0.0.1"
     */
    void setHost(QString host);

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
     * @brief Emitted when the host name changes
     */
    void hostChanged();

    /**
     * @brief Emitted whe the port changes
     */
    void portChanged();

    /** @endcond */

public slots:

    /**
     * @brief Starts providing remote access to the object so that clients connected to this host can obtain its replica
     *
     * @param  object Object to share
     * @param  name   Lookup name of the object at the client side, QCLASSINFO_REMOTEOBJECT_TYPE will be used if not given
     * @return        Whether remoting successfully enabled
     */
    bool enableRemoting(QObject* object, QString const& name = QString());

    /**
     * @brief Stops providing remote access to the object
     *
     * @param  object Object to stop sharing
     * @return        Whether remoting successfully stopped
     */
    bool disableRemoting(QObject* remoteObject);

private:

    /**
     * @brief Sets the internal QRemoteObjectHost's host and port to the current ones
     */
    void setHostAndPort();

    QRemoteObjectHost remoteObjectHost; ///< The low level socket
    QString host;                       ///< Host address
    int port;                           ///< Connection port

};

}

#endif /* REMOTEOBJECTHOST_H */
