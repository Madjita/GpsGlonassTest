#include "relizproverka.h"
#include <QDebug>

#include <windows.h>
#include <math.h>

RelizProverka::RelizProverka(int indexGet,N6700Model* n6700Get,
                             gsgModel* gsgModelGet,PortModel* portGet,QString GetName,screenCapture * screenClassget, QObject *parent):
    QObject(parent),
    screenClass(screenClassget),
    Name(GetName),
    index(indexGet),
    gsg(gsgModelGet),
    n6700(n6700Get),
    port(portGet),
    minut(0),
    count(0),
    countProverka(0),
    Good(false),
    liter(26)
{

    this->moveToThread(new QThread()); //Переместили класс GSG в новый поток

    QObject::connect(this->thread(),&QThread::started,this,&RelizProverka::process_start);
    this->thread()->start();

    flag_auto = true; //автоматическая проверка включена

}

void RelizProverka::SetIdLink(QString GetIdLink)
{
    IdLink = GetIdLink;
}

//QString id;


void RelizProverka::process_start()
{




    //   QObject::connect(n6700,&N6700Model::startTimer,this,&RelizProverka::Work);
    //QObject::connect(n6700,&N6700Model::Work,this,&RelizProverka::Work);

    QObject::connect(this,&RelizProverka::Work_signal,n6700->n6700,&N6700::Work); //

    QObject::connect(this,&RelizProverka::startTimer,n6700,&N6700Model::slot_StartTimer); //

    QObject::connect(this,&RelizProverka::setOutput,n6700,&N6700Model::setOut); //
    QObject::connect(this,&RelizProverka::setVolt,n6700,&N6700Model::setVolt); //



    //  QObject::connect(this,&RelizProverka::endWork_signal,n6700->n6700,&N6700::endWork,Qt::BlockingQueuedConnection);


    // QObject::connect(this,&RelizProverka::signal_GoodQML,n6700,&N6700Model::slot_GoodQML);
    // QObject::connect(this,&RelizProverka::signal_BadQML,n6700,&N6700Model::slot_BadQML);


    //    this->timer = new QTimer();

    //    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(time()));
    //    QObject::connect(this,SIGNAL(startTimer1(int)),timer,SLOT(start(int)));
    //    QObject::connect(this,&RelizProverka::stopTimer1,timer,&QTimer::stop);

    //    this->timer2 = new QTimer();

    //    QObject::connect(this->timer2,&QTimer::timeout,this,&RelizProverka::time2);
    //    QObject::connect(this,SIGNAL(startTimer2(int)),this->timer2,SLOT(start(int)));
    //    QObject::connect(this,&RelizProverka::stopTimer2,this->timer2,&QTimer::stop);

    //QObject::connect(this,&RelizProverka::signal_TimerQML,n6700,&N6700Model::slot_TimerQML);


    //От QML на запуск других проверок

    //   QObject::connect(n6700,&N6700Model::signal_proverka,this,&RelizProverka::slot_proverka);


    QObject::connect(this,&RelizProverka::signal_StartProverka_1,this,&RelizProverka::proverka_rabotosposobnosti_NP_ID_1);
    QObject::connect(this,&RelizProverka::signal_StartProverka_2,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_2);
    QObject::connect(this,&RelizProverka::signal_StartProverka_3,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_3);
    QObject::connect(this,&RelizProverka::signal_StartProverka_4,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_4);
    QObject::connect(this,&RelizProverka::signal_StartProverka_5,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_5);
    QObject::connect(this,&RelizProverka::signal_StartProverka_6,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_6);
    QObject::connect(this,&RelizProverka::signal_StartProverka_7,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_7);
    QObject::connect(this,&RelizProverka::signal_StartProverka_8,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_8);
    QObject::connect(this,&RelizProverka::signal_StartProverka_9,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_9);
    QObject::connect(this,&RelizProverka::signal_StartProverka_10,this,&RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_10);



    sem = new QSemaphore();
    mut = new QMutex();



    //поиск id прибора в Бд
    QSqlQueryModel* SQL_id;

    qDebug () <<"NP :" +this->Name;


    SQL_id  = gsg->BD->zaprosQueryModel("SELECT * FROM Serial WHERE Serial like '"+this->Name+"'",this->index);



    for(int i=0;i< SQL_id->rowCount();i++)
    {
        Id = SQL_id->data(SQL_id->index(i,0), Qt::EditRole).toString();

        qDebug () <<"Id : " << Id;
    }

    qDebug () <<"NP :" +this->Name << " Id: " << this->Id;


}



