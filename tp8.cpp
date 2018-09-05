#include "tp8.h"

#include <QThread>

/*!
    \brief Конструктор класса ТП8


   Контструктор класса ТП8 , инициализирует новый поток ( QThread ) и запускает его, выполняя функцию process_start().

    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Перемещение класса в новый поток
*/
TP8::TP8(QObject *parent) : QObject(parent),
    index(-1)
{

    this->moveToThread(new QThread()); //Переместили класс TP8 в новый поток

    QObject::connect(this->thread(),&QThread::started,this,&TP8::process_start);
    this->thread()->start();


}

/*!
    \brief Функция для переворачивания байты порта.

    \param[in]  QByteArray datagram
    \return QByteArray datagram с перевернутыми данными внутри на 11,12,13,14 позициях

   Функция принимает прочитанную датаграмму от пульта и переворачивает баты порта для того чтобы корректно отправить ответ\n
   Возвращает QByteArray (массив байт) с перевернутым портом в послыке принятия и отправки.

    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Плохо сделанная прошивка в пульте поэтому есть такой Кастыль. Притензии к Глушкову Антону.
*/
QByteArray TP8::perevod( QByteArray datagram)
{
    char tmp = datagram[11];
    datagram[11] = datagram[12];
    datagram[12] = tmp;

    tmp = datagram[13];
    datagram[13] = datagram[14];
    datagram[14] = tmp;


    return datagram;


}

