#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setCentralWidget(ui->mdiArea);

    //Выдиляем память на окно входа в систему
    page1_checketap = new Page1_checketap();

    //задаем размер окна
    page1_checketap->setMinimumSize(350,200);

    ui->mdiArea->setAttribute(Qt::WA_DeleteOnClose);

    //Добавляем в область окно для отображения.
    ui->mdiArea->addSubWindow(page1_checketap);

    connect(page1_checketap, &Page1_checketap::OpenDeviceConnect,this,&MainWindow::on_actionFind_triggered);

    //Выдиляем память на окно входа в систему
    page2_ConnectDevice = new Page2_ConnectDevice(this);

    connect(page2_ConnectDevice,&Page2_ConnectDevice::startAutoWork,this,&MainWindow::slot_startAutoWork);

    connect(this,&MainWindow::startAutoWork,page2_ConnectDevice,&Page2_ConnectDevice::slot_startAutoWork);


    //задаем размер окна
    page2_ConnectDevice->setMinimumSize(800,451);

    ui->mdiArea->addSubWindow(page2_ConnectDevice);


    ui->actionMode->setChecked(true);
    ui->actionPDF->setEnabled(false);


    ui->mdiArea->subWindowList().value(0)->setFixedSize(370,250);
    ui->mdiArea->subWindowList().value(1)->setFixedSize(808,530);

    ui->mdiArea->subWindowList().value(0)->move((this->width()/2)-(ui->mdiArea->subWindowList().value(0)->width()/2),(this->height()/2)-(ui->mdiArea->subWindowList().value(0)->height()/2));
    ui->mdiArea->subWindowList().value(1)->move((this->width()/2)-(ui->mdiArea->subWindowList().value(1)->width()/2),(this->height()/2)-(ui->mdiArea->subWindowList().value(1)->height()/2));

    ui->mdiArea->subWindowList().value(0)->setWindowFlags(Qt::CustomizeWindowHint);
    ui->mdiArea->subWindowList().value(1)->setWindowFlags(Qt::CustomizeWindowHint);
    ui->mdiArea->subWindowList().value(1)->hide();

    connect(page2_ConnectDevice, &Page2_ConnectDevice::OpenProverki,this,&MainWindow::on_actionProverki_triggered);

    //Выдиляем память на окно входа в систему
    page3_proverki = new Page3_Proverki();


    //задаем размер окна
    page3_proverki->setMinimumSize(800,300);

    ui->mdiArea->addSubWindow(page3_proverki);

    ui->mdiArea->subWindowList().value(2)->setFixedSize(800,350);
    ui->mdiArea->subWindowList().value(2)->move((this->width()/2)-(ui->mdiArea->subWindowList().value(2)->width()/2),(this->height()/2)-(ui->mdiArea->subWindowList().value(2)->height()/2));
    ui->mdiArea->subWindowList().value(2)->setWindowFlags(Qt::CustomizeWindowHint);
    ui->mdiArea->subWindowList().value(2)->hide();

    page4_StartEtapCamber = new Page4_StartEtapCamber();

    connect(page4_StartEtapCamber, &Page4_StartEtapCamber::Beak,this,&MainWindow::on_actionProverki_triggered);

    //задаем размер окна
    page4_StartEtapCamber->setMinimumSize(247,189);

    ui->mdiArea->addSubWindow(page4_StartEtapCamber);

    ui->mdiArea->subWindowList().at(3)->hide();

    connect(page3_proverki, &Page3_Proverki::OpenStartEtapCamber,this,&MainWindow::on_actionStartEtapCamber_triggered);

    page5_prmWindow_NP1 = new page5_PRMWindow();

    page5_prmWindow_NP1->setWindowTitle("ПРМ № 1");

    //задаем размер окна
    page5_prmWindow_NP1->setMinimumSize(330,550);


    //Надо проверить 10 Mgz сигналы на ошибки 1 порта с первым прибором
    //connect(page5_prmWindow_NP1,&page5_PRMWindow::Error_10Gh,page2_ConnectDevice->proverka->proverka1->relizProverkaTimer,&relizproverkaTimer::slot_stopProverka_error_10Mhz);

    //connect(page2_ConnectDevice->proverka->port->PortNew,&Port::error_10Mgz,page2_ConnectDevice->proverka->proverka1->relizProverkaTimer,&relizproverkaTimer::slot_stopProverka_error_10Mhz);




    ui->mdiArea->addSubWindow(page5_prmWindow_NP1);

    connect(page5_prmWindow_NP1,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(4),&QMdiSubWindow::hide);


    ui->mdiArea->subWindowList().at(4)->hide();

    page5_prmWindow_NP2 = new page5_PRMWindow();

    page5_prmWindow_NP2->setWindowTitle("ПРМ № 2");

    //задаем размер окна
    page5_prmWindow_NP2->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP2);

    connect(page5_prmWindow_NP2,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(5),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(5)->hide();

    page5_prmWindow_NP3 = new page5_PRMWindow();

    page5_prmWindow_NP3->setWindowTitle("ПРМ № 3");

    //задаем размер окна
    page5_prmWindow_NP3->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP3);

    connect(page5_prmWindow_NP3,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(6),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(6)->hide();

    page5_prmWindow_NP4 = new page5_PRMWindow();

    page5_prmWindow_NP4->setWindowTitle("ПРМ № 4");

    //задаем размер окна
    page5_prmWindow_NP4->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP4);

    connect(page5_prmWindow_NP4,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(7),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(7)->hide();

    page5_prmWindow_NP5 = new page5_PRMWindow();

    page5_prmWindow_NP5->setWindowTitle("ПРМ № 5");

    //задаем размер окна
    page5_prmWindow_NP5->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP5);

    connect(page5_prmWindow_NP5,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(8),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(8)->hide();

    page5_prmWindow_NP6 = new page5_PRMWindow();

    page5_prmWindow_NP6->setWindowTitle("ПРМ № 6");

    //задаем размер окна
    page5_prmWindow_NP6->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP6);

    connect(page5_prmWindow_NP6,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(9),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(9)->hide();

    page5_prmWindow_NP7 = new page5_PRMWindow();

    page5_prmWindow_NP7->setWindowTitle("ПРМ № 7");

    //задаем размер окна
    page5_prmWindow_NP7->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP7);

    connect(page5_prmWindow_NP7,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(10),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(10)->hide();

    page5_prmWindow_NP8 = new page5_PRMWindow();

    page5_prmWindow_NP8->setWindowTitle("ПРМ № 8");

    //задаем размер окна
    page5_prmWindow_NP8->setMinimumSize(130,514);

    ui->mdiArea->addSubWindow(page5_prmWindow_NP8);

    connect(page5_prmWindow_NP8,&page5_PRMWindow::closeWindowNP,ui->mdiArea->subWindowList().value(11),&QMdiSubWindow::hide);

    ui->mdiArea->subWindowList().at(11)->hide();

    page6_FindDevice = new Page6_FindDevice();

    ui->mdiArea->addSubWindow(page6_FindDevice);

    ui->mdiArea->subWindowList().value(12)->setWindowFlags(Qt::CustomizeWindowHint);
    ui->mdiArea->subWindowList().at(12)->hide();

    connect(page2_ConnectDevice->find,&FindDevice::ListDeviceChanged,page6_FindDevice,&Page6_FindDevice::FindDeviceListChenge);

    connect(page2_ConnectDevice,&Page2_ConnectDevice::OpenFindDevice,this,&MainWindow::on_actionFindDevice_triggered);

    connect(page6_FindDevice,&Page6_FindDevice::FindDeviceWork,page2_ConnectDevice->find,&FindDevice::Work);

    connect(page6_FindDevice,&Page6_FindDevice::IP,page2_ConnectDevice,&Page2_ConnectDevice::getFindIp);
    connect(page6_FindDevice,&Page6_FindDevice::IP,this,&MainWindow::on_actionFind_triggered);

    /////////////////////////////////////////////////////////////////////////////////

    viewProverka = new QQuickView();
    viewProverka->rootContext()->setContextProperty("proverka", page2_ConnectDevice->proverka);
    viewProverka->rootContext()->setContextProperty("camber", page2_ConnectDevice->camber);
    viewProverka->rootContext()->setContextProperty("pdf", page2_ConnectDevice->pdf);

    viewProverka->rootContext()->setContextProperty("gsg", page2_ConnectDevice->gsg);
    viewProverka->rootContext()->setContextProperty("n6700_1", page2_ConnectDevice->n6700_1);
    viewProverka->rootContext()->setContextProperty("n6700_2", page2_ConnectDevice->n6700_2);
    viewProverka->rootContext()->setContextProperty("os", page2_ConnectDevice->os);
    viewProverka->rootContext()->setContextProperty("tp", page2_ConnectDevice->tp);

    viewProverka->rootContext()->setContextProperty("port1", page2_ConnectDevice->port1);
    viewProverka->rootContext()->setContextProperty("port2", page2_ConnectDevice->port2);
    viewProverka->rootContext()->setContextProperty("port3", page2_ConnectDevice->port3);
    viewProverka->rootContext()->setContextProperty("port4", page2_ConnectDevice->port4);
    viewProverka->rootContext()->setContextProperty("port5", page2_ConnectDevice->port5);
    viewProverka->rootContext()->setContextProperty("port6", page2_ConnectDevice->port6);
    viewProverka->rootContext()->setContextProperty("port7", page2_ConnectDevice->port7);
    viewProverka->rootContext()->setContextProperty("port8", page2_ConnectDevice->port8);

    viewProverka->rootContext()->setContextProperty("find", page2_ConnectDevice->find);

    viewProverka->rootContext()->setContextProperty("MainWindow", this);

    viewProverka->setSource(QUrl("qrc:/np.qml"));

    qDebug () << viewProverka->source();

    qDebug () << viewProverka->errors();

    containerProverka = QWidget::createWindowContainer(viewProverka);




    ui->mdiArea->addSubWindow(containerProverka);

    ui->mdiArea->subWindowList().value(13)->show();
    ui->mdiArea->subWindowList().value(13)->hide();


    connect(page4_StartEtapCamber,&Page4_StartEtapCamber::StartProverka,this,&MainWindow::startOneProverka);

    ///////////////////////////

    // Всё, что требуется в данном файле - это зарегистрировать новый класс (Тип объекта) для QML слоя
    qmlRegisterType<ClockCircle>("ClockCircle",1,0,"ClockCircle");

    viewTiemer = new QQuickView();
    viewTiemer->rootContext()->setContextProperty("proverka", page2_ConnectDevice->proverka);
    viewTiemer->rootContext()->setContextProperty("camber", page2_ConnectDevice->camber);
    viewTiemer->rootContext()->setContextProperty("pdf", page2_ConnectDevice->pdf);

    viewTiemer->rootContext()->setContextProperty("gsg", page2_ConnectDevice->gsg);
    viewTiemer->rootContext()->setContextProperty("n6700_1", page2_ConnectDevice->n6700_1);
    viewTiemer->rootContext()->setContextProperty("n6700_2", page2_ConnectDevice->n6700_2);
    viewTiemer->rootContext()->setContextProperty("os", page2_ConnectDevice->os);
    viewTiemer->rootContext()->setContextProperty("tp", page2_ConnectDevice->tp);

    viewTiemer->rootContext()->setContextProperty("port1", page2_ConnectDevice->port1);
    viewTiemer->rootContext()->setContextProperty("port2", page2_ConnectDevice->port2);
    viewTiemer->rootContext()->setContextProperty("port3", page2_ConnectDevice->port3);
    viewTiemer->rootContext()->setContextProperty("port4", page2_ConnectDevice->port4);
    viewTiemer->rootContext()->setContextProperty("port5", page2_ConnectDevice->port5);
    viewTiemer->rootContext()->setContextProperty("port6", page2_ConnectDevice->port6);
    viewTiemer->rootContext()->setContextProperty("port7", page2_ConnectDevice->port7);
    viewTiemer->rootContext()->setContextProperty("port8", page2_ConnectDevice->port8);

    viewTiemer->rootContext()->setContextProperty("find", page2_ConnectDevice->find);

    viewTiemer->rootContext()->setContextProperty("page2_ConnectDevice", page2_ConnectDevice);

    //  connect(page2_ConnectDevice,&Page2_ConnectDevice::signals_StartProverka,page2_ConnectDevice->proverkaModel->proverka,&Proverka::slot_StartProverka);
    // connect(page2_ConnectDevice,&Page2_ConnectDevice::signals_StartProverka2,page2_ConnectDevice->proverkaModel->proverka,&Proverka::slot_StartProverka2);
    //  connect(page2_ConnectDevice,&Page2_ConnectDevice::signals_StartProverka3,page2_ConnectDevice->proverkaModel->proverka,&Proverka::slot_StartProverka3);

    connect(page2_ConnectDevice,&Page2_ConnectDevice::signals_StartProverka,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka);
    connect(page2_ConnectDevice,&Page2_ConnectDevice::signals_StartProverka2,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka2);
    connect(page2_ConnectDevice,&Page2_ConnectDevice::signals_StartProverka3,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka3);


    viewTiemer->setSource(QUrl("qrc:/ClockCircle.qml"));

    qDebug () << viewTiemer->source();

    qDebug () << viewTiemer->errors();

    containerTiemer = QWidget::createWindowContainer(viewTiemer);

    containerTiemer->setMinimumSize(1200,900);

    ui->mdiArea->addSubWindow(containerTiemer);

    ui->mdiArea->subWindowList().value(14)->show();
    ui->mdiArea->subWindowList().value(14)->hide();


    connect(this,&MainWindow::setNY,page2_ConnectDevice->camber,&CamberModel::slot_SetNY);
    connect(this,&MainWindow::setCold,page2_ConnectDevice->camber,&CamberModel::slot_SetCold);
    connect(this,&MainWindow::setHord,page2_ConnectDevice->camber,&CamberModel::slot_SetHord);
    //  connect(page2_ConnectDevice->proverkaModel->proverka,&Proverka::signalOnMainWindow_OpenWindowWork,this,&MainWindow::openWindowWork);
    //  connect(page2_ConnectDevice->proverkaModel->proverka,&Proverka::signalOnMainWindow_finish,this,&MainWindow::on_actionProverki_triggered);

    connect(page2_ConnectDevice->proverka,&Proverka::signalOnMainWindow_OpenWindowWork,this,&MainWindow::openWindowWork);
    connect(page2_ConnectDevice->proverka,&Proverka::signalOnMainWindow_finish,this,&MainWindow::on_actionFind_triggered);


    //Соединяем signal (источника питания) со слотами представления Widghet

    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP1,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP1,&page5_PRMWindow::slot_getMeasureVolt);

    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP2,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP2,&page5_PRMWindow::slot_getMeasureVolt);

    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP3,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP3,&page5_PRMWindow::slot_getMeasureVolt);

    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP4,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_1->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP4,&page5_PRMWindow::slot_getMeasureVolt);

    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP5,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP5,&page5_PRMWindow::slot_getMeasureVolt);

    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP6,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP6,&page5_PRMWindow::slot_getMeasureVolt);


    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP7,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP7,&page5_PRMWindow::slot_getMeasureVolt);


    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureCURRentSignal,page5_prmWindow_NP8,&page5_PRMWindow::slot_getMeasureTok);
    connect(page2_ConnectDevice->n6700_2->n6700,&N6700::getMeasureVoltSignal,page5_prmWindow_NP8,&page5_PRMWindow::slot_getMeasureVolt);




    //Соединяем signal (ком порт 1) со слотами представления Widghet
    connect(page2_ConnectDevice->port1->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP1,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 2) со слотами представления Widghet
    connect(page2_ConnectDevice->port2->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP2,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 3) со слотами представления Widghet
    connect(page2_ConnectDevice->port3->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP3,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 4) со слотами представления Widghet
    connect(page2_ConnectDevice->port4->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP4,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 5) со слотами представления Widghet
    connect(page2_ConnectDevice->port5->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP5,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 6) со слотами представления Widghet
    connect(page2_ConnectDevice->port6->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP6,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 7) со слотами представления Widghet
    connect(page2_ConnectDevice->port7->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP7,&page5_PRMWindow::slot_getUpdateTableSP);
    //Соединяем signal (ком порт 8) со слотами представления Widghet
    connect(page2_ConnectDevice->port8->PortNew,&Port::signal_GoTORelizproverka,page5_prmWindow_NP8,&page5_PRMWindow::slot_getUpdateTableSP);

    //Соединяем signal (имитатор) со слотами представления Widghet
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP1,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP1,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP2,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP2,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP3,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP3,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP4,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP4,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP5,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP5,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP6,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP6,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP7,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP7,&page5_PRMWindow::slot_countSpytnik_G);

    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_R,page5_prmWindow_NP8,&page5_PRMWindow::slot_countSpytnik_R);
    connect(page2_ConnectDevice->gsg,&gsgModel::countSpytnik_G,page5_prmWindow_NP8,&page5_PRMWindow::slot_countSpytnik_G);

    /*
    connect(page2_ConnectDevice->proverka->proverka1,&proverkaItem::glonassFindChanged,page5_prmWindow_NP1,&page5_PRMWindow::slot_countFindSpytnik_R);
    connect(page2_ConnectDevice->proverka->proverka1,&proverkaItem::gpsFindChanged,page5_prmWindow_NP1,&page5_PRMWindow::slot_countFindSpytnik_G);

    connect(page2_ConnectDevice->proverka->proverka1->relizProverkaTimer,&relizproverkaTimer::signal_Tick,page5_prmWindow_NP1,&page5_PRMWindow::slot_updateTikTimer);

    if(page2_ConnectDevice->proverka->proverka2 != NULL)
    {
        connect(page2_ConnectDevice->proverka->proverka2,&proverkaItem::glonassFindChanged,page5_prmWindow_NP2,&page5_PRMWindow::slot_countFindSpytnik_R);
        connect(page2_ConnectDevice->proverka->proverka2,&proverkaItem::gpsFindChanged,page5_prmWindow_NP2,&page5_PRMWindow::slot_countFindSpytnik_G);
        connect(page2_ConnectDevice->proverka->proverka2->relizProverkaTimer,&relizproverkaTimer::signal_Tick,page5_prmWindow_NP2,&page5_PRMWindow::slot_updateTikTimer);
    }

    connect(page2_ConnectDevice->proverka,&Proverka::signal_slot_comand6_Connect_Vx2_10_ext,page2_ConnectDevice->tp,&TP8::slot_comand6_Connect_Vx2_10_ext);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_slot_comand7_Set_zatyxanie_10,page2_ConnectDevice->tp,&TP8::slot_comand7_Set_zatyxanie_10);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_slot_comand5_Connect_10MG,page2_ConnectDevice->tp,&TP8::slot_comand5_Connect_10MG);

    */


    connect(page2_ConnectDevice->tp,&TP8::signal_comandaClear_ok,page2_ConnectDevice->proverka,&Proverka::signal_StartProverka_BeforeClearTP,Qt::DirectConnection);

    connect(page2_ConnectDevice->tp,&TP8::signal_comanda1_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda2_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda3_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda4_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda5_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda6_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda7_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);
    connect(page2_ConnectDevice->tp,&TP8::signal_comanda8_ok,page2_ConnectDevice->proverka,&Proverka::slot_StartProverka_Os,Qt::DirectConnection);

    /*
    //Сигнал очистки окон
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP1,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP2,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP3,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP4,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP5,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP6,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP7,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP8,&page5_PRMWindow::slot_clearWindow);

    */
    ///////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////

    viewPDF = new QQuickView();
    viewPDF->rootContext()->setContextProperty("proverka", page2_ConnectDevice->proverka);
    viewPDF->rootContext()->setContextProperty("camber", page2_ConnectDevice->camber);
    viewPDF->rootContext()->setContextProperty("pdf", page2_ConnectDevice->pdf);

    viewPDF->rootContext()->setContextProperty("gsg", page2_ConnectDevice->gsg);
    viewPDF->rootContext()->setContextProperty("n6700_1", page2_ConnectDevice->n6700_1);
    viewPDF->rootContext()->setContextProperty("n6700_2", page2_ConnectDevice->n6700_2);
    viewPDF->rootContext()->setContextProperty("os", page2_ConnectDevice->os);
    viewPDF->rootContext()->setContextProperty("tp", page2_ConnectDevice->tp);

    viewPDF->rootContext()->setContextProperty("port1", page2_ConnectDevice->port1);
    viewPDF->rootContext()->setContextProperty("port2", page2_ConnectDevice->port2);
    viewPDF->rootContext()->setContextProperty("port3", page2_ConnectDevice->port3);
    viewPDF->rootContext()->setContextProperty("port4", page2_ConnectDevice->port4);
    viewPDF->rootContext()->setContextProperty("port5", page2_ConnectDevice->port5);
    viewPDF->rootContext()->setContextProperty("port6", page2_ConnectDevice->port6);
    viewPDF->rootContext()->setContextProperty("port7", page2_ConnectDevice->port7);
    viewPDF->rootContext()->setContextProperty("port8", page2_ConnectDevice->port8);

    viewPDF->rootContext()->setContextProperty("find", page2_ConnectDevice->find);

    viewPDF->rootContext()->setContextProperty("MainWindow", this);

    viewPDF->setSource(QUrl("qrc:/Page3.qml"));

    qDebug () << viewPDF->source();

    qDebug () << viewPDF->errors();

    containerPDF = QWidget::createWindowContainer(viewPDF);


    containerPDF->setMinimumSize(1200,900);


    ui->mdiArea->addSubWindow(containerPDF);

    ui->mdiArea->subWindowList().value(15)->hide();

    //временно пока нет камеры

    connect(page2_ConnectDevice->proverka,&Proverka::signal_startCold,this,&MainWindow::on_actionProverki_triggered);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_startNY,this,&MainWindow::on_actionProverki_triggered);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_startHord,this,&MainWindow::on_actionProverki_triggered);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_startNY,this,&MainWindow::on_actionProverki_triggered);




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionMode_triggered()
{

    for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        ui->mdiArea->subWindowList().value(i)->hide();
    }

    ui->actionFind->setChecked(false);
    ui->actionPDF->setChecked(false);
    ui->actionProverki->setChecked(false);
    ui->actionResult->setChecked(false);


    if(ui->mdiArea->subWindowList().value(0)->isVisible())
    {
        ui->mdiArea->subWindowList().value(0)->hide();
    }
    else
    {
        ui->mdiArea->subWindowList().value(0)->show();
    }

}