void RelizProverka::process_start_timer()
{
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(time()));
    QObject::connect(this,SIGNAL(startTimer1(int)),timer,SLOT(start(int)));
    QObject::connect(this,&RelizProverka::stopTimer1,timer,&QTimer::stop);
}



void RelizProverka::process_start_timer2()
{
    QObject::connect(timer2,SIGNAL(timeout()),this,SLOT(time2()));
    QObject::connect(this,SIGNAL(startTimer2(int)),timer2,SLOT(start(int)));
    QObject::connect(this,&RelizProverka::stopTimer2,timer,&QTimer::stop);
}


//**********************************************************************************
//1.	Проверка работоспособности приемника
void RelizProverka::proverka_rabotosposobnosti_NP_ID_1()
{

    // proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_6();
    // return;


    qDebug () << "Запустили proverka_rabotosposobnosti_NP_ID_1 проверку " << index;



//    gsg->tp->index = index;
//    gsg->tp->slot_comand2_Connect_Vx1_1C(*QString::number(index).toUtf8().data()-0x30);

//    sem->acquire();

//    gsg->tp->index = index;
//    gsg->tp->slot_comand1_Connect_Vx2_10(*QString::number(index).toUtf8().data()-0x30);

//    sem->acquire();



    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    // На всякий случай зануление счета проверок ( это 1 проверка)
    countProverka = 0;
    // Подсчет проверок
    countProverka = 1;  //№1

    emit signal_StartProverkaIndex(QString::number(countProverka));

    //Cигнал для установки напряжения на источнике питания на том блоке к которому подсоединен приемник
    emit setVolt(QString::number(index),"5");
    //Подача питания на приемник
    emit setOutput(QString::number(index),true);
    //Флаг работы, приемник включен
    job = true;
    //Сигнал начала запуска таймера для проверки (3.30 минут)
    emit startWork();
    qDebug () << "Запустили 1 проверку";
    //Время начала проверки для записи в БД
    stay = QDateTime::currentDateTime();
    qDebug () << "Проверка Начата  1 ждем = " << sem->available();
    qDebug () << "Дата старта: " << start.toString("dd.MM.yyyy  hh:mm:ss");
    //Запись в БД начала проверки

    mut->lock();
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    mut->unlock();

    //screenClass->capture("Старт_" + QString::number(countProverka) + "_" +this->Name +".jpg");

    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
    sem->acquire();
    //По окончанию работы проверки переводим флаг работы в ложь, для показания того, что приемник прошел проверку и может быть выключен
    job = false;
    qDebug () << "Проверка Прошла = " << sem->available();
    //Флаг показывающий прошел ли приемник данную проверку или нет
    flag_good_1 = Good;

    if(flag_good_1)
    {
        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
    }
    else
    {
        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
    }

    //screenClass->capture("Конец_" + QString::number(countProverka) + "_" +this->Name +".jpg");


    //Сигнал выключения питания приемника по окончанию проверки
    emit setOutput(QString::number(index),false);
    //Сигнал завершения проверки
    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();



    //Остановка потока для того чтоб дождаться остальные приемники для перехода на следующую првоерку
    sem->acquire();

    //Если проверка автоматическая то продолжать дальше
    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_2();
    }
}
//**********************************************************************************