/*!
    \brief Слот для чтения посылки от пульта ТП8 и принятие решения какую посылку отправить в ответ


   Функция читает посылку от пульта ТП8 и принятие решения какую посылку отправить в ответ.\n
   Пишет в Debug принята ли команда и выполненна ли.

    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::readPendingDatagrams()
{

    while (udpsocket->hasPendingDatagrams())
    {


        QByteArray datagram;



        datagram.resize(udpsocket->pendingDatagramSize());
        QHostAddress* sender = new QHostAddress();
        quint16* senderPort = new quint16();

        udpsocket->readDatagram(datagram.data(), datagram.size(),sender, senderPort);


        switch (datagram[0])
        {

        case 0x1C: {
            datagram = perevod(datagram);
            otvet_first = (find*)datagram.data();

            //запишим найденный IP в переменную (на всякий случай)
            ipTP = QString::number(otvet_first->ipTP[0]&0xFF) + "." +
                    QString::number(otvet_first->ipTP[1]&0xFF) + "." +
                    QString::number(otvet_first->ipTP[2]&0xFF) + "." +
                    QString::number(otvet_first->ipTP[3]&0xFF);


            listTP.append(*otvet_first);

            QByteArray byte_ip;

            QStringList locIP_split = locIP.split('.');

            for(int i=0;i < locIP_split.count();i++)
            {
                byte_ip.append(locIP_split[i].toInt());

            }

            bool flag = false;


            if(otvet_first->mod == static_cast<char>(0x09))
            {
                qDebug () << "Пульт свободен . Clear Tp8";
                break;
            }
            else
            {
                qDebug () << "Пульт занят . Close Tp8";


                for(int i=0;i < byte_ip.count();i++)
                {
                    if(otvet_first->ipServer[i] == byte_ip[i])
                    {
                        flag = true;
                    }
                    else
                    {
                        flag = false;
                    }
                }



            }


            if(flag)
            {
                emit signal_Ok(true);
            }
            else
            {
                emit signal_Ok(false);
            }

            break;
        }

        case char(0xFB):{
            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0xFB на сброс принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] == static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0xFB на сброс выполнена";

                    emit signal_comandaClear_ok();
                }
            }
            break;
        }
        case 0x01: {

            if(datagram[2] ==  static_cast<char>(0x01))
            {
                qDebug () << "Команда 0x01 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] == static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x01 выполнена";

                    emit signal_comanda1_ok(index);

                }
            }


            break;
        }

        case 0x02: {

            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x02 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] ==  char(0x03))
                {
                    qDebug () << "Команда 0x02 выполнена";

                    qDebug () << "TP8 NP = " << index;
                    emit signal_comanda2_ok(index);

                }
            }


            break;
        }
        case 0x03: {

            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x03 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] ==  static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x03 выполнена";

                    emit signal_comanda3_ok(index);

                }
            }


            break;
        }
        case 0x04: {
            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x04 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] ==  static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x04 выполнена";

                    emit signal_comanda4_ok(index);

                }
            }

            break;
        }
        case 0x05: {
            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x05 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] ==  static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x05 выполнена";
                    emit signal_comanda5_ok(index);
                }
            }

            break;
        }
        case 0x06: {
            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x06 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] == static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x06 выполнена";

                    emit signal_comanda6_ok(index);
                }
            }

            break;
        }
        case 0x07: {
            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x07 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] ==  static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x07 выполнена";

                    emit signal_comanda7_ok(index);

                }
            }

            break;
        }
        case 0x08: {
            if(datagram[2] ==  static_cast<char>(0x02))
            {
                qDebug () << "Команда 0x08 принята";
                otvet = (Otvet*)datagram.data();
            }
            else
            {
                if(datagram[2] ==  static_cast<char>(0x03))
                {
                    qDebug () << "Команда 0x08 выполнена";

                    emit signal_comanda8_ok(index);

                }
            }

            break;
        }


        }


    }

}

/*!
    \brief Слот для поиска ТП8 для получения IP адреса по которому подключится ПК

   Функция отправляет широковещательный UDP запрос (Broadcast)\n
   Порт отправки: 6683
   Состав посылки:\n
   1C\n
   1C\n
   01\n
   байты IP адреса\n
   2 байта порта пульта\n
   2 байта порта ПК\n
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_findTp()
{
    listTP.clear();

    QByteArray b;
    QByteArray byte_ip;

    QStringList locIP_split;


    locIP_split = locIP.split('.');


    for(int i=0;i < locIP_split.count();i++)
    {
        byte_ip.append(static_cast<char>(locIP_split[i].toInt()));
    }


    b.append(0x1C);
    b.append(0x1C);
    b.append(0x01);
    //Ip
    for(int i=0;i < locIP_split.count();i++)
    {
        b.append(byte_ip[i]);
    }

    // Первый - порт пульта Второй - порт сервера
    b.append(static_cast<char>(0xFF));
    b.append(static_cast<char>(0xDC));
    b.append(static_cast<char>(0xFF));
    b.append(static_cast<char>(0xE6));

    udpsocket->writeDatagram(b,b.count(),QHostAddress::Broadcast,6683);
}

/*!
    \brief Слот для подключения ТП8 к ПК
    \param[in] QString ip Ip адресс пульта ТП8

   Функция принимает IP адресс прибора ТП8 для его подключения к ПК\n
   Порт отправки: 6683
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_ConnectTp(QString ip)
{
    listTP.clear();

    ipTP = ip;

    QStringList locIP_split;
    QByteArray b;
    QByteArray byte_ip;



    locIP_split = locIP.split('.');


    for(int i=0;i < locIP_split.count();i++)
    {
        byte_ip.append(static_cast<char>(locIP_split[i].toInt())); //проверить
    }


    b.append(static_cast<char>(0x1C));
    b.append(static_cast<char>(0x1C));
    b.append(static_cast<char>(0x03));
    //Ip
    for(int i=0;i < locIP_split.count();i++)
    {
        b.append(byte_ip[i]);
    }

    b.append(static_cast<char>(0xFF));
    b.append(static_cast<char>(0xDC));
    b.append(static_cast<char>(0xFF));
    b.append(static_cast<char>(0xE6));

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),6683);

    index = -1;

    for(int i=0x01; i <= 0x08;i++)
    {
        //  slot_comand8_Connect_10_in(i);

        // slot_comand1_Connect_Vx2_10(i);
    }

}

/*!
    \brief Слот для выполняения 1 команды
    \param[in] char NP байт номера навигационного приемника в пульте ТП8 к которому применить команду

   Подключение к «ВЫХОД2» сигнала 10МГц с НП1-НП8\n
   Здесь младший байт — это номер НП с которого осуществляется подключение сигнала 10 МГц на «ВЫХОД2»\n
   Младший байт: 01-08.\n
   Порт отправки: 65500
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand1_Connect_Vx2_10(char NP)
{
    QByteArray b;

    b.append(0x01);
    b.append(NP);
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 2 команды
    \param[in] char NP байт номера навигационного приемника в пульте ТП8 к которому применить команду

   Подключение к «ВЫХОД1» сигнала 1С с НП1-НП8\n
   Здесь младший байт — это номер НП с которого осуществляется подключение сигнала 1С на «ВЫХОД1»\n
   Младший байт: 01-08.
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand2_Connect_Vx1_1C(char NP)
{
    QByteArray b;

    b.append(0x02);
    b.append(NP);
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 3 команды

   Подключение к «ВЫХОД2» сигнала 1С с внешнего источника (имитатора)\n
   Здесь младший байт не имеет значения\n
   Младший байт: 00.\n
   Порт отправки: 65500

    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand3_Connect_Vx2_1C()
{
    QByteArray b;

    b.append(0x03);
    b.append('\0');
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 4 команды
    \param[in] char NP байт номера навигационного приемника в пульте ТП8 к которому применить команду

   Подключение к «ВЫХОД1» входа НП1-НП8 для проверки уровня напряжения питания МШУ\n
   Здесь младший байт — это номер НП с которого осуществляется измерение напряжения питания МШУ на выходе «ВЫХОД1»\n
   Младший байт: 01-08.\n
   Порт отправки: 65500
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand4_Connect_Vx1_MShY(char NP)
{
    QByteArray b;

    b.append(0x04);
    b.append(NP);
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 5 команды
    \param[in] char NP байт номера навигационного приемника в пульте ТП8 к которому применить команду

   Подключение внешнего источника 10МГц к НП1-НП8\n
   Здесь младший байт — это номер НП к которому подключается сигнал 10 МГц с внешнего источника\n
   Младший байт: 01-08.\n
   Порт отправки: 65500
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand5_Connect_10MG(char NP,bool _flagClear)
{

    // flagClear = false;

    QByteArray b;

    b.append(0x05);
    b.append(NP);
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 6 команды

   Подключение к «ВЫХОД2» внешнего источника 10МГц (для контроля уровня сигнала внешнего источника 10 МГц)\n
   Здесь младший байт не имеет значения.\n
   Младший байт: 00.\n
   Порт отправки: 65500
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand6_Connect_Vx2_10_ext()
{
    QByteArray b;

    b.append(0x06);
    b.append('\0');
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 7 команды
    \param[in] char zatyx байт затухания

   Установка уровня затухания внешнего источника 10 МГц в дБ (0-38,75 шаг 0,25).\n
   Здесь младший байт — это номер от 0 до 155 соответствующий уровню затухания от 0 до 38,75дБ с шагом 0,25. Эта величина определяется по формуле Х/0,25, где Х величина затухания в дБ с шагом 0,25дБ (На пример 01- затухание 0,25дБ, 02- затухание 0,5дБ, 3С- затухание 15 дБ, 9B затухание38,75 дБ.\n
   Младший байт: 00-9B.\n
   Порт отправки: 65500
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand7_Set_zatyxanie_10(char zatyx)
{
    QByteArray b;

    b.append(0x07);
    b.append(zatyx);
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Слот для выполняения 8 команды
    \param[in] char NP байт номера навигационного приемника в пульте ТП8 к которому применить команду

   Подключение внутреннего источника 10МГц к НП1-НП8.\n
   Здесь младший байт — это номер НП к которому подключается сигнал 10 МГц с внешнего источника.\n
   Младший байт: 01-08\n
   Порт отправки: 65500
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
    \warning Данная функция выполняется в отдельном потоке
*/
void TP8::slot_comand8_Connect_10_in(char NP)
{
    QByteArray b;

    b.append(0x08);
    b.append(NP);
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

void TP8::slot_clear()
{
    QByteArray b;

    b.append(0xfb);
    b.append('\0');
    b.append(0x01);

    udpsocket->writeDatagram(b,b.count(),QHostAddress(ipTP),65500);
}

/*!
    \brief Функция инициализации объекта ТП8 в новом потоке

    Данная функция выполняется в новом потке и находит все доступные Ip адреса на момент запуска программы.\n
    Открывает UDP сокет для чтения на 65510 порте.\n
    Стандартный IP пульта: 10.12.0.166.\n
    Устанавливает index = 1.

    \warning Данная функция выполняется в отдельном потоке
    \author Sergey Smoglyuk
    \version 1.0
    \date Август 2018 года
*/
void TP8::process_start()
{

    QList<QHostAddress> addr = QNetworkInterface::allAddresses();

    locIP = addr[0].toString();

    // locIP = addr.first().toString();

    udpsocket=new QUdpSocket();//соккет для чтения IP

    udpsocket->bind(QHostAddress(locIP),65510);

    connect(udpsocket, SIGNAL(readyRead()),this, SLOT(readPendingDatagrams()));

    ipTP = "10.12.0.166";

    index = 1;
}
