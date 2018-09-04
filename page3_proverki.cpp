#include "page3_proverki.h"
#include "ui_page3_proverki.h"

Page3_Proverki::Page3_Proverki(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page3_Proverki)
{
    ui->setupUi(this);
}

Page3_Proverki::~Page3_Proverki()
{
    delete ui;
}

void Page3_Proverki::on_pushButton_1_clicked()
{
    emit OpenStartEtapCamber(1);
}

void Page3_Proverki::on_pushButton_2_clicked()
{
    emit OpenStartEtapCamber(2);
}

void Page3_Proverki::on_pushButton_3_clicked()
{
    emit OpenStartEtapCamber(3);
}

void Page3_Proverki::on_pushButton_4_clicked()
{
    emit OpenStartEtapCamber(4);
}

void Page3_Proverki::on_pushButton_5_clicked()
{
    emit OpenStartEtapCamber(5);
}

void Page3_Proverki::on_pushButton_6_clicked()
{
    emit OpenStartEtapCamber(6);
}

void Page3_Proverki::on_pushButton_7_clicked()
{
    emit OpenStartEtapCamber(7);
}

void Page3_Proverki::on_pushButton_8_clicked()
{
    emit OpenStartEtapCamber(8);
}

void Page3_Proverki::on_pushButton_9_clicked()
{
    emit OpenStartEtapCamber(9);
}

void Page3_Proverki::on_pushButton_10_clicked()
{
    emit OpenStartEtapCamber(10);
}