//**********************************************************************************
//2.	Проверка на воздействие пониженного напряжения питания
void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_2()  //Дописать код для управления  камерой климотов и поставить таймер на ждание 3 часов и 2 часов
{
    // Подсчет проверок
    countProverka = 2;  //№2


    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    //Cигнал для установки напряжения на источнике питания на том блоке к которому подсоединен приемник
    emit setVolt(QString::number(index),"4.75");
    //Подача питания на приемник
    emit setOutput(QString::number(index),true);
    //Флаг работы, приемник включен
    job = true;
    //Очитска листа с результатоми этапов 2 проверки по разным напряжениями питания
    list_flag_good_2.clear();
    //Сигнал начала запуска таймера для проверки (3.30 минут)
    emit startWork();
    qDebug () << "Запустили 2 проверку";
    qDebug () << "Проверка Начата  2 часть 1 ждем = " << sem->available();
    //Время начала проверки для записи в БД
    stay = QDateTime::currentDateTime();
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Проверка 2 часть 1
    proverka2_part = 1;
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
    sem->acquire();
    //По окончанию работы проверки переводим флаг работы в ложь, для показания того, что приемник прошел проверку и может быть выключен
    job = false;
    qDebug () << "Проверка 2 часть 1 Прошла = " << sem->available();
    //Флаг показывающий прошел ли приемник данную проверку или нет
    flag_good_2 = Good;
    //Добавление результата в лист
    list_flag_good_2.append(flag_good_2);

    if(flag_good_2)
    {
        switch (index) {
        case 1:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 2:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 3:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 4:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 5:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 6:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 7:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 8:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }

        }

    }
    else
    {
        // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
        //                                                                                                                             "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        switch (index) {
        case 1:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 2:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 3:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 4:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 5:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 6:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 7:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 8:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }

        }
    }


    //Сигнал завершения проверки
    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();

    //Сигнал выключения питания приемника по окончанию проверки
    emit setOutput(QString::number(index),false);



    //Остановка потока для того чтоб дождаться остальные приемники для перехода на следующую првоерку
    sem->acquire();


    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_3();
    }

}
//**********************************************************************************


//**********************************************************************************
//3.	Проверка работоспособности приемника на воздействие повышенного напряжения питания
void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_3()
{
    // Подсчет проверок
    countProverka = 3;  //№3

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    //Cигнал для установки напряжения на источнике питания на том блоке к которому подсоединен приемник
    emit setVolt(QString::number(index),"5.25");
    //Подача питания на приемник
    emit setOutput(QString::number(index),true);
    //Флаг работы, приемник включен
    job = true;
    //Очитска листа с результатоми этапов 2 проверки по разным напряжениями питания
    list_flag_good_3.clear();
    //Сигнал начала запуска таймера для проверки (3.30 минут)
    emit startWork();
    qDebug () << "Запустили 3 проверку";
    //Время начала проверки для записи в БД
    stay = QDateTime::currentDateTime();
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    qDebug () << "Проверка Начата  3 часть 1 ждем = " << sem->available();
    //Проверка 3 часть 1
    proverka2_part = 1;
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
    sem->acquire();
    //По окончанию работы проверки переводим флаг работы в ложь, для показания того, что приемник прошел проверку и может быть выключен
    job = false;
    qDebug () << "Проверка 3 часть 1 Прошла = " << sem->available();
    //Флаг показывающий прошел ли приемник данную проверку или нет
    flag_good_3 = Good;
    //Добавление результата в лист
    list_flag_good_3.append(flag_good_3);

    if(flag_good_3)
    {
        //  gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
        //                                                                                                                             "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        switch (index) {
        case 1:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 2:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 3:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 4:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 5:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 6:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 7:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 8:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }

        }

    }
    else
    {
        // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
        //                                                                                                                             "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        switch (index) {
        case 1:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 2:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 3:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 4:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 5:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_1+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 6:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_2+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 7:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_3+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 8:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+n6700->n6700->v_4+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }

        }

    }

    //Сигнал выключения питания приемника по окончанию проверки
    emit setOutput(QString::number(index),false);
    //Сигнал завершения проверки
    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();



    //Остановка потока для того чтоб дождаться остальные приемники для перехода на следующую првоерку
    sem->acquire();

    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_4();
    }

}
//**********************************************************************************


