#include "proverkaitem.h"



proverkaItem::proverkaItem(int indexGet,N6700Model* n6700,
                           gsgModel* gsgModelGet,PortModel* port,
                           bool vnytrenGenGet, bool goodGet,QString GetName,screenCapture* screenClassGet, QObject *parent):
    QObject(parent),
    m_tok("-"),
    m_v("-"),
    m_power("-"),
    m_gpsGen("-"),
    m_glonassGen("-"),
    m_gpsFind("-"),
    m_glonassFind("-"),
    m_vnytrenGen(true),
    m_good(false),
    m_tick("Ждем запуска приемника"),
    m_indexProverki("0"),
    screenClass(screenClassGet)
{



    index = indexGet;
    n6700model = n6700;
    relizProverka = new RelizProverka(indexGet,n6700,gsgModelGet,port,GetName,screenClass);

    relizProverkaTimer = new relizproverkaTimer(indexGet,n6700,gsgModelGet,port,relizProverka);


    for(int i=0;i < 24;i++)
    {
        m_listSpytnik.append("0");
    }

    emit signal_listSpytnikChanged(m_listSpytnik);



    QObject::connect(gsgModelGet,&gsgModel::countSpytnik_R,this,&proverkaItem::getR);
    QObject::connect(gsgModelGet,&gsgModel::countSpytnik_G,this,&proverkaItem::getG);

    QObject::connect(n6700->n6700,&N6700::getMeasureCURRentSignal,this,&proverkaItem::slot_getMeasureCURRentSignal);
    QObject::connect(n6700->n6700,&N6700::getMeasureVoltSignal,this,&proverkaItem::slot_getMeasureVoltSignal);


    QObject::connect(port,&PortModel::UpdateCountFindQML,this,&proverkaItem::slot_getUpdateCountFindQML);

    QObject::connect(port->PortNew,&Port::signal_GoTORelizproverka,this,&proverkaItem::slot_setListSpytnik);


    QObject::connect(relizProverkaTimer,&relizproverkaTimer::signal_Tick,this,&proverkaItem::slot_Tick);

    QObject::connect(relizProverka,&RelizProverka::startWork,relizProverkaTimer,&relizproverkaTimer::Work);

    QObject::connect(relizProverka,&RelizProverka::startWork_liters,relizProverkaTimer,&relizproverkaTimer::Work_liters);
    QObject::connect(relizProverka,&RelizProverka::startWork_Os,relizProverkaTimer,&relizproverkaTimer::Work_Os);

    QObject::connect(relizProverka,&RelizProverka::signal_StopGSG,gsgModelGet,&gsgModel::slot_StopTimer);

    QObject::connect(relizProverkaTimer,&relizproverkaTimer::signal_GoodQML,this,&proverkaItem::slot_Good);


    QObject::connect(relizProverka,&RelizProverka::signal_IndexProverka,this,&proverkaItem::slot_IndexProverki);

    QObject::connect(this,&proverkaItem::powerChanged,relizProverkaTimer,&relizproverkaTimer::slot_Power);


    QObject::connect(relizProverkaTimer,&relizproverkaTimer::signal_GetMrk_OT,port->PortNew,&Port::GetMrk_OT);
    QObject::connect(relizProverkaTimer,&relizproverkaTimer::signal_GetMrk_liters,port->PortNew,&Port::GetMrk_liters);
    QObject::connect(relizProverkaTimer,&relizproverkaTimer::signal_GetMrk_liters_2,port->PortNew,&Port::GetMrk_liters_2);

    QObject::connect(relizProverka,&RelizProverka::signal_StartProverkaIndex,this,&proverkaItem::signal_StartProverkaIndex);


}

/////////////////////////////////////////////////////////////////////////////////

void proverkaItem::getR(int R)
{

    m_glonassGen = QString::number(R);

    glonassGenChanged(m_glonassGen);
}

void proverkaItem::getG(int G)
{
    m_gpsGen = QString::number(G);

    gpsGenChanged(m_gpsGen);
}



void proverkaItem::slot_getMeasureCURRentSignal(QVector<QString> list)
{
    get_tok.clear();

    for(int i=0; i < list.count();i++)
    {
        get_tok.append(list[i].split("\n").first());
    }
}