void MainWindow::on_actionFind_triggered()
{

    for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        ui->mdiArea->subWindowList().value(i)->hide();
    }

    ui->mdiArea->subWindowList().value(0)->hide();


    page2_ConnectDevice->proverka->setfioStart(page1_checketap->getName());
    page2_ConnectDevice->setName(page1_checketap->getName());

    page2_ConnectDevice->proverka->setModeStart(page1_checketap->getMode());
    page2_ConnectDevice->setMode(page1_checketap->getMode());


    if(ui->mdiArea->subWindowList().value(1)->isVisible())
    {
        ui->actionMode->setChecked(true);
        ui->mdiArea->subWindowList().value(0)->show();
        ui->actionFind->setChecked(false);
        ui->mdiArea->subWindowList().value(1)->hide();
    }
    else
    {
        ui->actionMode->setChecked(false);
        ui->mdiArea->subWindowList().value(0)->hide();
        ui->actionFind->setChecked(true);
        ui->mdiArea->subWindowList().value(1)->show();
    }

}

void MainWindow::on_actionProverki_triggered()
{

    if(ui->mdiArea->subWindowList().value(2)->isVisible())
    {
        ui->actionProverki->setChecked(false);

        ui->mdiArea->subWindowList().value(2)->hide();

        ui->actionFind->setChecked(true);
        ui->mdiArea->subWindowList().value(1)->show();
    }
    else
    {

        ui->actionProverki->setChecked(true);
        ui->actionMode->setChecked(false);
        ui->actionFind->setChecked(false);
        ui->actionPDF->setChecked(false);
        ui->actionResult->setChecked(false);

        for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
        {
            ui->mdiArea->subWindowList().value(i)->hide();
        }


        if(page2_ConnectDevice->flag_auto)
        {
            startOneProverka(1,1);
        }
        else
        {
            ui->mdiArea->subWindowList().value(2)->show();
        }
    }

}