//**********************************************************************************
//4.	Проверка мощности, потребляемой приемником от источника постоянного тока
void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_4()
{
    // Подсчет проверок
    countProverka = 4;  //№4

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    //Cигнал для установки напряжения на источнике питания на том блоке к которому подсоединен приемник
    emit setVolt(QString::number(index),"5");
    //Подача питания на приемник
    emit setOutput(QString::number(index),true);
    //Флаг работы, приемник включен
    job = true;
    //Время начала проверки для записи в БД
    stay = QDateTime::currentDateTime();
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Сигнал начала запуска таймера для проверки (3.30 минут)
    emit startWork();
    qDebug () << "Запустили 4 проверку";
    qDebug () << "Проверка Начата  4 = " << sem->available();
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
    sem->acquire();
    //По окончанию работы проверки переводим флаг работы в ложь, для показания того, что приемник прошел проверку и может быть выключен
    job = false;
    qDebug () << "Проверка 4  Прошла = " << sem->available();
    //Флаг показывающий прошел ли приемник данную проверку или нет
    flag_good_4 = Good;

    if(flag_good_4)
    {
        //gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
        //                                                                                                                            "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        switch (index) {
        case 1:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_1.toDouble()*n6700->n6700->i_1.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 2:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_2.toDouble()*n6700->n6700->i_2.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 3:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_3.toDouble()*n6700->n6700->i_3.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 4:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_4.toDouble()*n6700->n6700->i_4.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 5:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_1.toDouble()*n6700->n6700->i_1.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 6:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_2.toDouble()*n6700->n6700->i_2.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 7:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_3.toDouble()*n6700->n6700->i_3.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 8:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_4.toDouble()*n6700->n6700->i_4.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }

        }

    }
    else
    {
        // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
        //                                                                                                                             "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        switch (index) {
        case 1:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_1.toDouble()*n6700->n6700->i_1.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 2:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_2.toDouble()*n6700->n6700->i_2.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 3:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_3.toDouble()*n6700->n6700->i_3.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 4:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_4.toDouble()*n6700->n6700->i_4.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 5:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_1.toDouble()*n6700->n6700->i_1.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 6:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_2.toDouble()*n6700->n6700->i_2.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 7:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_3.toDouble()*n6700->n6700->i_3.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }
        case 8:
        {
            gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                        "Sootv = '"+QString::number(n6700->n6700->v_4.toDouble()*n6700->n6700->i_4.toDouble(),NULL,3)+" Вт'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
            break;
        }

        }
    }

    //Сигнал выключения питания приемника по окончанию проверки
    emit setOutput(QString::number(index),false);
    //Сигнал завершения проверки
    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();



    //Остановка потока для того чтоб дождаться остальные приемники для перехода на следующую првоерку
    sem->acquire();

    if(flag_auto)
    {
       // proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_6();
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_5();
    }

}
//**********************************************************************************


