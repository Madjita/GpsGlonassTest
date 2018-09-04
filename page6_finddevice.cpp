#include "page6_finddevice.h"
#include "ui_page6_finddevice.h"

Page6_FindDevice::Page6_FindDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page6_FindDevice),
    index(1)
{
    ui->setupUi(this);
}

Page6_FindDevice::~Page6_FindDevice()
{
    delete ui;
}

void Page6_FindDevice::on_pushButton_clicked()
{
    emit FindDeviceWork();
}

void Page6_FindDevice::FindDeviceListChenge(QList<QObject *> list)
{
    ui->tableWidget->setRowCount(list.count());

    for(int i=0; i < list.count();i++)
    {
        FindDeviceItem *it = (FindDeviceItem*)list.value(i);

        QTableWidgetItem *newItem = new QTableWidgetItem(it->ip());
             ui->tableWidget->setItem(i, 0, newItem);

        QTableWidgetItem *newItem2 = new QTableWidgetItem(it->content());
             ui->tableWidget->setItem(i, 1, newItem2);
    }


}

void Page6_FindDevice::on_tableWidget_cellDoubleClicked(int row, int column)
{

    emit IP(ui->tableWidget->item(row,0)->text(),index);

}
