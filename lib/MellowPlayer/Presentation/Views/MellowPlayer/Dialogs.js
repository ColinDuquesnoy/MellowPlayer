function open(component, parent, properties) {
    // load component
    var component = Qt.createComponent(Qt.resolvedUrl("Dialogs/" + component));
    if (component.status !== Component.Ready) {
        console.log("Error loading dialog component:", component.errorString());
        return;
    }

    // create object
    var dialog = component.createObject(parent, properties);
    if (dialog == null) {
        console.log("Error creating dialog object");
        return;
    }

    dialog.x = parent.width / 2 - dialog.width / 2
    dialog.y = parent.height / 2 - dialog.height / 2
    dialog.open();
}