//**********************************************************************************
//5.	Проверка поиска, захвата и сопровождения сигнала с уровнем мощности минус 160 дБВт(-130 dBm)
void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_5()
{
    // Подсчет проверок
    countProverka = 5;  //№5

    // остановка чтоб дождаться сброса пульта
    sem->acquire();


    emit signal_StartProverkaIndex(QString::number(countProverka));
    //Cигнал на запуск имитации 1 спутника на имитаторе
    emit signal_startGen();
    qDebug () << "Запустили 5 проверку";
    //Время начала проверки для записи в БД
    stay = QDateTime::currentDateTime();
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Часть проверки (зануление, инициализация)
    proverka5_part = 0;
    //Отчистка листа результатов для данной проверки
    list_flag_good_5.clear();

    //Семафор для остановки потока для того чтоб подождать пока не запуститься имитатор
    sem->acquire();


    //Цикол для проверки чувствительности по ГЛОНАСС установка литер от -7 до 0 и проверка их
    for(int i = 26; i <= 151;i++) //убрал G24 так как на имитаторе не ставится. (151)  26
    {

        qDebug() << "First:  I = " << i << " Litrea = " << liter;
        //Добавление части проверки
        proverka5_part++;
        //Установка литеры
        liter = i;

        qDebug() << "Second: I = " <<    i << " Litrea = " << liter;

        if(i == 39)
        {
            //Перевод на GPS
            i = 129;
            liter = i;
        }
        else
        {
            //Глонасс
            liter = i;
        }

        //Подача питания на приемник
        emit setOutput(QString::number(index),true);
        //Флаг работы, приемник включен
        job = true;
        //Сигнал начала запуска таймера для проверки (3.30 минут)
        emit startWork_liters();
        qDebug () << "Проверка Начата  5: литера № " << (i-32);
        //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
        sem->acquire();
        //По окончанию работы проверки переводим флаг работы в ложь, для показания того, что приемник прошел проверку и может быть выключен
        job = false;
        qDebug () << "Проверка 5: литера № "  << (i-32);
        //Флаг показывающий прошел ли приемник данную проверку или нет
        flag_good_5 = Good;
        //Добавление результата в лист
        list_flag_good_5.append(flag_good_5);
        qDebug () <<" Finish = " << this->Name << "Id: " << Id << " Date_Stay = " << stay_liter.toString("dd.MM.yyyy  hh:mm:ss");

        if(flag_good_5)
        {
            gsg->BD->zaprosQueryModel("UPDATE Liter SET Sootv = 'Соответствует'"
                                      " WHERE Date = '"+stay_liter.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
        }
        else
        {
            gsg->BD->zaprosQueryModel("UPDATE Liter SET Sootv = 'Не соответствует'"
                                      " WHERE Date = '"+stay_liter.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
        }

        //Сигнал выключения питания приемника по окончанию проверки
        emit setOutput(QString::number(index),false);
        //Сигнал завершения проверки
        emit signal_EndProverka(countProverka);
        qDebug () << "Ждем остальные приемники = " << sem->available();
        //Остановка потока для того чтоб дождаться остальные приемники для перехода на следующую првоерку

        qDebug () << "Нп = " << index << " Count_NP =" << Count_NP;
        sem->acquire();

        /*
        if(flag_good_5 == false)
        {
            for(int i=1; i <= Count_NP; i++)
            {
                qDebug () << "Нп = " << index << " Count_NP =" << Count_NP << "i = " << i;
                sem->acquire();
            }
        }
        else
        {
            qDebug () << "Нашли спутники";
             sem->acquire();
        }   */



    }

    qDebug () << "Конец проверки на литеры = " << sem->available() << "data: " << stay_liter.toString("dd.MM.yyyy  hh:mm:ss");



    QSqlQueryModel* SQL_sootv;

    SQL_sootv = gsg->BD->zaprosQueryModel("SELECT Sootv,Id FROM Liter WHERE Sootv LIKE 'Не соответствует' AND  IdLink LIKE '"+IdLink+"' ");

    if(SQL_sootv->rowCount() > 0)
    {
        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
    }
    else
    {
        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
    }

    emit signal_IndexProverka(QString::number(countProverka));




    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_6();
    }

}



void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_6()
{


    countProverka = 6; //№6

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    //Флаг работы, приемник включен
    job = true;

    if(index == 1)
    {
        this->thread()->msleep(10);
    }
    emit signal_beginOSProv(index);

    sem->acquire();


    gsg->os->os->flag_change_seitings = true;

    gsg->os->slot_Change_Seitings();

    gsg->tp->index = index;
    gsg->tp->slot_comand7_Set_zatyxanie_10(0x9B);
    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand6_Connect_Vx2_10_ext();
    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand5_Connect_10MG(0x01,true); //(*QString::number(index).toUtf8().data()-0x30);


//    gsg->tp->index = index;
//    gsg->tp->slot_comand1_Connect_Vx2_10(*QString::number(index).toUtf8().data()-0x30);

//    sem->acquire();






    for(int i=0x9B; i > 0; i--)
    {

        qDebug() << (UINT)i;

        gsg->tp->index = index;
        gsg->tp->slot_comand7_Set_zatyxanie_10(i);
        sem->acquire();

        // this->thread()->sleep(1);

        QString VMAX = gsg->os->os->getVRMS("CHANnel2");


        qDebug () <<"VMAX = " << VMAX;

        qDebug () <<"VMAX.toDouble() = " << VMAX.toDouble();

        if(VMAX.toDouble() >= 0.2 &&  VMAX.toDouble() <= 0.3 ) //мили вольты
        {
            flag_good_6 = true;

            qDebug () <<"[VMAX.toDouble() >= 0.2 &&  VMAX.toDouble() <= 0.3  ] = " << flag_good_6;

            break;

        }
        else
        {
            flag_good_6 = false;

            if(( VMAX.toDouble() > 0.3 ) || (VMAX.toDouble() == 0) )
            {
                break;
            }

        }
    }


    gsg->tp->index = index;
    gsg->tp->slot_comand8_Connect_10_in(0x01);
    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand3_Connect_Vx2_1C(); //(*QString::number(index).toUtf8().data()-0x30);
    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand5_Connect_10MG(*QString::number(index).toUtf8().data()-0x30,false);
    sem->acquire();

    //Cигнал для установки напряжения на источнике питания на том блоке к которому подсоединен приемник
    emit setVolt(QString::number(index),"5");

    this->thread()->msleep(50);

    //Подача питания на приемник
    emit setOutput(QString::number(index),true);

    this->thread()->msleep(50);

    emit signal_startImitator();

    this->thread()->msleep(50);

    emit signal_StartProverkaIndex(QString::number(countProverka));

    this->thread()->msleep(10);




    stay = QDateTime::currentDateTime();
    qDebug () << "Проверка 6 Начата  ждем";
    qDebug () << "Дата старта: " << start.toString("dd.MM.yyyy  hh:mm:ss");
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)


    //Сигнал начала запуска таймера для проверки (3.30 минут)
    emit startWork();
    qDebug () << "Запустили 6 проверку";
    qDebug () << "Проверка Начата 6 = " << sem->available();
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
    sem->acquire();
    //По окончанию работы проверки переводим флаг работы в ложь, для показания того, что приемник прошел проверку и может быть выключен
    job = false;
    qDebug () << "Проверка 6  Прошла = " << sem->available();
    //Флаг показывающий прошел ли приемник данную проверку или нет



    flag_good_6 = Good;




    if(flag_good_6)
    {
        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
    }
    else
    {
        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");
    }

    //Сигнал выключения питания приемника по окончанию проверки
    emit setOutput(QString::number(index),false);

    gsg->tp->index = index;
    gsg->tp->slot_comand8_Connect_10_in(*QString::number(index).toUtf8().data()-0x30);
    sem->acquire();


    //Сигнал завершения проверки
    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();
    //Остановка потока для того чтоб дождаться остальные приемники для перехода на следующую првоерку

    emit signal_slot_StartProverka_Os(index);
    sem->acquire();

    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_7();
    }

}


