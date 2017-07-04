import QtQuick 2.7
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

WizardPage {
    property string directory

    title: "Finished"
    description: "Plugin succesfully created!"
    goBackVisible: false
    goNextVisible: false
    finishVisible: true
    openPluginDirectoryVisible: true

    Label {
        anchors.fill: parent
        textFormat: "RichText"
        text: '
<html>
    <head>
        <body>
            <p>Your plugin has been created to: <b>' + directory + '</b></p>
            <p>Your plugin should now appear in the list of available services, just select it and start working in it!</p>
            <p><span style=" font-style:italic;">Your code will be reloaded automatically whenever you save it using your preferred editor...</span></p>
        </body>
    </head>
</html>'
    }
}
