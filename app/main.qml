import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2
import dev.rlevkovych 1.0

ApplicationWindow {
    visible: true
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Caesar Cipher")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            Action {
                text: qsTr("Open")
                onTriggered: {
                    openFileDialog.open()
                }
            }
            Action {
                text: qsTr("Save")
                onTriggered: {
                    saveFileDialog.open()
                }
            }
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
                        enabled: encryptBtn.focus
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
                        enabled: dencryptBtn.focus
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
                    id: encryptBtn
                    text: qsTr("Encrypt")
                }

                TabButton {
                    id: dencryptBtn
                    text: qsTr("Decrypt")
                }
            }

            StackLayout {
                currentIndex: cryptMenu.currentIndex
                Item {
                    id: encrypt
                    Rectangle {
                        id: asdf
                        anchors {
                            right: parent.right
                            left: parent.left
                            top: parent.top
                        }
                        implicitHeight: enrcyptKey.font.pixelSize + 3
                        border {
                            color: "black"
                            width: 1
                        }


                        TextInput {
                            id: enrcyptKey
                            anchors.fill: parent
                            validator : RegExpValidator { regExp : /-?[0-9]+/ }
                        }
                    }

                    ButtonGroup {
                        buttons: alphabetBtns1.children
                    }

                    Column {
                        id: alphabetBtns1

                        anchors {
                            top: asdf.bottom
                            topMargin: 10
                            left: parent.left
                            right: parent.right
                        }

                        RadioButton {
                            text: qsTr("Ukraininan")
                            onClicked: {
                                cipher.setAlphabet("ua")
                            }
                        }

                        RadioButton {
                            text: qsTr("Latin")
                            checked: true
                            onClicked: {
                                cipher.setAlphabet("en")
                            }
                        }
                    }

                    Button {
                        text: qsTr("encrypt")
                        anchors {
                            right: parent.right
                            left: parent.left
                            bottom: parent.bottom
                        }

                        onClicked: {
                            encryptedText.text =
                                    cipher.encrypt(textToEncrypt.text,
                                                   cipher.convertKey(parseInt(enrcyptKey.text)))
                        }
                    }
                }
                Item {
                    id: decrypt
                    Rectangle {
                        id: npt
                        anchors {
                            right: parent.right
                            left: parent.left
                            top: parent.top
                        }
                        implicitHeight: decryptKey.font.pixelSize + 3
                        border {
                            color: "black"
                            width: 1
                        }


                        TextInput {
                            id: decryptKey
                            anchors.fill: parent
                            validator : RegExpValidator { regExp : /-?[0-9]+/ }
                        }
                    }

                    ButtonGroup {
                        buttons: alphabetBtns.children
                    }

                    Column {
                        id: alphabetBtns

                        anchors {
                            top: npt.bottom
                            topMargin: 10
                            left: parent.left
                            right: parent.right
                        }

                        RadioButton {
                            text: qsTr("Ukraininan")
                            onClicked: {
                                cipher.setAlphabet("ua")
                            }
                        }

                        RadioButton {
                            id: ltn
                            text: qsTr("Latin")
                            checked: true
                            onClicked: {
                                cipher.setAlphabet("en")
                            }
                        }
                    }

                    Button {
                        text: "Brute force"
                        anchors {
                            right: parent.right
                            left: parent.left
                            bottom: dec.top
                            bottomMargin: 10
                        }

                        onClicked: {
                            textToEncrypt.text = cipher.bruteForce(encryptedText.text, ltn.checked ? "en" : "ua")
                        }
                    }

                    Button {
                        id: dec
                        text: qsTr("Decrypt")
                        anchors {
                            right: parent.right
                            left: parent.left
                            bottom: parent.bottom
                        }

                        onClicked: {
                            textToEncrypt.text =
                                    cipher.decrypt(encryptedText.text,
                                                   cipher.convertKey(parseInt(decryptKey.text)))
                        }
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
    FileDialog {
        id: openFileDialog
        onAccepted: {
            textToEncrypt.text = fs.readFile(fileUrl.toString())
        }
    }

    FileDialog {
        id: saveFileDialog
        selectExisting: false

        onAccepted: {
            fs.saveFile(fileUrl, encryptedText.text)
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