//Проверка 10 МГЦ
void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_7()
{
    countProverka = 7;  //№7

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    //запускаем приемник (падали ток)
    emit setOutput(QString::number(index),true);

    job = true;

    emit startWork_Os();

    emit signal_start_10Proverka(index);
    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand8_Connect_10_in(*QString::number(index).toUtf8().data()-0x30);

    sem->acquire();

    emit signal_slot_StartProverka_Os(index);
    sem->acquire();

    qDebug () << "Запустили 7 проверку";

    stay = QDateTime::currentDateTime();
    qDebug () << "Проверка 7 Начата  ждем";
    qDebug () << "Дата старта: " << start.toString("dd.MM.yyyy  hh:mm:ss");
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");

    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)
    qDebug () << "Проверка Начата  7 = " << sem->available();

    sem->acquire();
    gsg->tp->index = index;
    emit signal_start_10Proverka(index);
    sem->acquire();

    gsg->os->os->flag_change_seitings = true;
    gsg->os->slot_Change_Seitings();

    job = false;

    qDebug () << "Номер НП = " << *QString::number(index).toUtf8().data();

    gsg->tp->index = index;
    gsg->tp->slot_comand2_Connect_Vx1_1C(*QString::number(index).toUtf8().data()-0x30);

    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand1_Connect_Vx2_10(*QString::number(index).toUtf8().data()-0x30);

    sem->acquire();


    QString VMAX = gsg->os->os->getVMAX("CHANnel2");

    qDebug () <<"VMAX = " << VMAX;

    qDebug () <<"VMAX.toDouble() = " << VMAX.toDouble();

    if(VMAX.toDouble() >= 0.2  && VMAX.toDouble() <= 0.3  ) //мили вольты
    {
        flag_good_7 = true;

        qDebug () <<"[VMAX.toDouble() >= 0.2  && VMAX.toDouble() <= 0.3 ] = " << flag_good_7;

    }
    else
    {
        flag_good_7 = false;

        qDebug () <<"[VMAX.toDouble() >= 0.2  && VMAX.toDouble() <= 0.3 ] = " << flag_good_7;
    }


    if(flag_good_7)
    {
        // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
        //                                                                                                                             "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");


        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(VMAX.toDouble()*100)+" мВ'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

    }
    else
    {
       // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
       //                                                                                                                             "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(VMAX.toDouble()*100)+" мВ'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

    }


    qDebug () << "Проверка 7  Прошла = " << sem->available();

    emit setOutput(QString::number(index),false);



    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();




    emit signal_slot_StartProverka_Os(index);
    sem->acquire();

    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_8();
    }

}