void MainWindow::on_actionStartEtapCamber_triggered(int indexproverka)
{
    for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        ui->mdiArea->subWindowList().value(i)->hide();
    }


    //page2_ConnectDevice->gsg->tp->slot_comand1_Connect_Vx2_10(0x01);
    // page2_ConnectDevice->gsg->tp->slot_comand5_Connect_10MG(0x01);

    page4_StartEtapCamber->setIndexProverka(indexproverka);

    ui->mdiArea->subWindowList().value(3)->show();
}

void MainWindow::on_actionFindDevice_triggered(int index)
{
    for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        ui->mdiArea->subWindowList().value(i)->hide();
    }

    page6_FindDevice->index = index;

    ui->mdiArea->subWindowList().value(1)->show();
    ui->mdiArea->subWindowList().value(12)->show();
}

void MainWindow::startOneProverka(int indexProverka, int modeCamber)
{

    // initializate_proverka();

    for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        ui->mdiArea->subWindowList().value(i)->hide();
    }

    //page2_ConnectDevice->proverkaModel->proverka->autoProverka = false;
    // page2_ConnectDevice->proverkaModel->proverka->namberModeCamber = modeCamber;
    // page2_ConnectDevice->proverkaModel->proverka->namberProverkaStart = indexProverka;

    //  page2_ConnectDevice->proverka->autoProverka = false;
    page2_ConnectDevice->proverka->namberModeCamber = modeCamber;
    page2_ConnectDevice->proverka->namberProverkaStart = indexProverka;


    switch (modeCamber) {
    case 2:
    {
        emit setCold();
        break;
    }
    case 4:
    {
        emit setHord();
        break;
    }
    default:
    {
        emit setNY();
        break;
    }
    }

    page2_ConnectDevice->camber->slot_startCamberWork();
    page2_ConnectDevice->camber->slot_StartTimer();


    ui->mdiArea->subWindowList().value(14)->show();

}

