import QtQuick 2.7
import QtQuick.Controls 2.2

WizardPage {
    title: "Introduction"
    description: "Please, read this page carefully!"
    goBackVisible: false
    goNextVisible: true
    finishVisible: false
    showDocVisible: true

    Label {
        anchors.fill: parent
        textFormat: "RichText"
        text: '
<html>
    <head>
        <body>
            <p>This wizard will guide you though the steps needed to create a new streaming service plugin.</p>
            </br>
            <p>A plugin is a directory which contains 4 files:</p>
            <ul style="margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;">
                <li style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                    <span style=" font-weight:600;">integration.js</span>: this file contains the code of your plugin. You just have to implement a few functions in javascript.
                </li>
                <li style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                    <span style=" font-weight:600;">style.json</span>: this file contains the style of the plugin. Customize it if you want the adaptive theme to work with your plugin.
                </li>
                <li style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                    <span style=" font-weight:600;">metadata.ini</span>: this file contains some metadata about your plugin.</li>
                <li style=" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                    <span style=" font-weight:600;">logo.svg</span>: the logo of your plugin.
                </li>
            </ul>
            <p>This wizard will create all those files for you, you\'re left with the implementation.</p>
        </body>
    </head>
</html>'
    }
}
