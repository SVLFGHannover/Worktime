#include "arbeitstag.h"

// Klasse enthält Informationen zu einem Arbeitstag

Arbeitstag::Arbeitstag() { this->setCompleted(false); }
Arbeitstag::~Arbeitstag() {}

const QString &Arbeitstag::getZeitFA() const { return zeitFA; }

void Arbeitstag::setZeitFA(const QString &newZeitFA) {
  zeitFA = newZeitFA;
  intZeitFA = toMinutes(zeitFA);
}

void Arbeitstag::setZeitNT(const QString &newZeitNT) {
  zeitNT = newZeitNT;
  intZeitNT = toMinutes(zeitNT);
}

void Arbeitstag::setZeitFehl(const QString &newZeitF) {
  zeitFehl = newZeitF;
  intZeitFehl = toMinutes(zeitFehl);
}

void Arbeitstag::setZeitFehlGrund(const QString &newZeitFGrund) {
  zeitFehlGrund = newZeitFGrund;
}

void Arbeitstag::setIntZeitFA(qint32 newIntZeitFA) {
  intZeitFA = newIntZeitFA;
  zeitFA = minutes2String(intZeitFA);
}

void Arbeitstag::setIntZeitNT(qint32 newIntZeitNT) {
  intZeitNT = newIntZeitNT;
  zeitNT = minutes2String(intZeitNT);
}

void Arbeitstag::setIntZeitFZ(qint32 newIntZeitF) {
  intZeitFehl = newIntZeitF;
  zeitFehl = minutes2String(intZeitFehl);
}

void Arbeitstag::setZeitSoll(const QString &newZeitSoll) {
  zeitSoll = newZeitSoll;
  intZeitSoll = toMinutes(zeitSoll);
}

void Arbeitstag::setIntZeitSoll(qint32 newIntZeitSoll) {
  intZeitSoll = newIntZeitSoll;
  zeitSoll = minutes2String(newIntZeitSoll);
}

void Arbeitstag::setKommtBuchung(const QString &newKommtBuchung) {
  kommtBuchung.append(newKommtBuchung);
}

void Arbeitstag::setGehtBuchung(const QString &newGehtBuchung) {
  gehtBuchung.append(newGehtBuchung);
}

void Arbeitstag::setFaBuchung(const QString &newFaBuchung) {
  faBuchung.append(newFaBuchung);
}

void Arbeitstag::setZeitZeus(const QString &newZeitZeus)
{
    zeitZeus = newZeitZeus;
    intZeitZeus = toMinutes(zeitZeus);
}

void Arbeitstag::setIntZeitZeus(qint32 newIntZeitZeus)
{
    intZeitZeus = newIntZeitZeus;
    zeitZeus = minutes2String(intZeitZeus);
}

void Arbeitstag::setDate(const QDate &newDate) { date = newDate; }
void Arbeitstag::setCompleted(bool newCompleted) { completed = newCompleted; }

const QString &Arbeitstag::getZeitNT() const { return zeitNT; }
const QString &Arbeitstag::getZeitFehlGrund() const { return zeitFehlGrund; }
qint32 Arbeitstag::getIntZeitFA() const { return intZeitFA; }
qint32 Arbeitstag::getIntZeitNT() const { return intZeitNT; }
qint32 Arbeitstag::getIntZeitF() const { return intZeitFehl; }
const QString &Arbeitstag::getZeitSoll() const { return zeitSoll; }
qint32 Arbeitstag::getIntZeitSoll() const { return intZeitSoll; }
const QDate &Arbeitstag::getDate() const { return date; }
bool Arbeitstag::getCompleted() const { return completed; }
const QStringList &Arbeitstag::getKommtBuchung() const { return kommtBuchung; }
const QStringList &Arbeitstag::getGehtBuchung() const { return gehtBuchung; }
const QStringList &Arbeitstag::getFaBuchung() const { return faBuchung; }
const QString &Arbeitstag::getZeitZeus() const { return zeitZeus; }
qint32 Arbeitstag::getIntZeitZeus() const { return intZeitZeus; }
const QString &Arbeitstag::getLineSummary()
{
    lineSummary = QString("%1  Sollzeit:%2    Büro:%3    FA:%4    ZeusDienst:%5    Kennung:%6").arg(getDate().toString("dd.MMM yyyy"),12,QChar(' ')).arg(getZeitSoll(),6).arg(
                getZeitNT(),6).arg(getZeitFA(),6).arg(getZeitZeus(),6).arg(getZeitFehlGrund(),4);
    return lineSummary;
}

