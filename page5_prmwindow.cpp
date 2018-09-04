#include "page5_prmwindow.h"
#include "ui_page5_prmwindow.h"

#include <QtDebug>

page5_PRMWindow::page5_PRMWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page5_PRMWindow)
{
    ui->setupUi(this);
}

page5_PRMWindow::~page5_PRMWindow()
{
    delete ui;
}

void page5_PRMWindow::slot_getMeasureTok(QVector<QString> list)
{


    if(this->windowTitle() == "ПРМ № 1")
    {
        ui->label_I->setText( QString::number(list[0].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 2")
    {
        ui->label_I->setText( QString::number(list[1].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 3")
    {
        ui->label_I->setText( QString::number(list[2].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 4")
    {
        ui->label_I->setText( QString::number(list[3].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 5")
    {
        ui->label_I->setText( QString::number(list[0].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 6")
    {
        ui->label_I->setText( QString::number(list[1].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 7")
    {
        ui->label_I->setText( QString::number(list[2].split("\n").first().toDouble(),NULL,3) + " A");
    }

    if(this->windowTitle() == "ПРМ № 8")
    {
        ui->label_I->setText( QString::number(list[3].split("\n").first().toDouble(),NULL,3) + " A");
    }
}

void page5_PRMWindow::slot_getMeasureVolt(QVector<QString> list)
{
    if(this->windowTitle() == "ПРМ № 1")
    {
        ui->label_V->setText(QString::number(list[0].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[0].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 2")
    {
        ui->label_V->setText(QString::number(list[1].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[1].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 3")
    {
        ui->label_V->setText(QString::number(list[2].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[2].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 4")
    {
        ui->label_V->setText(QString::number(list[3].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[3].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 5")
    {
        ui->label_V->setText(QString::number(list[0].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[0].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 6")
    {
        ui->label_V->setText(QString::number(list[1].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[1].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 7")
    {
        ui->label_V->setText(QString::number(list[2].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[2].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }

    if(this->windowTitle() == "ПРМ № 8")
    {
        ui->label_V->setText(QString::number(list[3].split("\n").first().toDouble(),NULL,3) + " B");

        ui->label_P->setText(QString::number(list[3].split("\n").first().toDouble()*ui->label_I->text().split(' ').first().toDouble(),NULL,3) + " Вт");
    }
}

void page5_PRMWindow::slot_getUpdateTableSP(QStringList listSP,QStringList listSP_Amplitude, QStringList listSP_Name)
{


    for(int i=0; i < listSP.count();i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(listSP_Name[i]);

        ui->tableWidget->setItem(i,0,item);

        QTableWidgetItem *item1 = new QTableWidgetItem(listSP[i]);

        ui->tableWidget->setItem(i,1,item1);


        QTableWidgetItem *item2 = new QTableWidgetItem(listSP_Amplitude[i]);

        ui->tableWidget->setItem(i,2,item2);

        ui->tableWidget->item(i,0)->setBackground(QBrush("#FFFFFF"));
        ui->tableWidget->item(i,1)->setBackground(QBrush("#FFFFFF"));
        ui->tableWidget->item(i,2)->setBackground(QBrush("#FFFFFF"));


        if(listSP[i].toInt() >7)
        {
            ui->tableWidget->item(i,0)->setBackground(QBrush("#FF0000"));
            ui->tableWidget->item(i,1)->setBackground(QBrush("#FF0000"));
            ui->tableWidget->item(i,2)->setBackground(QBrush("#FF0000"));

            qDebug () << "ERROR 10 MGz";

           // emit Error_10Gh();
        }


        if(listSP[i].toInt() ==7)
        {
            ui->tableWidget->item(i,0)->setBackground(QBrush("#99FF99"));
            ui->tableWidget->item(i,1)->setBackground(QBrush("#99FF99"));
            ui->tableWidget->item(i,2)->setBackground(QBrush("#99FF99"));
        }

        if(listSP[i].toInt() == 6)
        {
            ui->tableWidget->item(i,0)->setBackground(QBrush("#FFA500"));
            ui->tableWidget->item(i,1)->setBackground(QBrush("#FFA500"));
            ui->tableWidget->item(i,2)->setBackground(QBrush("#FFA500"));
        }

        if(listSP[i].toInt() == 5)
        {
            ui->tableWidget->item(i,0)->setBackground(QBrush("#FFF000"));
            ui->tableWidget->item(i,1)->setBackground(QBrush("#FFF000"));
            ui->tableWidget->item(i,2)->setBackground(QBrush("#FFF000"));
        }

    }



}

void page5_PRMWindow::slot_countSpytnik_R(int R)
{
    ui->label_GenGLONASS->setText(QString::number(R));
}

void page5_PRMWindow::slot_countSpytnik_G(int G)
{
   ui->label_GenGPS->setText(QString::number(G));

   ui->label_GenSp->setText(QString::number(ui->label_GenGLONASS->text().toInt()+G));
}

void page5_PRMWindow::slot_countFindSpytnik_R(QString R)
{
    ui->label_GLONASSFind->setText(R);
}

void page5_PRMWindow::slot_countFindSpytnik_G(QString G)
{
    ui->label_GPSFind->setText(G);

    ui->label_sumFaind->setText(QString::number(ui->label_GLONASSFind->text().toInt()+G.toInt()));
}

void page5_PRMWindow::slot_updateTikTimer(QString data)
{
    ui->label_Timer->setText(data);
}

void page5_PRMWindow::slot_clearWindow()
{
    for(int i=0; i < 24;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(" ");

        ui->tableWidget->setItem(i,0,item);

        QTableWidgetItem *item1 = new QTableWidgetItem(" ");

        ui->tableWidget->setItem(i,1,item1);


        QTableWidgetItem *item2 = new QTableWidgetItem(" ");

        ui->tableWidget->setItem(i,2,item2);

        ui->tableWidget->item(i,0)->setBackground(QBrush("#FFFFFF"));
        ui->tableWidget->item(i,1)->setBackground(QBrush("#FFFFFF"));
        ui->tableWidget->item(i,2)->setBackground(QBrush("#FFFFFF"));
    }

    ui->label_V->setText("- B");
    ui->label_P->setText("- Вт");
    ui->label_I->setText("- A");

    ui->label_GenSp->setText("NaN");
    ui->label_GenGPS->setText("-");
    ui->label_GenGLONASS->setText("-");

    ui->label_sumFaind->setText("NaN");
    ui->label_GLONASSFind->setText("-");
    ui->label_GPSFind->setText("-");

    ui->label_Timer->setText("Ждем запуска приемника");


}

void page5_PRMWindow::on_pushButton_close_clicked()
{
    emit closeWindowNP();
}
