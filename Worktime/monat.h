#ifndef MONAT_H
#define MONAT_H

#include <QObject>
#include <QDate>

//Klasse fasst die Daten aus den Arbeitstagen zusammen zu einem Summary
class Monat
{
public:
    Monat();

    const QDate &getYearMonth() const;
    void setYearMonth(const QDate &newYearMonth);
    qint64 getSumZeitSoll() const;
    void setSumZeitSoll(qint64 newSumZeitSoll);
    qint64 getSumZeitNT() const;
    void setSumZeitNT(qint64 newSumZeitNT);
    qint64 getSumZeitFA() const;
    void setSumZeitFA(qint64 newSumZeitFA);
    qint64 getSumZeitFehl1() const;
    void setSumZeitFehl1(qint64 newSumZeitFehl1);
    qint64 getSumZeitFehl2() const;
    void setSumZeitFehl2(qint64 newSumZeitFehl2);
    qint64 getSaldo() const;
    void setSaldo(qint64 newSaldo);
    const QString &getStrYearMonth() const;
    void setStrYearMonth(const QString &newStrYearMonth);
    const QString &getStrSumZeitSoll() const;
    void setStrSumZeitSoll(const QString &newStrSumZeitSoll);
    const QString &getStrSumZeitNT() const;
    void setStrSumZeitNT(const QString &newStrSumZeitNT);
    const QString &getStrSumZeitFA() const;
    void setStrSumZeitFA(const QString &newStrSumZeitFA);
    const QString &getStrSumZeitFehl1() const;
    void setStrSumZeitFehl1(const QString &newStrSumZeitFehl1);
    const QString &getStrSumZeitFehl2() const;
    void setStrSumZeitFehl2(const QString &newStrSumZeitFehl2);
    const QString &getStrSaldo() const;
    void setStrSaldo(const QString &newStrSaldo);
    QString getSummaryLine();
    void setSummaryLine(const QString s);
    void clear();

private:
    QDate yearMonth;
    qint64 sumZeitSoll;
    qint64 sumZeitNT;
    qint64 sumZeitFA;
    qint64 sumZeitFehl1;
    qint64 sumZeitFehl2;
    qint64 saldo;

    QString strYearMonth;
    QString strSumZeitSoll;
    QString strSumZeitNT;
    QString strSumZeitFA;
    QString strSumZeitFehl1;
    QString strSumZeitFehl2;
    QString strSaldo;

    QString summaryLine;

    qint32 toMinutes(QString s);
    QString minutes2String(qint32 m);
};

#endif // MONAT_H
