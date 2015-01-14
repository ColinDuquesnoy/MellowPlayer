#ifndef DLGSELECTSERVICE_H
#define DLGSELECTSERVICE_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
    class DialogSelectServices;
}

class DlgSelectServices:
        public QDialog
{
    Q_OBJECT

public:
    explicit DlgSelectServices(QWidget* parent=NULL);
    ~DlgSelectServices();

    static QString selectService(QWidget* parent);

private slots:
    void onCurrentItemChanged(QListWidgetItem* item);

private:
    Ui::DialogSelectServices* ui;

};

#endif // DLGSELECTSERVICE_H
