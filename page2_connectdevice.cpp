#include "page2_connectdevice.h"
#include "ui_page2_connectdevice.h"

Page2_ConnectDevice::Page2_ConnectDevice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page2_ConnectDevice),
    flag_auto(false)
{
    ui->setupUi(this);

    n6700_1 = new N6700Model();

    n6700_2 = new N6700Model();

    camber = new CamberModel(); //Создание объекта для управления камерой

    gsg = new gsgModel(); // Создали модель класса gsg

    os = new OsuilografModel();

    tp = new TP8();

    port1 = new PortModel();
    port2 = new PortModel();
    port3 = new PortModel();
    port4 = new PortModel();
    port5 = new PortModel();
    port6 = new PortModel();
    port7 = new PortModel();
    port8 = new PortModel();


    find = new FindDevice();

    BD = new BData(); // Создали класс для работы с базой данных

    BD->connect(); // Подключаемся к БД

    gsg->SetBD(BD); // Передаем указатель на класс БД для работы с ним из класса GSG для того чтоб во время проверок записывать для каждого.
    gsg->Sed_TP_OS(os,tp); // Передаем указатель на класс Осцилографа и Пульта для использования его в проверках.



    QQmlApplicationEngine engine;

    screenCapture screenClass(&engine);

   // proverkaModel = new ProverkaModel(camber,gsg,n6700_1,port1,port2,port3,port4,port5,port6,port7,port8,&screenClass,this);

   // proverkaModel->SetBD(BD);

    proverka = new Proverka(camber,gsg,n6700_1,n6700_2,port1,port2,port3,port4,port5,port6,port7,port8,&screenClass); // Создали модель класса port, для управления и обновления объектов в QML

    proverka->SetBD(BD);

    pdf = new Report(gsg); // Создаем класс для создания Отчетности.


    connect(n6700_1,&N6700Model::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_1);
    connect(n6700_2,&N6700Model::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_2);
    connect(camber,&CamberModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_Camber);
    connect(gsg,&gsgModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_GSG);
    connect(os,&OsuilografModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_Os);
    connect(tp,&TP8::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_TP8);

    connect(port1,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port1);
    connect(port2,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port2);
    connect(port3,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port3);
    connect(port4,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port4);
    connect(port5,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port5);
    connect(port6,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port6);
    connect(port7,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port7);
    connect(port8,&PortModel::signal_Ok,this,&Page2_ConnectDevice::slot_coonnectOK_port8);


    ui->comboBox_1->addItems( port1->listCOM());
    ui->comboBox_2->addItems( port2->listCOM());
    if(port2->listCOM().count()>= 1)
        ui->comboBox_2->setCurrentIndex(1);
    ui->comboBox_3->addItems( port3->listCOM());
    if(port3->listCOM().count()>= 2)
        ui->comboBox_3->setCurrentIndex(2);
    ui->comboBox_4->addItems( port4->listCOM());
    if(port4->listCOM().count()>= 3)
        ui->comboBox_4->setCurrentIndex(3);
    ui->comboBox_5->addItems( port5->listCOM());
    if(port5->listCOM().count()>= 4)
        ui->comboBox_5->setCurrentIndex(4);
    ui->comboBox_6->addItems( port6->listCOM());
    if(port6->listCOM().count()>= 5)
        ui->comboBox_6->setCurrentIndex(5);
    ui->comboBox_7->addItems( port7->listCOM());
    if(port7->listCOM().count()>= 6)
        ui->comboBox_7->setCurrentIndex(6);
    ui->comboBox_8->addItems( port8->listCOM());
    if(port8->listCOM().count()>= 7)
        ui->comboBox_8->setCurrentIndex(7);

}

Page2_ConnectDevice::~Page2_ConnectDevice()
{
    delete ui;
}

void Page2_ConnectDevice::setName(QString name)
{
    ui->label_FIO->setText(name);
}

void Page2_ConnectDevice::setMode(QString mode)
{
    ui->label_Mode->setText(mode);
}

