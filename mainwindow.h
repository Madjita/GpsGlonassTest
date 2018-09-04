#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtQuick>
#include <QDebug>

#include <QMdiSubWindow>

#include <page1_checketap.h>
#include <page2_connectdevice.h>
#include <page3_proverki.h>
#include <page4_startetapcamber.h>
#include <page5_prmwindow.h>
#include <page6_finddevice.h>

#include <clockcircle.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Page1_checketap *page1_checketap;
    Page2_ConnectDevice *page2_ConnectDevice;
    Page3_Proverki * page3_proverki;
    Page4_StartEtapCamber * page4_StartEtapCamber;
    page5_PRMWindow* page5_prmWindow_NP1;
    page5_PRMWindow* page5_prmWindow_NP2;
    page5_PRMWindow* page5_prmWindow_NP3;
    page5_PRMWindow* page5_prmWindow_NP4;
    page5_PRMWindow* page5_prmWindow_NP5;
    page5_PRMWindow* page5_prmWindow_NP6;
    page5_PRMWindow* page5_prmWindow_NP7;
    page5_PRMWindow* page5_prmWindow_NP8;

    Page6_FindDevice* page6_FindDevice;

    QQuickView * viewProverka;
    QWidget *containerProverka;

    QQuickView * viewTiemer;
    QWidget *containerTiemer;

    QQuickView * viewPDF;
    QWidget *containerPDF;

signals:
    void setNY();
    void setCold();
    void setHord();

    void startAutoWork();

public slots:
    void on_actionMode_triggered();
    void on_actionFind_triggered();
    void on_actionProverki_triggered();
    void on_actionStartEtapCamber_triggered(int indexproverka);
    void on_actionFindDevice_triggered(int index);

    void startOneProverka(int,int);
    void openWindowWork();

    void openWindowWorkNP(int index);

    void initializate_proverka();

    void slot_startAutoWork();



private slots:
    void on_actionResult_triggered();

    void on_actionPDF_triggered();



private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