void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_8()
{
    countProverka = 8;  //№8

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    //запускаем приемник (падали ток)
    emit setOutput(QString::number(index),true);
    job = true;

    //  emit startWork();



    emit startWork_Os();

    qDebug () << "Запустили 8 проверку";

    stay = QDateTime::currentDateTime();
    qDebug () << "Проверка 7 Начата  ждем";
    qDebug () << "Дата старта: " << start.toString("dd.MM.yyyy  hh:mm:ss");
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)

    qDebug () << "Проверка Начата  8 = " << sem->available();

    sem->acquire();
    emit signal_start_10Proverka(index);
    sem->acquire();

    gsg->os->os->flag_change_seitings = false;
    gsg->os->slot_Change_Seitings();
    job = false;

    gsg->tp->index = index;
    gsg->tp->slot_comand2_Connect_Vx1_1C(*QString::number(index).toUtf8().data()-0x30);

    sem->acquire();

    // Sleep(1000);


    QString Amplituda = gsg->os->os->getAmplitude();

    // Amplituda = gsg->os->os->getAmplitude();

    qDebug () <<"Amplituda = " << Amplituda;

    qDebug () <<"Amplituda.toDouble() = " << Amplituda.toDouble();

    if(Amplituda.toDouble() >= 2.4 )
    {
        flag_good_8 = true;
    }
    else
    {
        flag_good_8 = false;
    }



    if(flag_good_8)
    {
       // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
       //                                                                                                                             "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(Amplituda.toDouble())+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");


    }
    else
    {
       // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
       //                                                                                                                             "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(Amplituda.toDouble())+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");


    }


    qDebug () << "Проверка 8  Прошла = " << sem->available();



    // Sleep(1000);






    emit setOutput(QString::number(index),false);

    emit signal_EndProverka(countProverka);
    qDebug () << "Ждем остальные приемники = " << sem->available();



    emit signal_slot_StartProverka_Os(index);
    sem->acquire();





    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_9();
    }

}

//9.	Проверка напряжения питания МШУ (нет в ПМ)
void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_9()
{
    countProverka = 9;  //№9

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    //запускаем приемник (падали ток)
    emit setOutput(QString::number(index),true);

    gsg->os->os->flag_change_seitings_3 = false;
    gsg->os->slot_Change_Seitings3();


    job = true;

    // Sleep(10000); // Ждем 10 секунд

    qDebug () << "Запустили 9 проверку";

    stay = QDateTime::currentDateTime();
    qDebug () << "Проверка 7 Начата  ждем";
    qDebug () << "Дата старта: " << start.toString("dd.MM.yyyy  hh:mm:ss");
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)

    emit signal_start_10Proverka(index);

    sem->acquire();

    gsg->tp->index = index;
    gsg->tp->slot_comand4_Connect_Vx1_MShY(*QString::number(index).toUtf8().data()-0x30);

    sem->acquire();

    //  Sleep(5000);

    //Отправить на пульт команду
    //Отправить на пульт команду 0401 (где младший байт – номер приемника в соответствии с приложением 3)

    QString Amplituda = gsg->os->os->getVMAX("CHANnel1");

    qDebug () <<"Amplituda = " << Amplituda;

    qDebug () <<"Amplituda.toDouble() = " << Amplituda.toDouble();

    job = false;

    if(Amplituda.toDouble() <= 5.25 && Amplituda.toDouble() >= 4.75 )
    {
        flag_good_9 = true;
    }
    else
    {
        flag_good_9 = false;
    }

    emit signal_EndProverka(countProverka);

    if(flag_good_9)
    {
      //  gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
      //                                                                                                                              "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(Amplituda.toDouble())+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

    }
    else
    {
      //  gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
      //                                                                                                                              "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(Amplituda.toDouble())+" В'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

    }

   // Sleep(5000); // Ждем 5 секунд

    emit signal_slot_StartProverka_Os(index);


    sem->acquire();

    emit setOutput(QString::number(index),false);


    if(flag_auto)
    {
        proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_10();
    }
}

