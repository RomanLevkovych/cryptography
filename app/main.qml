import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Caesar Cipher")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action { text: qsTr("Create") }
            Action { text: qsTr("Open") }
            Action { text: qsTr("Save") }
            Action { text: qsTr("Delete") }
        }

        Menu {
            title: qsTr("About")
            Action {
                text: qsTr("About App")
                onTriggered: {
                    aboutApp.open()
                }
            }
            Action {
                text: qsTr("About Developer")
                onTriggered: {
                    aboutDeveloper.open()
                }
            }
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 5

        ColumnLayout {
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: (parent.width - 2*parent.spacing) / 3

            Text {
                id: toEncryptTextCst
                text: "To encrypt"
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true

                border {
                    color: "black"
                    width: 1
                }

                Flickable {
                    anchors.fill: parent

                    TextArea.flickable: TextArea {
                        id: textToEncrypt
                        placeholderText: "Text to encrypt is here."
                        wrapMode: TextArea.Wrap
                        Layout.fillHeight: true
                    }
                    ScrollBar.vertical: ScrollBar { }
                }
            }
        }

        ColumnLayout {
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: (parent.width - 2*parent.spacing) / 3

            Text {
                id: encryptedTextCst
                text: "Encrypted"
            }

            Rectangle {
                Layout.fillHeight: true
                Layout.fillWidth: true

                border {
                    color: "black"
                    width: 1
                }

                Flickable {
                    anchors.fill: parent

                    TextArea.flickable: TextArea {
                        id: encryptedText
                        placeholderText: "Encrypted text is here."
                        wrapMode: TextArea.Wrap
                        Layout.fillHeight: true
                    }
                    ScrollBar.vertical: ScrollBar { }
                }
            }
        }

        ColumnLayout {
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: (parent.width - 2*parent.spacing) / 3
            TabBar {
                id: cryptMenu
                Layout.fillWidth: true
                TabButton {
                    text: qsTr("Encrypt")
                }

                TabButton {
                    text: qsTr("Decrypt")
                }
            }

            StackLayout {
                currentIndex: cryptMenu.currentIndex
                Item {
                    id: encrypt
                    Text {
                        text: qsTr("encrypt")
                    }
                }
                Item {
                    id: decrypt
                    Text {
                        text: qsTr("dencrypt")
                    }
                }
            }
        }
    }

    MessageDialog {
        id: aboutApp
        title: qsTr("About the app")
        text: qsTr("App was developed by Roman Levkovych, AMi-33 for Cryptography course.")
    }

    MessageDialog {
        id: aboutDeveloper
        title: qsTr("About the developer")
        text: qsTr("Caesar cipher encryption/decryption.")
    }
}
