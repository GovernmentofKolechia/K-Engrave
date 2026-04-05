import QtQuick
import QtQuick.Layouts
import QtQuick.Controls as Controls
import org.kde.kirigami as Kirigami

Kirigami.ApplicationWindow {
    id: root
    title: "K-Engrave"
    width: 500; height: 750

    pageStack.initialPage: Kirigami.ScrollablePage {
        title: "K-Engrave | Sistem Denetimi"

        ColumnLayout {
            spacing: 20
            width: parent.width

            Repeater {
                model: backend.getCategorizedServices()

                delegate: ColumnLayout {
                    Layout.fillWidth: true
                    spacing: 8

                    Kirigami.Heading {
                        text: modelData.title
                        level: 2
                        Layout.leftMargin: 10
                        color: Kirigami.Theme.highlightColor
                    }

                    Kirigami.InlineMessage {
                        Layout.fillWidth: true
                        Layout.margins: 10
                        visible: modelData.title === "Sistem Çekirdeği"
                        type: Kirigami.MessageType.Error
                        showCloseButton: false
                        text: "Only play with those if you know what you're doing and that you acknowledge it could break your system."
                        icon.name: "dialog-warning"
                    }

                    Repeater {
                        model: modelData.services
                        delegate: Kirigami.AbstractCard {
                            Layout.fillWidth: true
                            
                            background: Rectangle {
                                color: modelData.isActive ? "#252a2e" : "#1e1e1e"
                                border.color: modelData.isActive ? Kirigami.Theme.highlightColor : "#333"
                                border.width: 1
                                radius: 2
                                
                                Rectangle {
                                    anchors.bottom: parent.bottom
                                    width: parent.width; height: 1
                                    color: "#ffffff"
                                    opacity: 0.05
                                }
                            }

                            contentItem: RowLayout {
                                spacing: 15
                                
                                Kirigami.Icon {
                                    source: {
                                        let name = modelData.prettyName.toLowerCase();
                                        if (name.includes("network") || name.includes("vpn") || name.includes("proton") || name.includes("warp")) return "network-wired";
                                        if (name.includes("blue")) return "preferences-system-bluetooth";
                                        if (name.includes("user")) return "user-identity";
                                        if (name.includes("tty") || name.includes("dbus") || name.includes("journal")) return "utilities-terminal";
                                        if (name.includes("power") || name.includes("thermal") || name.includes("battery")) return "battery-charging";
                                        return "services";
                                    }
                                    implicitWidth: 32; implicitHeight: 32
                                    color: modelData.isActive ? Kirigami.Theme.highlightColor : Kirigami.Theme.disabledTextColor
                                    opacity: modelData.isActive ? 1.0 : 0.6
                                }

                                ColumnLayout {
                                    spacing: 0
                                    Controls.Label { 
                                        text: modelData.prettyName 
                                        font.bold: true 
                                        font.pointSize: 11
                                    }
                                    Controls.Label { 
                                        text: modelData.rawName 
                                        opacity: 0.5
                                        font.pointSize: 8
                                        font.family: "Monospace"
                                    }
                                }

                                Item { Layout.fillWidth: true }

                                Controls.Switch {
                                    checked: modelData.isActive
                                    onToggled: {
                                        backend.toggleService(modelData.rawName, checked)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