void proverkaItem::slot_getMeasureVoltSignal(QVector<QString> list)
{

    get_volt.clear();
    get_p.clear();

    for(int i=0; i < list.count();i++)
    {
        get_volt.append(list[i].split("\n").first());

        get_p.append(QString::number(get_tok.value(i).toDouble() * get_volt.value(i).toDouble()));
    }


    switch (index) {
    case 1:

        m_tok = QString::number(get_tok.value(0).toDouble(),NULL,3);
        m_v = QString::number(get_volt.value(0).toDouble(),NULL,3);
        m_power = QString::number(get_p.value(0).toDouble(),NULL,3);
        break;
    case 2:
        m_tok = QString::number(get_tok.value(1).toDouble(),NULL,3);
        m_v = QString::number(get_volt.value(1).toDouble(),NULL,3);
        m_power = QString::number(get_p.value(1).toDouble(),NULL,3);
        break;
    case 3:
        m_tok = QString::number(get_tok.value(2).toDouble(),NULL,3);
        m_v = QString::number(get_volt.value(2).toDouble(),NULL,3);
        m_power = QString::number(get_p.value(2).toDouble(),NULL,3);
        break;
    case 4:
        m_tok = QString::number(get_tok.value(3).toDouble(),NULL,3);
        m_v = QString::number(get_volt.value(3).toDouble(),NULL,3);
        m_power = QString::number(get_p.value(3).toDouble(),NULL,3);
        break;
    default:
        break;
    }

    emit tokChanged(m_tok);
    emit vChanged(m_v);
    emit powerChanged(m_power);

}

void proverkaItem::slot_getUpdateCountFindQML(int GLONASS, int GPS, int ALL)
{

    m_gpsFind = QString::number(GPS);
    m_glonassFind = QString::number(GLONASS);

    gpsFindChanged(m_gpsFind);
    glonassFindChanged(m_glonassFind);
}


////////////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::tok() const
{
    return m_tok;
}

void proverkaItem::setTok(const QString &tok)
{
    if(tok != m_tok)
    {
        m_tok = tok;
        emit tokChanged(m_tok);
    }
}

///////////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::v() const
{
    return m_v;
}

void proverkaItem::setV(const QString &v)
{
    if(v != m_v)
    {
        m_v = v;
        emit vChanged(m_v);
    }
}
///////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::power() const
{
    return m_power;
}

void proverkaItem::setPower(const QString &power)
{
    if(power != m_power)
    {
        m_power = power;
        emit powerChanged(m_power);
    }
}

///////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::gpsGen() const
{
    return m_gpsGen;
}

void proverkaItem::setGpsGen(const QString &gpsGen)
{
    if(gpsGen != m_gpsGen)
    {
        m_gpsGen = gpsGen;
        emit gpsGenChanged(m_gpsGen);
    }
}

///////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::glonassGen() const
{
    return m_glonassGen;
}

void proverkaItem::setGlonassGen(const QString &glonassGen)
{
    if(glonassGen != m_glonassGen)
    {
        m_glonassGen = glonassGen;
        emit glonassGenChanged(m_glonassGen);
    }
}
///////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::gpsFind() const
{
    return m_gpsFind;
}

void proverkaItem::setGpsFind(const QString &gpsFind)
{
    if(gpsFind != m_gpsFind)
    {
        m_gpsFind = gpsFind;
        emit gpsFindChanged(m_gpsFind);
    }
}

///////////////////////////////////////////////////////////////////////////////
const QString &proverkaItem::glonassFind() const
{
    return m_glonassFind;
}

void proverkaItem::setGlonassFind(const QString &glonassFind)
{
    if(glonassFind != m_glonassFind)
    {
        m_glonassFind = glonassFind;
        emit glonassFindChanged(m_glonassFind);
    }
}

///////////////////////////////////////////////////////////////////////////////
const bool &proverkaItem::vnytrenGen() const
{
    return m_vnytrenGen;
}

void proverkaItem::setVnytrenGen(const bool &vnytrenGen)
{
    if(vnytrenGen != m_vnytrenGen)
    {
        m_vnytrenGen = vnytrenGen;
        emit vnytrenGenChanged();
    }
}

///////////////////////////////////////////////////////////////////////////////
const bool &proverkaItem::good() const
{
    return m_good;
}

void proverkaItem::setGood(const bool &good)
{
    if(good != m_good)
    {
        m_good = good;
        emit goodChanged(m_good);
    }
}
///////////////////////////////////////////////////////////////////
const QString &proverkaItem::indexProverki() const
{
    return m_indexProverki;
}

