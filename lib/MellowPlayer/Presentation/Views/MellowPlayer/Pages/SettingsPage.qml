import QtQuick 2.9
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2
import QtQuick.Controls.Material 2.2

import MellowPlayer 3.0
import ".."
import "../Dialogs"
import "../SettingsTranslator.js" as Translator

Page {
    id: settingsPage

    signal closeRequested()

    header: ToolBar {
        id: toolBar

        Material.primary: _theme.primary
        Material.foreground: _theme.primaryForeground
        Material.theme: _theme.isDark(_theme.primary) ? Material.Dark : Material.Light

        RowLayout {
            anchors.fill: parent

            Item {
                Layout.fillWidth: true
            }

            ToolButton {
                id: btBack

                font { family: MaterialIcons.family; pixelSize: 24 }
                hoverEnabled: true
                text: MaterialIcons.icon_keyboard_arrow_right
                onClicked: settingsPage.closeRequested()
                Tooltip {
                    y: toolBar.implicitHeight
                    text: qsTr("Back")
                }

                Shortcut {
                    sequence: _settings.get(SettingKey.SHORTCUTS_SETTINGS)
                    onActivated: settingsPage.closeRequested()
                }
            }
        }

        Label {
            anchors.centerIn: parent
            font.pixelSize: 16
            text: settingsPageList.currentItem.category
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        Pane {
            padding: 0

            Layout.fillHeight: true
            Layout.maximumWidth: 324
            Layout.minimumWidth: 324

            Material.background: _theme.secondary
            Material.foreground: _theme.secondaryForeground
            Material.elevation: 4
            Material.theme: _theme.isDark(_theme.secondary) ? Material.Dark : Material.Light

            ColumnLayout {
                anchors.fill: parent

                Component {
                    id: settingsCategoryDelegate

                    ItemDelegate {
                        id: delegate

                        property string category: Translator.translateCategory(model.name)

                        height: 60; width: parent.width
                        hoverEnabled: true

                        RowLayout {
                            anchors.fill: parent
                            anchors.leftMargin: parent.leftPadding
                            anchors.rightMargin: parent.rightPadding
                            anchors.topMargin: parent.topPadding
                            anchors.bottomMargin: parent.bottomPadding

                            Label {
                                text: model.icon
                                font.family: MaterialIcons.family
                                font.pixelSize: 24
                            }

                            Label {
                                verticalAlignment: "AlignVCenter"
                                text: delegate.category
                                font.pixelSize: 20
                            }

                            Item { Layout.fillWidth: true; }
                        }

                        onClicked: settingsPageList.currentIndex = index
                    }
                }

                ListView {
                    id: settingsPageList

                    highlight: Rectangle {
                        color: _theme.isDark(_theme.secondary) ? "#10ffffff" : "#10000000"

                        Rectangle {
                            anchors.top: parent.top
                            anchors.left: parent.left
                            anchors.bottom: parent.bottom

                            width: 4
                            color: _theme.accent
                        }
                    }
                    highlightMoveDuration: 200
                    model: _settings.categories
                    delegate: settingsCategoryDelegate
                    interactive: false

                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }

                Button {
                    id: btRestoreDefaults

                    flat: true
                    highlighted: true
                    hoverEnabled: true
                    text: qsTr("Restore all to defaults")
                    onClicked: messageBoxConfirmRestore.open()

                    Layout.fillWidth: true
                    Layout.leftMargin: 4
                    Layout.rightMargin: 4

                    Tooltip {
                        text: qsTr('Restore all settings to their <b>default value</b>.')
                    }
                }
            }
        }

        StackLayout {
            clip: true
            currentIndex: settingsPageList.currentIndex

            Layout.fillHeight: true
            Layout.fillWidth: true

            Repeater {
                model: _settings.categories

                Loader {
                    anchors.fill: parent
                    source: model.qmlComponent
                }
            }
        }
    }

    UserScriptsDialog {
        id: userScriptsDialog

        height: 540; width: 960
        x: parent.width / 2 - width / 2; y: parent.height / 2 - height / 2
    }

    MessageBoxDialog {
        id: messageBoxConfirmRestore

        standardButtons: Dialog.Yes | Dialog.No
        message: qsTr("Are you sure you want to restore all settings to their default values?")
        title: qsTr("Confirm restore defaults")
        x: settingsPage.width / 2 - width / 2
        y: settingsPage.height / 2 - height / 2

        onAccepted: _settings.restoreDefaults()
    }

    NewPluginWizard {
        id: wizardNewPlugin

        height: 540; width: 960
        x: parent.width / 2 - width / 2; y: parent.height / 2 - height / 2
    }
}
