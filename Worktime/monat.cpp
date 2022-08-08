#include "monat.h"

//Klasse fasst die Daten aus den Arbeitstagen zusammen zu einem Summary
Monat::Monat()
{
    yearMonth=QDate();
    sumZeitSoll=0;
    sumZeitNT=0;
    sumZeitFA=0;
    sumZeitFehl1=0;
    sumZeitFehl2=0;
    saldo=0;

    strYearMonth="";
    strSumZeitSoll="";
    strSumZeitNT="";
    strSumZeitFA="";
    strSumZeitFehl1="";
    strSumZeitFehl2="";
    strSaldo="";

    summaryLine="";
}

void Monat::clear()
{
    yearMonth=QDate();
    sumZeitSoll=0;
    sumZeitNT=0;
    sumZeitFA=0;
    sumZeitFehl1=0;
    sumZeitFehl2=0;
    saldo=0;

    strYearMonth="";
    strSumZeitSoll="";
    strSumZeitNT="";
    strSumZeitFA="";
    strSumZeitFehl1="";
    strSumZeitFehl2="";
    strSaldo="";

    summaryLine="";
}

const QDate &Monat::getYearMonth() const
{
    return yearMonth;
}

void Monat::setYearMonth(const QDate &newYearMonth)
{
    yearMonth = newYearMonth;
    strYearMonth = yearMonth.toString();
}

qint64 Monat::getSumZeitSoll() const
{
    return sumZeitSoll;
}

void Monat::setSumZeitSoll(qint64 newSumZeitSoll)
{
    sumZeitSoll = newSumZeitSoll;
    strSumZeitSoll = minutes2String(sumZeitSoll);
}

qint64 Monat::getSumZeitNT() const
{
    return sumZeitNT;
}

void Monat::setSumZeitNT(qint64 newSumZeitNT)
{
    sumZeitNT = newSumZeitNT;
    strSumZeitNT = minutes2String(sumZeitNT);
}

qint64 Monat::getSumZeitFA() const
{
    return sumZeitFA;
}

void Monat::setSumZeitFA(qint64 newSumZeitFA)
{
    sumZeitFA = newSumZeitFA;
    strSumZeitFA = minutes2String(sumZeitFA);
}

qint64 Monat::getSumZeitFehl1() const
{
    return sumZeitFehl1;
}

void Monat::setSumZeitFehl1(qint64 newSumZeitFehl1)
{
    sumZeitFehl1 = newSumZeitFehl1;
    strSumZeitFehl1 = minutes2String(sumZeitFehl1);
}

qint64 Monat::getSumZeitFehl2() const
{
    return sumZeitFehl2;
}

void Monat::setSumZeitFehl2(qint64 newSumZeitFehl2)
{
    sumZeitFehl2 = newSumZeitFehl2;
    strSumZeitFehl2 = minutes2String(sumZeitFehl2);
}

qint64 Monat::getSaldo() const
{
    return saldo;
}

void Monat::setSaldo(qint64 newSaldo)
{
    saldo = newSaldo;
    strSaldo = QString::number(saldo);
}

const QString &Monat::getStrYearMonth() const
{
    return strYearMonth;
}

void Monat::setStrYearMonth(const QString &newStrYearMonth)
{
    strYearMonth = newStrYearMonth;
    yearMonth = QDate::fromString(strYearMonth);    // testen...
}

const QString &Monat::getStrSumZeitSoll() const
{
    return strSumZeitSoll;
}

void Monat::setStrSumZeitSoll(const QString &newStrSumZeitSoll)
{
    strSumZeitSoll = newStrSumZeitSoll;
    sumZeitSoll = toMinutes(strSumZeitSoll);
}

const QString &Monat::getStrSumZeitNT() const
{
    return strSumZeitNT;
}

void Monat::setStrSumZeitNT(const QString &newStrSumZeitNT)
{
    strSumZeitNT = newStrSumZeitNT;
    sumZeitNT = toMinutes(strSumZeitNT);
}

const QString &Monat::getStrSumZeitFA() const
{
    return strSumZeitFA;
}

void Monat::setStrSumZeitFA(const QString &newStrSumZeitFA)
{
    strSumZeitFA = newStrSumZeitFA;
    sumZeitFA = toMinutes(strSumZeitFA);
}

const QString &Monat::getStrSumZeitFehl1() const
{
    return strSumZeitFehl1;
}

void Monat::setStrSumZeitFehl1(const QString &newStrSumZeitFehl1)
{
    strSumZeitFehl1 = newStrSumZeitFehl1;
    sumZeitFehl1 = toMinutes(strSumZeitFehl1);
}

const QString &Monat::getStrSumZeitFehl2() const
{
    return strSumZeitFehl2;
}

void Monat::setStrSumZeitFehl2(const QString &newStrSumZeitFehl2)
{
    strSumZeitFehl2 = newStrSumZeitFehl2;
    sumZeitFehl2 = toMinutes(strSumZeitFehl2);
}

const QString &Monat::getStrSaldo() const
{
    return strSaldo;
}

void Monat::setStrSaldo(const QString &newStrSaldo)
{
    strSaldo = newStrSaldo;
    saldo = toMinutes(strSaldo);
}

qint32 Monat::toMinutes(QString s) {
  QTime time = QTime::fromString(s, "H.mm");
  return (time.hour() * 60 + time.minute());
}

QString Monat::minutes2String(qint32 m) {
  qint32 hour = (int)m / 60;
  qint32 min = m % 60;
  QString retVal =
      QString("%1.%2").arg(hour, 3, 10, QChar(' ')).arg(min, 2, 10, QChar('0'));
  return retVal;
}

void Monat::setSummaryLine(const QString s)
{
    summaryLine = s;
    return ;
}



QString Monat::getSummaryLine()
{
    QString retLine=QString("%1 Sollzeit:%2   FA:%3   NT:%4   NT+FA:%5   R1:%6   R2:%7").arg(getYearMonth().toString("MMM yyyy"),-10).arg(
                getStrSumZeitSoll(),7).arg(getStrSumZeitFA(),7).arg(getStrSumZeitNT(),7).arg(
                minutes2String(getSumZeitFA()+getSumZeitNT()),7).arg((double)getSumZeitNT()/(double)getSumZeitSoll(),5,'f',2, QChar(' ')).arg(
                (double)getSumZeitNT()/(double)(getSumZeitFA()+getSumZeitNT()),5,'f',2, QChar(' '));
    return retLine;
}
