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
        port: parseInt(hostPortText.text)

        listen: listenCheckbox.checked
    }

    RemoteObjectClient{
        id: objectClient

        peer: peerText.text
        port: parseInt(clientPortText.text)

        onError: console.info(errorCode)
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
                    id: hostPortText
                    text: "12345"
                    placeholderText: "Port"
                }
                CheckBox{
                    id: listenCheckbox
                    text: "Listen?"
                }
                Button{
                    text: "enable remoting"
                    onClicked: objectHost.enableRemoting(test, "Test")
                }
                Button{
                    text: "disable remoting"
                    onClicked: objectHost.disableRemoting(test)
                }




                Button{
                    text: test.testProp
                    onClicked: test.testSignal()
                }

                QtObject{
                    id: test

                    //text: "QWEQWEQWE"

                    property string testProp: "DENEME"

                    signal testSignal()
                }
            }
        }

        GroupBox{
            title: "Client"

            Column{
                TextField{
                    id: peerText
                    text: "127.0.0.1"
                    placeholderText: "Peer (e.g 127.0.0.1)"
                }
                TextField{
                    id: clientPortText
                    text: "12345"
                    placeholderText: "Port"
                }
                Button{
                    id: connectButton
                    text: "Connect"
                    onClicked: objectClient.connectToNode()

                    property var repl: objectClient.acquire("Test")

                    Connections{
                        target: connectButton.repl

                        onInitialized: connectButton.repl.testProp = "QWEQWEQWE"
                        //testPropChanged.connect(
                        //                   function(){ console.log("testSignal emitted!!!!!!"); }
                        //                   )
                    }
                }
            }
        }
    }

    CelluloBluetooth{
        id: robot
    }
}