void proverkaItem::setIndexProverki(const QString &indexProverki)
{
    if(indexProverki != m_indexProverki)
    {
        m_indexProverki = indexProverki;
        emit indexProverkiChanged(m_indexProverki);

        qDebug () << "indexPr = " << m_indexProverki;
    }
}

/////////////////////////////////////////////////////////////////////
const QString &proverkaItem::timeTimer() const
{
    return m_tick;
}

void proverkaItem::setTimeTimer(const QString &timeTimer)
{
    if(timeTimer != m_tick)
    {
        m_tick = timeTimer;
        emit signal_Tick(timeTimer);
    }
}
////////////////////////////////////////////////////////////////

const QVariantList &proverkaItem::listSpytnik() const
{

    return m_listSpytnik;
}

void proverkaItem::setListSpytnik(const QVariantList &listSpytnik)
{

    if(listSpytnik != m_listSpytnik)
    {
        m_listSpytnik.clear();

        for(int i=0; i < listSpytnik.count();i++)
        {
              m_listSpytnik.append(listSpytnik.value(i));
        }

        emit signal_listSpytnikChanged(m_listSpytnik);
    }
}

const QVariantList &proverkaItem::listSpytnik_Amplitude() const
{
    return m_listSpytnik_Amplitude;
}

void proverkaItem::setlistSpytnik_Amplitude(const QVariantList &listSpytnik_Amplitude)
{
    if(listSpytnik_Amplitude != m_listSpytnik_Amplitude)
    {
        m_listSpytnik_Amplitude = listSpytnik_Amplitude;

        emit signal_listSpytnik_AmplitudeChanged(m_listSpytnik_Amplitude);
    }
}

const QVariantList &proverkaItem::listSpytnik_Name() const
{
    return m_listSpytnik_Name;
}

void proverkaItem::setlistSpytnik_Name(const QVariantList &listSpytnik_Name)
{
    if(listSpytnik_Name != m_listSpytnik_Name)
    {
        m_listSpytnik_Name = listSpytnik_Name;

        emit signal_listSpytnik_NameChanged(m_listSpytnik_Name);
    }

}

const QVariantList &proverkaItem::listSpytnik_Liters() const
{
    return m_listSpytnik_Liters;
}

void proverkaItem::setlistSpytnik_Liters(const QVariantList &listSpytnik_Liters)
{
    if(listSpytnik_Liters != m_listSpytnik_Liters)
    {
        m_listSpytnik_Liters = listSpytnik_Liters;

        emit signal_listSpytnik_LitersChanged(m_listSpytnik_Liters);
    }
}



///////////////////////////////////////////////////////////////////////////////


void proverkaItem::slot_GetSignalProverka()
{
    emit signal_StartProverka();

}

void proverkaItem::slot_Tick(QString timeTimer)
{
    // qDebug () << "LOl = " << timeTimer;

    setTimeTimer(timeTimer);

}

void proverkaItem::slot_Good(bool good)
{
    setGood(good);
}

void proverkaItem::slot_IndexProverki(QString indexPr)
{

    setIndexProverki(indexPr);
}

int proverkaItem::slot_IndexNp()
{
    return index;
}





void proverkaItem::slot_setListSpytnik(QStringList listSp,QStringList listSp_Amplitude,QStringList listSp_Name)
{
    // qDebug() <<"listSP = " << listSp;





    list.clear();

    foreach(QString s, listSp)
    {
        list << s;
    }


    //qCopy(listSp.begin(),listSp.end(),list.begin());

  //  for(int i =0; i < listSp.count();i++)
  //  {
  //      v = QVariant();
   //     list.append();
   // }

    setListSpytnik(list);


    list.clear();

    foreach(QString s, listSp_Amplitude)
    {
        list << s;
    }

   //  qCopy(listSp_Amplitude.begin(),listSp_Amplitude.end(),list.begin());

  //  for(int i =0; i < listSp_Amplitude.count();i++)
   // {
   //     list << listSp_Amplitude[i];
   // }


    setlistSpytnik_Amplitude(list);

    list.clear();

    foreach(QString s, listSp_Name)
    {
        list << s;
    }

    // qCopy(listSp_Name.begin(),listSp_Name.end(),list.begin());

   // for(int i =0; i < listSp_Name.count();i++)
  //  {
   //     list << listSp_Name[i];
   // }

    setlistSpytnik_Name(list);

    list.clear();


}
