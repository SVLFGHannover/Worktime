#ifndef ARBEITSTAG_H
#define ARBEITSTAG_H

#include <QObject>
#include <QTime>
#include <QDate>

// Klasse enthält Informationen zu einem Arbeitstag
class Arbeitstag {
public:
  Arbeitstag();
  ~Arbeitstag();

// Getter und Setter
// Setter setzen sowohl qint32 als auch QString Versionen der Variablen
  const QString &getZeitFA() const;
  void setZeitFA(const QString &newZeitFA);
  const QString &getZeitNT() const;
  void setZeitNT(const QString &newZeitNT);
  void setZeitFehl(const QString &newZeitFehl);
  const QString &getZeitFehlGrund() const;
  void setZeitFehlGrund(const QString &newZeitFehlGrund);

  qint32 getIntZeitFA() const;
  void setIntZeitFA(qint32 newIntZeitFA);
  qint32 getIntZeitNT() const;
  void setIntZeitNT(qint32 newIntZeitNT);
  qint32 getIntZeitF() const;
  void setIntZeitFZ(qint32 newIntZeitFehl);

  const QString &getZeitSoll() const;
  void setZeitSoll(const QString &newZeitSoll);

  qint32 getIntZeitSoll() const;
  void setIntZeitSoll(qint32 newIntZeitSoll);

  const QDate &getDate() const;
  void setDate(const QDate &newDate);

  bool getCompleted() const;
  void setCompleted(bool newCompleted);

  const QStringList &getKommtBuchung() const;
  void setKommtBuchung(const QString &newKommtZeit);
  const QStringList &getGehtBuchung() const;
  void setGehtBuchung(const QString &newGehtZeit);
  const QStringList &getFaBuchung() const;
  void setFaBuchung(const QString &newFaBuchung);
  qint32 popFaBuchung();
  qint32 popNTBuchung();

  void
  clear(); // setzt alle Werte bis aufs Datum zurück für einen neuen Arbeitstag
  void auswerten(); // Wertet Buchungszeitpunkte aus und summiert unter NT/FA Zeit
  const QString &getLineSummary();

  const QString &getZeitZeus() const;
  void setZeitZeus(const QString &newZeitZeus);

  qint32 getIntZeitZeus() const;
  void setIntZeitZeus(qint32 newIntZeitZeus);

private:
  QDate date;            // Arbeitstag
  QString zeitSoll;      // Sollzeit
  QString zeitZeus;      // Die von Zeus ermittelte Arbeitszeit
  QString zeitFA;        // Summe der flexiblen Arbeitszeit pro Tag
  QString zeitNT;        // Summe der Büro Arbeitszeit pro Tag
  QString zeitFehl;      // Summe der Fehlzeiten pro Tag
  QString zeitFehlGrund; // Grund für die Fehlzeit (URL,GLT, etc.)
  QStringList kommtBuchung; // Liste der Kommen Buchungen
  QStringList gehtBuchung;  // Liste der Geht Buchungen
  QStringList faBuchung; // Liste der hoffentlich paarigen Buchungen mit flexibler
                      // Arbeitszeit

  qint32 intZeitSoll; // Sollzeit in Minuten
  qint32 intZeitZeus; // Ermittelte Arbeitszeit in Minuten
  qint32 intZeitFA;   // Summe der flexiblen Arbeitszeit pro Tag in Minuten
  qint32 intZeitNT;   // Summe der Büro Arbeitszeit pro Tag in Minuten
  qint32 intZeitFehl; // Summe der Fehlzeiten pro Tag in Minuten

  QString lineSummary;  // Gibt eine Zeile mit den Daten zurück (für Listen)

  bool completed;       // Arbeitszeit-Objekt ist vollständig
  qint32 toMinutes(QString);      // konvertiert die Strings in Minuten (H.mm)-> Minuten
  QString minutes2String(qint32); // konvertiert die Minuten wieder in Strings Minuten->(H:mm)

signals:
};

#endif // ARBEITSTAG_H