void MainWindow::openWindowWork()
{
    for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        ui->mdiArea->subWindowList().value(i)->hide();
    }

    ui->mdiArea->subWindowList().value(13)->show(); //showMaximized



}

void MainWindow::openWindowWorkNP(int index)
{
    switch (index) {
    case 0:
    {
        ui->mdiArea->subWindowList().value(4)->show();
        break;
    }
    case 1:
    {
        ui->mdiArea->subWindowList().value(5)->show();
        break;
    }
    case 2:
    {
        ui->mdiArea->subWindowList().value(6)->show();
        break;
    }
    case 3:
    {
        ui->mdiArea->subWindowList().value(7)->show();
        break;
    }
    }

}

void MainWindow::initializate_proverka()
{
    // нужно запустить поиск количества спутников.

    if((page2_ConnectDevice->n6700_1 != nullptr))
    {




        if(page2_ConnectDevice->n6700_1->n6700->connected == true)
        {
            if(page2_ConnectDevice->n6700_1->n6700->timer_IstP1_Measure->isActive())
            {
                page2_ConnectDevice->n6700_1->slot_StopTimer();
            }

            page2_ConnectDevice->n6700_1->n6700->setOutput("ALL",true);


        }

    }

    if((page2_ConnectDevice->n6700_2 != nullptr))
    {

        if(page2_ConnectDevice->n6700_2->n6700->connected == true)
        {

            if(page2_ConnectDevice->n6700_2->n6700->timer_IstP1_Measure->isActive())
            {
                page2_ConnectDevice->n6700_2->slot_StopTimer();
            }


            page2_ConnectDevice->n6700_2->n6700->setOutput("ALL",true);
        }

    }


    QStringList list;


    QVector<QString> listFind_I =  page2_ConnectDevice->n6700_1->n6700->getMeasureCURRentALL_find();

    listFind_I =  page2_ConnectDevice->n6700_1->n6700->getMeasureCURRentALL_find();

    listFind_I =  page2_ConnectDevice->n6700_1->n6700->getMeasureCURRentALL_find();


    for(int i=0 ; i < listFind_I.count();i++)
    {
        qDebug () << listFind_I.value(i).toDouble();

        if(listFind_I.value(i).toDouble() > 0.01)
        {
            list.append(QString::number(i+1));
        }
    }


    listFind_I =  page2_ConnectDevice->n6700_2->n6700->getMeasureCURRentALL_find();

    listFind_I =  page2_ConnectDevice->n6700_2->n6700->getMeasureCURRentALL_find();

    listFind_I =  page2_ConnectDevice->n6700_2->n6700->getMeasureCURRentALL_find();


    for(int i=0 ; i < listFind_I.count();i++)
    {
        if(listFind_I.value(i).toDouble() > 0.1)
        {
            list.append(QString::number(i+5));
        }
    }

    qDebug () << list;


    if((page2_ConnectDevice->n6700_1 != nullptr))
    {

        if(page2_ConnectDevice->n6700_1->n6700->connected == true)
        {
            page2_ConnectDevice->n6700_1->n6700->setOutput("ALL",false);
        }

    }

    if((page2_ConnectDevice->n6700_2 != nullptr))
    {

        if(page2_ConnectDevice->n6700_2->n6700->connected == true)
        {
            page2_ConnectDevice->n6700_2->n6700->setOutput("ALL",false);
        }

    }



    page2_ConnectDevice->proverka->list_CountNP = list;

    page2_ConnectDevice->proverka->process_start();



    switch (page2_ConnectDevice->proverka->Count_NP)
    {
    case 1:
        ui->mdiArea->subWindowList().value(13)->setMinimumSize(1200/4,(900/2)-50);
        break;
    case 2:
        ui->mdiArea->subWindowList().value(13)->setMinimumSize((1200/4)*2+50,(900/2));
        break;
    case 3:
        ui->mdiArea->subWindowList().value(13)->setMinimumSize((1200/4)*3,(900/2)-50);
        break;
    case 4:
        ui->mdiArea->subWindowList().value(13)->setMinimumSize(1200,(900/2)-50);
        break;
    default:
        ui->mdiArea->subWindowList().value(13)->setMinimumSize(1200,900-100);
        break;
    }



    if(page2_ConnectDevice->proverka->proverka1 != nullptr)
    {
        connect(page2_ConnectDevice->proverka->proverka1,&proverkaItem::glonassFindChanged,page5_prmWindow_NP1,&page5_PRMWindow::slot_countFindSpytnik_R);
        connect(page2_ConnectDevice->proverka->proverka1,&proverkaItem::gpsFindChanged,page5_prmWindow_NP1,&page5_PRMWindow::slot_countFindSpytnik_G);

        connect(page2_ConnectDevice->proverka->proverka1->relizProverkaTimer,&relizproverkaTimer::signal_Tick,page5_prmWindow_NP1,&page5_PRMWindow::slot_updateTikTimer);

    }

    if(page2_ConnectDevice->proverka->proverka2 != nullptr)
    {
        connect(page2_ConnectDevice->proverka->proverka2,&proverkaItem::glonassFindChanged,page5_prmWindow_NP2,&page5_PRMWindow::slot_countFindSpytnik_R);
        connect(page2_ConnectDevice->proverka->proverka2,&proverkaItem::gpsFindChanged,page5_prmWindow_NP2,&page5_PRMWindow::slot_countFindSpytnik_G);
        connect(page2_ConnectDevice->proverka->proverka2->relizProverkaTimer,&relizproverkaTimer::signal_Tick,page5_prmWindow_NP2,&page5_PRMWindow::slot_updateTikTimer);
    }

    if(page2_ConnectDevice->proverka->proverka3 != nullptr)
    {
        connect(page2_ConnectDevice->proverka->proverka3,&proverkaItem::glonassFindChanged,page5_prmWindow_NP3,&page5_PRMWindow::slot_countFindSpytnik_R);
        connect(page2_ConnectDevice->proverka->proverka3,&proverkaItem::gpsFindChanged,page5_prmWindow_NP3,&page5_PRMWindow::slot_countFindSpytnik_G);
        connect(page2_ConnectDevice->proverka->proverka3->relizProverkaTimer,&relizproverkaTimer::signal_Tick,page5_prmWindow_NP3,&page5_PRMWindow::slot_updateTikTimer);
    }

    connect(page2_ConnectDevice->proverka,&Proverka::signal_slot_comand6_Connect_Vx2_10_ext,page2_ConnectDevice->tp,&TP8::slot_comand6_Connect_Vx2_10_ext);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_slot_comand7_Set_zatyxanie_10,page2_ConnectDevice->tp,&TP8::slot_comand7_Set_zatyxanie_10);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_slot_comand5_Connect_10MG,page2_ConnectDevice->tp,&TP8::slot_comand5_Connect_10MG);


    //Сигнал очистки окон
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP1,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP2,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP3,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP4,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP5,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP6,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP7,&page5_PRMWindow::slot_clearWindow);
    connect(page2_ConnectDevice->proverka,&Proverka::signal_clearView,page5_prmWindow_NP8,&page5_PRMWindow::slot_clearWindow);
}

void MainWindow::slot_startAutoWork()
{
    initializate_proverka();

    emit startAutoWork();
}

void MainWindow::on_actionResult_triggered()
{
    /*for(int i = 0; i < ui->mdiArea->subWindowList().count() ;i++)
    {
        if(i!=15)
        {
         ui->mdiArea->subWindowList().value(i)->hide();
        }
    } */

    if(ui->mdiArea->subWindowList().value(15)->isVisible())
    {
        ui->mdiArea->subWindowList().value(15)->hide();
        ui->actionPDF->setEnabled(false);
    }
    else
    {
        ui->mdiArea->subWindowList().value(15)->show();

        ui->actionPDF->setEnabled(true);

    }

}

void MainWindow::on_actionPDF_triggered()
{
    page2_ConnectDevice->pdf->slot_FindData();
}
