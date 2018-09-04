#ifndef TP8_H
#define TP8_H

#include <QObject>

#include <QtNetwork>

#pragma pack(push,1)
struct find
{
    char bigBayt;
    char smolBayt;
    char mod;
    char ipTP[4];
    char ipServer[4];
    short int portServer;
    short int portTp;
    char nameTP[20];
    char NumberTP[6];
    char Version[6];

};
#pragma pack(pop)


#pragma pack(push, 1)
struct Otvet
{
    char KodSend;
    char Argyment;
    char mod;

};
#pragma pack(pop)


/*!
    \brief Класс пульта ТП8 для навигационных плат НП101
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данный класс создан для управления технологическим пультом ТП8

    Данный класс имеет набор свойств и методов для управления пультом
 ТП8 в котором находится 8 навигационных плат НП101, который отнаследован от QObject

*/
class TP8 : public QObject
{
    Q_OBJECT

public:
    explicit TP8(QObject *parent = 0);

    int index;

    //  Q_PROPERTY(QList<QObject*> listDevice READ listDevice NOTIFY ListDeviceChanged)


    bool flagClear;

    QUdpSocket *udpsocket;

    find *otvet_first;

    Otvet *otvet;

    QList<find> listTP;

    QString ipTP;
    QString locIP;

    QByteArray perevod( QByteArray datagram);

signals:
    void signal_Ok(bool good);

    void signal_comandaClear_ok();

    void signal_comanda1_ok(int index);
    void signal_comanda2_ok(int index);
    void signal_comanda3_ok(int index);
    void signal_comanda4_ok(int index);
    void signal_comanda5_ok(int index);

    void signal_comanda6_ok(int index);

    void signal_comanda7_ok(int index);

    void signal_comanda8_ok(int index);

public slots:
    void readPendingDatagrams();

    void slot_findTp();

    void slot_ConnectTp(QString ip);

    //Подключение к «ВЫХОД2» сигнала 10МГц с НП1-НП8
    void slot_comand1_Connect_Vx2_10(char NP);

    //Подключение к «ВЫХОД1» сигнала 1С с НП1-НП8
    void slot_comand2_Connect_Vx1_1C(char NP);

    //Подключение к «ВЫХОД2» сигнала 1С с внешнего источника (имитатора)
    void slot_comand3_Connect_Vx2_1C();

    //Подключение к «ВЫХОД1» входа НП1-НП8 для проверки уровня напряжения питания МШУ
    void slot_comand4_Connect_Vx1_MShY(char NP);

    //Подключение внешнего источника 10МГц к НП1-НП8
    void slot_comand5_Connect_10MG(char NP,bool _flagClear);

    //Подключение к «ВЫХОД2» внешнего источника 10МГц (для контроля уровня сигнала внешнего источника 10 МГц)
    void slot_comand6_Connect_Vx2_10_ext();

    //Установка уровня затухания внешнего источника 10 МГц в дБ (0-38,75 шаг 0,25)
    void slot_comand7_Set_zatyxanie_10(char zatyx);

    void slot_comand8_Connect_10_in(char NP);

    void slot_clear();


    void process_start();




};

#endif // TP8_H
