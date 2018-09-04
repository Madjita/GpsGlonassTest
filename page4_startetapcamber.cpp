#include "page4_startetapcamber.h"
#include "ui_page4_startetapcamber.h"

Page4_StartEtapCamber::Page4_StartEtapCamber(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page4_StartEtapCamber)
{
    ui->setupUi(this);
}

Page4_StartEtapCamber::~Page4_StartEtapCamber()
{
    delete ui;
}

void Page4_StartEtapCamber::setIndexProverka(int index)
{
    indexProverka = index;
}

void Page4_StartEtapCamber::on_pushButton_clicked()
{
      emit Beak();
}

void Page4_StartEtapCamber::on_pushButton_2_clicked()
{





    modeCamber = 0;

    if(ui->radioButton->isChecked())
    {
        modeCamber = 1;
    }

    if(ui->radioButton_2->isChecked())
    {
        modeCamber = 3;

    }

    if(ui->radioButton_3->isChecked())
    {
        modeCamber = 5;

    }

    if(ui->radioButton_4->isChecked())
    {
        modeCamber = 2;
    }










    emit  StartProverka(indexProverka, modeCamber);
}
