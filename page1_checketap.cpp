#include "page1_checketap.h"
#include "ui_page1_checketap.h"

Page1_checketap::Page1_checketap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page1_checketap)
{
    ui->setupUi(this);

}

Page1_checketap::~Page1_checketap()
{
    delete ui;
}

void Page1_checketap::on_pushButton_Work_clicked()
{
    qDebug () << "Go Work";

    emit OpenDeviceConnect();
}

QString Page1_checketap::getName()
{
    return ui->lineEdit_FIO->text();
}

QString Page1_checketap::getMode()
{

    if(ui->radioButton_R->isChecked())
    {
        return ui->radioButton_R->text();
    }

    if(ui->radioButton_PSI->isChecked())
    {
        return ui->radioButton_PSI->text();
    }

    if(ui->radioButton_T->isChecked())
    {
        return ui->radioButton_T->text();
    }

    if(ui->radioButton_WorkTime->isChecked())
    {
        return ui->radioButton_WorkTime->text();
    }



}
