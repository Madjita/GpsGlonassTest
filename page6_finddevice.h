#ifndef PAGE6_FINDDEVICE_H
#define PAGE6_FINDDEVICE_H

#include <QWidget>

#include <finddeviceitem.h>

namespace Ui {
class Page6_FindDevice;
}

class Page6_FindDevice : public QWidget
{
    Q_OBJECT

public:
    explicit Page6_FindDevice(QWidget *parent = 0);
    ~Page6_FindDevice();

    void FindDeviceListChenge(QList<QObject*>);

    int index;

signals:
    void FindDeviceWork();
    void IP(QString,int);
private slots:
    void on_pushButton_clicked();



    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::Page6_FindDevice *ui;
};

#endif // PAGE6_FINDDEVICE_H
