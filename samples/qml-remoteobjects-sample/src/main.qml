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
        id: objectHost

        host: hostText.text
        port: parseInt(portText.text)
        listen: listenCheckbox.checked
    }

    Column{
        GroupBox{
            title: "Host"

            Column{
                TextField{
                    id: hostText
                    text: "0.0.0.0"
                    placeholderText: "Host (e.g 0.0.0.0)"
                }
                TextField{
                    id: portText
                    text: "12345"
                    placeholderText: "Port"
                }
                CheckBox{
                    id: listenCheckbox
                    text: "Listen?"
                }
            }
        }
    }

    CelluloRobot{
        id: robot
    }
}
