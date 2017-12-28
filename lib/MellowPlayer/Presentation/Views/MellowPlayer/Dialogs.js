function open(qmlComponent, parent, properties) {
    // load component
    var component = Qt.createComponent(Qt.resolvedUrl("Dialogs/" + qmlComponent));
    if (component.status !== Component.Ready) {
        console.error("Error loading dialog component:", component.errorString());
        return;
    }

    // create object
    var dialog = component.createObject(parent, properties);
    if (dialog == null) {
        console.error("Error creating dialog object");
        return;
    }

    dialog.x = parent.width / 2 - dialog.width / 2
    dialog.y = parent.height / 2 - dialog.height / 2
    dialog.open();
}
