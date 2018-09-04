#ifndef PAGE2_CONNECTDEVICE_H
#define PAGE2_CONNECTDEVICE_H
#pragma once
#include <QWidget>
#include <QtDebug>

#include <gsgmodel.h>
#include <n6700model.h>
#include <portmodel.h>
#include <osuilografmodel.h>
#include <tp8.h>

//////библиотека Управления камерой////////////
#include "cambermodel.h"

#include <finddevice.h>

#include <bdata.h>
#include <report.h>

#include <QQmlContext>

#include <proverkamodel.h>

namespace Ui {
class Page2_ConnectDevice;
}

class Page2_ConnectDevice : public QWidget
{
    Q_OBJECT

public:
    explicit Page2_ConnectDevice(QWidget *parent = 0);
    ~Page2_ConnectDevice();



    N6700Model* n6700_1;
    N6700Model* n6700_2;
    CamberModel* camber;
    gsgModel* gsg;
    OsuilografModel* os;
    TP8* tp;

    PortModel* port1;
    PortModel* port2;
    PortModel* port3;
    PortModel* port4;
    PortModel* port5;
    PortModel* port6;
    PortModel* port7;
    PortModel* port8;

    FindDevice* find;

    bool flag_auto;

    Proverka* proverka;
    //ProverkaModel* proverkaModel;
    BData* BD;
    Report* pdf;

    void setName(QString);
    void setMode(QString);

public slots:
    void getFindIp(QString ip,int index);

    void slot_StartProverka();
    void slot_StartProverka2();
    void slot_StartProverka3();

    void slot_startAutoWork();

signals:
    void OpenProverki();
    void OpenFindDevice(int index);

    void signals_StartProverka();
    void signals_StartProverka2();
    void signals_StartProverka3();

    void startAutoWork();

private slots:
    void on_pushButton_IS1_clicked();
    void on_pushButton_IS2_clicked();

    void slot_coonnectOK_1(bool);
    void slot_coonnectOK_2(bool);

    void slot_coonnectOK_Camber(bool);
    void slot_coonnectOK_GSG(bool);
    void slot_coonnectOK_Os(bool);
    void slot_coonnectOK_TP8(bool);

    void slot_coonnectOK_port1(bool ok);
    void slot_coonnectOK_port2(bool ok);
    void slot_coonnectOK_port3(bool ok);
    void slot_coonnectOK_port4(bool ok);
    void slot_coonnectOK_port5(bool ok);
    void slot_coonnectOK_port6(bool ok);
    void slot_coonnectOK_port7(bool ok);
    void slot_coonnectOK_port8(bool ok);



    void on_pushButton_Camber_clicked();

    void on_pushButton_Imitator_clicked();

    void on_pushButton_Os_clicked();

    void on_pushButton_TP8_clicked();

    void on_pushButton_COMNP1_clicked();

    void on_pushButton_COMNP2_clicked();

    void on_pushButton_COMNP3_clicked();

    void on_pushButton_COMNP4_clicked();

    void on_pushButton_COMNP5_clicked();

    void on_pushButton_COMNP6_clicked();

    void on_pushButton_COMNP7_clicked();

    void on_pushButton_COMNP8_clicked();

    void on_pushButton_Work_clicked();

    void on_pushButton_Result_clicked();

    void on_pushButton_IS1_Find_clicked();



    void on_pushButton_IS2_Find_clicked();

    void on_pushButton_Camber_Find_clicked();

    void on_pushButton_Imitator_Find_clicked();

    void on_pushButton_Os_Find_clicked();

    void on_pushButton_TP8_Find_clicked();

    void on_checkBox_auto_stateChanged(int arg1);




private:
    Ui::Page2_ConnectDevice *ui;
};

#endif // PAGE2_CONNECTDEVICE_H