//Слот кнопки для подключения Первого источника питания
void Page2_ConnectDevice::on_pushButton_IS1_clicked()
{
    if(ui->pushButton_IS1->text() == "Подключить")
    {
        n6700_1->slot_connectDevice(ui->lineEdit_IS1->text());

        ui->pushButton_IS1->setText("Ждем ответа сигнала");
    }
    else
    {
        n6700_1->slot_DisConnect();
        ui->pushButton_IS1->setText("Подключить");

        ui->label_IS1->setText("Прибор не подключен");
        ui->label_IS1->setStyleSheet("");
    }
}
//Слот ответа устройства на подключения Первого источника питания
void Page2_ConnectDevice::slot_coonnectOK_1(bool ok)
{
    if(ok)
    {
        ui->pushButton_IS1->setText("Отключить");
        ui->label_IS1->setText(n6700_1->name().split(',').first());
        ui->label_IS1->setStyleSheet("QLabel { background-color : green; color : white; }");

    }
    else
    {
        ui->pushButton_IS1->setText("Подключить");

        ui->label_IS1->setText("Прибор не подключен");
        ui->label_IS1->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

//Слот кнопки для подключения Второго источника питания
void Page2_ConnectDevice::on_pushButton_IS2_clicked()
{
    if(ui->pushButton_IS2->text() == "Подключить")
    {
        n6700_2->slot_connectDevice(ui->lineEdit_IS2->text());

        ui->pushButton_IS2->setText("Ждем ответа сигнала");
    }
    else
    {
        n6700_2->slot_DisConnect();
        ui->pushButton_IS2->setText("Подключить");

        ui->label_IS2->setText("Прибор не подключен");
        ui->label_IS2->setStyleSheet("");
    }
}

//Слот ответа устройства на подключения Второго источника питания
void Page2_ConnectDevice::slot_coonnectOK_2(bool ok)
{
    if(ok)
    {
        ui->pushButton_IS2->setText("Отключить");
        ui->label_IS2->setText(n6700_2->name().split(',').first());
        ui->label_IS2->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_IS2->setText("Подключить");

        ui->label_IS2->setText("Прибор не подключен");
        ui->label_IS2->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

//Слот кнопки для подключения Климатической камеры
void Page2_ConnectDevice::on_pushButton_Camber_clicked()
{
    if(ui->pushButton_Camber->text() == "Подключить")
    {
        camber->slot_connectCamber(ui->lineEdit_Camber->text());

        ui->pushButton_Camber->setText("Ждем ответа сигнала");
    }
    else
    {
        ui->pushButton_Camber->setText("Подключить");

        ui->label_Camber->setText("Прибор не подключен");
        ui->label_Camber->setStyleSheet("");
    }
}
//Слот ответа устройства на подключения Климатической камеры
void Page2_ConnectDevice::slot_coonnectOK_Camber(bool ok)
{
    if(ok)
    {
        ui->pushButton_Camber->setText("Отключить");
        ui->label_Camber->setText("Камера подключенна");
        ui->label_Camber->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_Camber->setText("Подключить");

        ui->label_Camber->setText("Прибор не подключен");
        ui->label_Camber->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

//Слот кнопки для подключения Имитатора
void Page2_ConnectDevice::on_pushButton_Imitator_clicked()
{
    if(ui->pushButton_Imitator->text() == "Подключить")
    {
        gsg->slot_connectDevice(ui->lineEdit_Imitator->text());

        ui->pushButton_Imitator->setText("Ждем ответа сигнала");
    }
    else
    {
        ui->pushButton_Imitator->setText("Подключить");

        ui->label_Imitator->setText("Прибор не подключен");
        ui->label_Imitator->setStyleSheet("");
    }
}

//Слот ответа устройства на подключения Имитатора
void Page2_ConnectDevice::slot_coonnectOK_GSG(bool ok)
{
    if(ok)
    {
        ui->pushButton_Imitator->setText("Отключить");
        ui->label_Imitator->setText(gsg->name().split(',').first());
        ui->label_Imitator->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_Imitator->setText("Подключить");

        ui->label_Imitator->setText("Прибор не подключен");
        ui->label_Imitator->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

//Слот кнопки для подключения Осцилографа
void Page2_ConnectDevice::on_pushButton_Os_clicked()
{
    if(ui->pushButton_Os->text() == "Подключить")
    {
        os->slot_connectDevice(ui->lineEdit_Os->text());

        ui->pushButton_Os->setText("Ждем ответа сигнала");
    }
    else
    {
        ui->pushButton_Os->setText("Подключить");

        ui->label_Os->setText("Прибор не подключен");
        ui->label_Os->setStyleSheet("");
    }
}

//Слот ответа устройства на подключения Осцилографа
void Page2_ConnectDevice::slot_coonnectOK_Os(bool ok)
{
    if(ok)
    {
        ui->pushButton_Os->setText("Отключить");
        ui->label_Os->setText(os->name().split(',').first());
        ui->label_Os->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_Os->setText("Подключить");

        ui->label_Os->setText("Прибор не подключен");
        ui->label_Os->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

//Слот кнопки для подключения Пульта
void Page2_ConnectDevice::on_pushButton_TP8_clicked()
{
    if(ui->pushButton_TP8->text() == "Подключить")
    {
        tp->slot_ConnectTp(ui->lineEdit_TP8->text());

        ui->pushButton_TP8->setText("Ждем ответа сигнала");
    }
    else
    {
        ui->pushButton_TP8->setText("Подключить");

        ui->label_TP8->setText("Прибор не подключен");
        ui->label_TP8->setStyleSheet("");
    }
}

//Слот ответа устройства на подключения Пульта
void Page2_ConnectDevice::slot_coonnectOK_TP8(bool ok)
{
    if(ok)
    {
        ui->pushButton_TP8->setText("Отключить");
        ui->label_TP8->setText("Подлючен TP8 : " + tp->ipTP);
        ui->label_TP8->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_TP8->setText("Подключить");

        ui->label_TP8->setText("Прибор не подключен");
        ui->label_TP8->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////

void Page2_ConnectDevice::on_pushButton_COMNP1_clicked()
{
    if(ui->pushButton_COMNP1->text() == "Подключить")
    {
        port1->openPort(ui->comboBox_1->currentText());

        ui->pushButton_COMNP1->setText("Ждем ответа от COM1");
    }
    else
    {
        port1->closePort();
        port1->slot_endWork();

        ui->pushButton_COMNP1->setText("Подключить");
        ui->label_COMNP1->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port1(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP1->setText("Отключить");
        ui->label_COMNP1->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP1->setText("Подключить");
        ui->label_COMNP1->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}


void Page2_ConnectDevice::on_pushButton_COMNP2_clicked()
{
    if(ui->pushButton_COMNP2->text() == "Подключить")
    {
        port2->openPort(ui->comboBox_2->currentText());
        ui->pushButton_COMNP2->setText("Ждем ответа от COM2");
    }
    else
    {
        port2->closePort();
        port2->slot_endWork();

        ui->pushButton_COMNP2->setText("Подключить");
        ui->label_COMNP2->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port2(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP2->setText("Отключить");
        ui->label_COMNP2->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP2->setText("Подключить");
        ui->label_COMNP2->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_COMNP3_clicked()
{
    if(ui->pushButton_COMNP3->text() == "Подключить")
    {
        port3->openPort(ui->comboBox_3->currentText());
        ui->pushButton_COMNP3->setText("Ждем ответа от COM3");
    }
    else
    {
        port3->closePort();
        port3->slot_endWork();

        ui->pushButton_COMNP3->setText("Подключить");
        ui->label_COMNP3->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port3(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP3->setText("Отключить");
        ui->label_COMNP3->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP3->setText("Подключить");
        ui->label_COMNP3->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_COMNP4_clicked()
{
    if(ui->pushButton_COMNP4->text() == "Подключить")
    {
        port4->openPort(ui->comboBox_4->currentText());
        ui->pushButton_COMNP4->setText("Ждем ответа от COM4");
    }
    else
    {
        port4->closePort();
        port4->slot_endWork();

        ui->pushButton_COMNP4->setText("Подключить");
        ui->label_COMNP4->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port4(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP4->setText("Отключить");
        ui->label_COMNP4->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP4->setText("Подключить");
        ui->label_COMNP4->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_COMNP5_clicked()
{
    if(ui->pushButton_COMNP5->text() == "Подключить")
    {
        port5->openPort(ui->comboBox_5->currentText());
        ui->pushButton_COMNP5->setText("Ждем ответа от COM5");
    }
    else
    {
        port5->closePort();
        port5->slot_endWork();

        ui->pushButton_COMNP5->setText("Подключить");
        ui->label_COMNP5->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port5(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP5->setText("Отключить");
        ui->label_COMNP5->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP5->setText("Подключить");
        ui->label_COMNP5->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_COMNP6_clicked()
{
    if(ui->pushButton_COMNP6->text() == "Подключить")
    {
        port6->openPort(ui->comboBox_6->currentText());
        ui->pushButton_COMNP6->setText("Ждем ответа от COM6");
    }
    else
    {
        port6->closePort();
        port6->slot_endWork();

        ui->pushButton_COMNP6->setText("Подключить");
        ui->label_COMNP6->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port6(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP6->setText("Отключить");
        ui->label_COMNP6->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP6->setText("Подключить");
        ui->label_COMNP6->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_COMNP7_clicked()
{
    if(ui->pushButton_COMNP7->text() == "Подключить")
    {
        port7->openPort(ui->comboBox_7->currentText());
        ui->pushButton_COMNP7->setText("Ждем ответа от COM7");
    }
    else
    {
        port7->closePort();
        port7->slot_endWork();

        ui->pushButton_COMNP7->setText("Подключить");
        ui->label_COMNP7->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port7(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP7->setText("Отключить");
        ui->label_COMNP7->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP7->setText("Подключить");
        ui->label_COMNP7->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_COMNP8_clicked()
{
    if(ui->pushButton_COMNP8->text() == "Подключить")
    {
        port8->openPort(ui->comboBox_8->currentText());
        ui->pushButton_COMNP8->setText("Ждем ответа от COM8");
    }
    else
    {
        port8->closePort();
        port8->slot_endWork();

        ui->pushButton_COMNP8->setText("Подключить");
        ui->label_COMNP8->setStyleSheet("");
    }
}

void Page2_ConnectDevice::slot_coonnectOK_port8(bool ok)
{
    if(ok)
    {

        ui->pushButton_COMNP8->setText("Отключить");
        ui->label_COMNP8->setStyleSheet("QLabel { background-color : green; color : white; }");
    }
    else
    {
        ui->pushButton_COMNP8->setText("Подключить");
        ui->label_COMNP8->setStyleSheet("QLabel { background-color : red; color : white; }");
    }
}

void Page2_ConnectDevice::on_pushButton_Work_clicked()
{
    emit startAutoWork();
}

void Page2_ConnectDevice::on_pushButton_Result_clicked()
{
    // запустить окно просмотра результатов
}

void Page2_ConnectDevice::on_pushButton_IS1_Find_clicked()
{
    emit OpenFindDevice(1); //index = 1; источник питания 1
}

void Page2_ConnectDevice::getFindIp(QString ip, int index)
{
    switch (index) {
    case 1:
    {
        ui->lineEdit_IS1->setText(ip);
        break;
    }
    case 2:
    {
        ui->lineEdit_IS2->setText(ip);
        break;
    }
    case 3:
    {
        ui->lineEdit_Camber->setText(ip);
        break;
    }
    case 4:
    {
        ui->lineEdit_Imitator->setText(ip);
        break;
    }
    case 5:
    {
        ui->lineEdit_Os->setText(ip);
        break;
    }
    case 6:
    {
        ui->lineEdit_TP8->setText(ip);
        break;
    }
    default:
        break;
    }
}

//////////////////////////////////////////////////////////////////////
/// \brief Page2_ConnectDevice::slot_StartProverka
///
void Page2_ConnectDevice::slot_StartProverka()
{
    emit signals_StartProverka();
}

void Page2_ConnectDevice::slot_StartProverka2()
{
    emit signals_StartProverka2();
}

void Page2_ConnectDevice::slot_StartProverka3()
{
    emit signals_StartProverka3();
}

///////////////////////////////////////////////////////////////////////////
void Page2_ConnectDevice::on_pushButton_IS2_Find_clicked()
{
    emit OpenFindDevice(2); //index = 2; источник питания 2
}

void Page2_ConnectDevice::on_pushButton_Camber_Find_clicked()
{
    emit OpenFindDevice(3); //index = 3;
}

void Page2_ConnectDevice::on_pushButton_Imitator_Find_clicked()
{
    emit OpenFindDevice(4); //index = 4;
}

void Page2_ConnectDevice::on_pushButton_Os_Find_clicked()
{
    emit OpenFindDevice(5); //index = 5;
}

void Page2_ConnectDevice::on_pushButton_TP8_Find_clicked()
{
    emit OpenFindDevice(6); //index = 6;
}

void Page2_ConnectDevice::on_checkBox_auto_stateChanged(int arg1)
{
    switch (arg1) {
        case 0:
                {
                    flag_auto = false;
                    proverka->autoProverka = false;
                    break;
                }
        case 2:
                {
                    flag_auto = true;
                    proverka->autoProverka = true;
                    break;
                }

    }
}

void Page2_ConnectDevice::slot_startAutoWork()
{

    if(flag_auto == true)
    {
        //Запуск окна камеры (ждем установки темпиратуры)

        //Запуск окна имитатора (ждем запуска имитатора)

        //Сначало установить темпиратуру 27 градусов (прграмма номер 3)
        camber->slot_SetNY();

        //Затем запустить камеру.
        camber->slot_startCamberWork();

        emit OpenProverki();

    }
    else
    {
        emit OpenProverki();
    }
}
