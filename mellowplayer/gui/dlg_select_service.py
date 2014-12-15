from mellowplayer.qt import QtCore, QtGui, QtWidgets
from .forms import dlg_select_service_ui


HTML = '''
<h1>%(sv_name)s</h1>
<h2>Description</h2>
%(sv_desc)s
<h2>Service information</h2>
<p><strong>Maintainer: </strong><a href=%(maintainer_url)s>%(maintainer_name)s
</a></p>
<p><strong>Version: </strong>%(sv_version)s</p>
'''


class DlgSelectService(QtWidgets.QDialog):
    def __init__(self, parent):
        super().__init__(parent)
        self.ui = dlg_select_service_ui.Ui_Dialog()
        self.ui.setupUi(self)
        self.ui.buttonBox.button(self.ui.buttonBox.Ok).setText('Use service')
        self.setWindowTitle('Select service - Mellow Player')
        services = parent.services.plugins.values()
        for sv in sorted(services, key=lambda x: x.metadata.name):
            meta = sv.metadata
            item = QtWidgets.QListWidgetItem(meta.name, self.ui.listWidget)
            if meta.icon:
                item.setIcon(QtGui.QIcon(meta.icon))
            item.service = sv
            self.ui.listWidget.addItem(item)
        self.ui.listWidget.setCurrentRow(0)
        self.ui.pushButton.hide()  # not use at the moment

    @QtCore.pyqtSlot(QtWidgets.QListWidgetItem, QtWidgets.QListWidgetItem)
    def on_listWidget_currentItemChanged(self, item, _):
        sv = item.service
        desc = HTML % {
            'sv_name': sv.metadata.name,
            'sv_desc': sv.description,
            'maintainer_url': sv.metadata.maintainer_link,
            'maintainer_name': sv.metadata.maintainer_name,
            'sv_version': sv.metadata.version_str
        }
        self.ui.textBrowser.setText(desc)

    @classmethod
    def select_service(cls, parent):
        dlg = cls(parent)
        if dlg.exec_() == dlg.Accepted:
            return dlg.ui.listWidget.currentItem().service.metadata.name
        return None
