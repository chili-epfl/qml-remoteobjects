import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.2

import QMLRemoteObjects 1.0

import Cellulo 1.0

ApplicationWindow {
    id: window
    visible: true
    minimumHeight: height
    minimumWidth: width


    RemoteObjectHost{
        id: host

        Component.onCompleted: enableRemoting(robot, "MyRobot")
    }

    CelluloRobot{
        id: robot
    }
}