void RelizProverka::proverka_rabotosposobnosti_Ponijennoe_naprRjenie_NP_ID_10()
{

    countProverka = 10;  //№10

    // остановка чтоб дождаться сброса пульта
    sem->acquire();

    emit signal_StartProverkaIndex(QString::number(countProverka));
    emit signal_startImitator();

    //запускаем приемник (падали ток)
    emit setOutput(QString::number(index),true);

    job = true;

    //  emit startWork();

    emit startWork_Os();

    qDebug () << "Запустили 10 проверку";

    stay = QDateTime::currentDateTime();

    qDebug () << "Проверка 10 Начата  ждем";
    qDebug () << "Дата старта: " << start.toString("dd.MM.yyyy  hh:mm:ss");
    //Запись в БД начала проверки
    gsg->BD->zaprosQueryModel("INSERT INTO Result (DateStayStart,IdLink,IdProverki) VALUES('"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"','"+IdLink+"','"+QString::number(countProverka)+"')");
    //Семафор для остановки потока проверок для того чтоб подождать пока не найдутся спутники (не выполнится сама проверка)


    qDebug () << "Проверка 10 Начата   = " << sem->available();



    sem->acquire();




    emit signal_start_10Proverka(index);

    sem->acquire();

    gsg->os->os->flag_change_seitings_3 = false;
    gsg->os->slot_Change_Seitings3();
    job = false;


    gsg->tp->index = index;
    gsg->tp->slot_comand2_Connect_Vx1_1C(*QString::number(index).toUtf8().data()-0x30);

    sem->acquire();


    QString Amplituda = gsg->os->os->getDelay();


    qDebug () <<"Amplituda = " << Amplituda;

    qDebug () <<"Amplituda.toDouble() = " << Amplituda.toDouble();

    qDebug () <<"Amplituda.toDouble() = " << Amplituda.toDouble()*(-1);

    qDebug () <<"Amplituda.toDouble() = " << 1*exp(-6);

    if(Amplituda.toDouble() <= 1*exp(-6) )
    {
        flag_good_10 = true;
    }
    else
    {
        flag_good_10 = false;
    }


    if(flag_good_10)
    {
       // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
       //                                                                                                                             "Sootv = 'Соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(Amplituda.toDouble()*100)+" мс'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");


    }
    else
    {
       // gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
       //                                                                                                                             "Sootv = 'Не соответствует'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");

        gsg->BD->zaprosQueryModel("UPDATE Result SET DateStayEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"', "
                                                                                                                                    "Sootv = '"+QString::number(Amplituda.toDouble()*100)+" мс'  WHERE DateStayStart = '"+stay.toString("dd.MM.yyyy  hh:mm:ss")+"' AND IdLink = '"+IdLink+"'");


    }

    qDebug () << "Проверка 10  Прошла = " << sem->available() << " Флаг : " << flag_good_10;



    qDebug () << "DateStart = " << start.toString("dd.MM.yyyy  hh:mm:ss");

    gsg->BD->zaprosQueryModel("UPDATE DateStartEnd SET DateEnd = '"+QDateTime::currentDateTime().toString("dd.MM.yyyy  hh:mm:ss")+"'"
                                                                                                                                  " WHERE DateStart = '"+start.toString("dd.MM.yyyy  hh:mm:ss")+"'");

    qDebug () << "Конец = " << sem->available();

    emit signal_slot_StartProverka_Os(index);

    sem->acquire();

    emit setOutput(QString::number(index),false);



    emit signal_EndProverka(countProverka);
}


void RelizProverka::Work(bool auto_test, int proverka)
{
    qDebug () << "RelizProverka";




    flag_auto = auto_test;

    if(auto_test)
    {
        sem->acquire();
        emit signal_StartProverka_1();
    }
    else
    {
        switch (proverka)
        {
        case 1:emit signal_StartProverka_1(); break;
        case 2:emit signal_StartProverka_2(); break;
        case 3:emit signal_StartProverka_3(); break;
        case 4:emit signal_StartProverka_4(); break;
        case 5:emit signal_StartProverka_5(); break;
        case 6:
        {
            emit signal_StartProverka_6(); break;
        }
        case 7:emit signal_StartProverka_7(); break;
        case 8:emit signal_StartProverka_8(); break;
        case 9:emit signal_StartProverka_9(); break;
        case 10:emit signal_StartProverka_10(); break;

        }
    }


}