void Arbeitstag::auswerten() {
  // wertet paarige Buchungszeitpunkte und andere Buchungszeitpunkte aus.
  // VORSICHT: Nur im Bereich 6:00 - 19:00 auswerten
  QTime t1;
  QTime t2;
  QTime t1min = QTime::fromString(
      "06:00"); // ausserhalb dieser Zeiten wird nichts gezählt
  QTime t2max = QTime::fromString(
      "19:00"); // ausserhalb dieser Zeiten wird nichts gezählt

  qint64 deltaMinuten = 0;
  // Kommt Geht summieren
  for (int i = 0; i < kommtBuchung.count(); i++) {
    t1 = QTime::fromString(kommtBuchung[i], "H:mm"); // kommtZeit[i]
    t2 = QTime::fromString(gehtBuchung[i], "H:mm");  // gehtZeit[i]
    if (t1 < t1min) {
      t1 = t1min;
    }
    if (t2 > t2max) {
      t2 = t2max;
    }
    deltaMinuten += (t1.secsTo(t2)) / 60;
  }
  // Mittagspause abziehen; TODO: Wenn Arbeitsunterbrechung mehr als 15 Minuten,
  // auf Mittagspause anrechnen
  if (deltaMinuten > 360) {
    deltaMinuten -= 30;
  }
  if (deltaMinuten > 540) {
    deltaMinuten -= 15;
  }

  setIntZeitNT(deltaMinuten);

  deltaMinuten = 0;
  // faZeit summieren
  for (int i = 0; i < faBuchung.count(); i += 2) {
    t1 = QTime::fromString(faBuchung[i], "H:mm");     // faZeit[i]
    t2 = QTime::fromString(faBuchung[i + 1], "H:mm"); // faZeit[i+1]
    if (t1 < t1min) {
      t1 = t1min;
    }
    if (t2 > t2max) {
      t2 = t2max;
    }
    deltaMinuten += (t1.secsTo(t2)) / 60;
  }
  // Mittagspause abziehen; TODO: Wenn Arbeitsunterbrechung mehr als 15 Minuten,
  // auf Mittagspause anrechnen
  if (deltaMinuten > 360) {
    deltaMinuten -= 30;
  }
  if (deltaMinuten > 540) {
    deltaMinuten -= 15;
  }
  setIntZeitFA(deltaMinuten);
}


qint32 Arbeitstag::toMinutes(QString s) {
  QTime time = QTime::fromString(s, "H.mm");
  return (time.hour() * 60 + time.minute());
}

QString Arbeitstag::minutes2String(qint32 m) {

  qint32 hour = (int)m / 60;
  qint32 min = m % 60;
  QString retVal =
      QString("%1:%2").arg(hour, 3, 10, QChar(' ')).arg(min, 2, 10, QChar('0'));
  return retVal;
}

void Arbeitstag::clear() {
  // date = QDate::currentDate();
  zeitSoll.clear();
  zeitFA.clear();
  zeitNT.clear();
  zeitFehl.clear();
  zeitFehlGrund.clear();
  kommtBuchung.clear();
  gehtBuchung.clear();
  faBuchung.clear();

  intZeitSoll = 0;
  intZeitFA = 0;
  intZeitNT = 0;
  intZeitFehl = 0;
  completed = false;
}
