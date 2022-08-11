#include "mainwindow.h"
#include "ui_mainwindow.h"

// Proof of Concept für eine eigene Zeusauswertung

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  appVersion = "0.10";
  countLines = 0;               // alle eingelesenen Zeilen
  countLinesProcessed = 0;      // Zeilen, die auf das Zeilenmuster gepasst haben
  currMonth = Monat();  // Summary für den Monat
  statusBar()->showMessage(QString("Version %1 von FZ, vom %2").arg(appVersion,QDate::currentDate().toString()));
}

MainWindow::~MainWindow() { delete ui; }

// Öffnet die Datei und liest zeilenweise die Datei ein
// Jede eingelesene Zeile wird in einer Funktion untersucht +++++++++++++++++++++++++++++++++++++++
void MainWindow::loadFile() {

  fileName = QFileDialog::getOpenFileName(this, tr("Öffne Zeus Textdatei"),
                                          QDir::homePath()+"/Documents/SVLFG/SVLFGWorktime/Worktime",
                                          tr("Zeus Datei (*.csv *.txt)"));
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    return;
  QTextStream in(&file);
  bool lineIsWaiting = false;   // noch eine unausgewertete Zeile auszuwerten?
  Arbeitstag at = Arbeitstag(); // ein neues Workday--Objekt reservieren
  QString line;
  currMonth.clear();            // Summary leeren

  // Schleife zum Einlesen der Tageswerte
  while (!in.atEnd()) {
    if (lineIsWaiting == false) {
      line = in.readLine();
      countLines++;             // eine Zeile wurde eingelesen
      ui->label_Count->setText(QString("%1").arg(countLines,8));
    }
    if (at.getCompleted() == false) { // falls noch nicht komplett...
      countLinesProcessed += process_line(
          &at, line);           // weiter mit neuer Zeile  und demselben Zeiger auf at-Objekt
      ui->label_CountProcessed->setText(QString("%1").arg(countLinesProcessed,8));
      lineIsWaiting = false;    // Zeile wurde konsumiert
    } else {                    // Arbeitstag-Objekt ist vollständig
      atArray.append(at);       // kopiert per value
      at.clear();               // initialisiert das Arbeitszeit-Objekt
      lineIsWaiting = true;     // unausgewertete Zeile ist noch zu bearbeiten
    }
  }
  // Gefundene Werte in GUI eintragen
  ui->listWidget->insertItem(1, fileName);
  ui->listWidget_3->insertItem(1,currMonth.getSummaryLine());
  ui->label_fileCount->setText(QString("%1").arg(ui->listWidget->count(),8)); // Anzahl der Files aus listWidget

  // Nur bei Debug ausgeben
  qDebug() << "Ausgabe des Arrays:";
  for (int i = 0; i < atArray.count(); i++) {
    qDebug() << atArray[i].getDate() << atArray[i].getZeitSoll()
             << atArray[i].getZeitNT() << atArray[i].getZeitFA();
  }
}

// Hier wird jede Zeile untersucht und geparst ++++++++++++++++++++++++++++++++++++++++++++++++++++
qint64 MainWindow::process_line(Arbeitstag *at, QString s) {
  qint64 processed = 0; // zeigt, ob Zeile verarbeitet wurde
  QString pattern_monthyear(
      R"(^(Januar|Februar|März|April|Mai|Juni|Juli|August|September|Oktober|November|Dezember)\s+(\d\d\d\d)$)");
  QString pattern_first(
      R"(^(Mo|Di|Mi|Do|Fr|Sa|So)\s+1.*Periode\s+([+-]\d{1,4}\.\d{2})\*)");
  QString pattern_day(
      R"(^(\w{2}|\s+)\s+(\d\d?)\s+\d{1,4}\s+\|\s+([ 0-9.:]{4,5})\s+(-)?\s{1,2}(\d{1,2}:\d{2})[+ *]{3}\s+(FA|SAB|GLT|F|URL)?\s+\|(.*)\|(.*)$)");
  QString pattern_endteil(
      R"(^\s?(\d{1,2}\.\d{2})\s+(\d{1,2}\.\d{2})\s+([+-]\d{1,2}\.\d{2})\s+([+-]\d{1,2}\.\d{2}))");
  static QRegularExpression re0(pattern_monthyear);
  static QRegularExpression re1(pattern_first);
  static QRegularExpression re2(pattern_day);
  static QRegularExpression re3(pattern_endteil);
  QString uebertrag;
  QString month, year, day, day_nr;
  qint32 intMonth = 0;
  QStringList mNamen = {"Januar",    "Februar", "März",     "April",
                        "Mai",       "Juni",    "Juli",     "August",
                        "September", "Oktober", "November", "Dezember"};
  QString mittelteil2;
  QString endteil;
  QString line = "";
  qDebug() << s;

  // filtert die Monats- und Jahrzeile
  // ------------------------------------------------------------------------------------
  QRegularExpressionMatch match0 = re0.match(s);
  if (match0.hasMatch()) {
    month = match0.captured(1).trimmed();
    for (int i = 0; i < mNamen.size(); i++) {
      if (mNamen.at(i).compare(month) == 0) {
        intMonth = i + 1;   // index von 0-based korrigieren
        break;
      }
    }
    year = match0.captured(2);
    at->setDate(QDate(year.toInt(), intMonth, 1));
    line = "Beginn" + at->getDate().toString() + "--->";
    ui->listWidget_2->addItem(line);
    currMonth.setYearMonth(QDate(year.toInt(), intMonth, 1));   // Hinein ins Monat Objekt
  }
  // sucht erste Zeile mit Periodenübertrag
  // ------------------------------------------------------------------------------------
  QRegularExpressionMatch match1 = re1.match(s);
  if (match1.hasMatch()) {
    day = match1.captured(1);
    day_nr = "1";
    at->setDate(QDate(at->getDate().year(), at->getDate().month(), 1));
    uebertrag = match1.captured(2);
    line = "(" + at->getDate().toString() + " Übertrag:" + uebertrag + ")";
    ui->listWidget_2->addItem(line);
    currMonth.setStrSaldo(uebertrag);   // Hinein ins Monat Objekt
  }
  // filtert die Tageszeile
  // ------------------------------------------------------------------------------------
  QRegularExpressionMatch match2 = re2.match(s);
  if (match2.hasMatch()) {
    day = match2.captured(1);                       // Wochentagname
    day_nr = match2.captured(2);                    // Wochentag Nr.
    QString time1 = match2.captured(3).trimmed();   // Startzeit
    QString minus = match2.captured(4).trimmed();   // Minus Zeichen
    QString time2 = match2.captured(5).trimmed();   // Stopzeit oder FA-Buchungszeit
    QString kennung;
    if (at->getZeitFehlGrund().isEmpty()) {         // Falls noch nichts erkannt wurde
      kennung = match2.captured(6).trimmed();       // Kennung FA,URL,SAB,F,GLT
      at->setZeitFehlGrund(kennung);                // Hinein ins Arbeitsplatz Objekt
    }
    at->setDate(                                    // Hinein ins Arbeitsplatz Objekt
        QDate(at->getDate().year(), at->getDate().month(), day_nr.toInt()));
    if (time1.isEmpty() && minus.compare("-") == 0) {  // Ist FA-Buchung
      at->setFaBuchung(time2);                         // Hinein ins Arbeitsplatz Objekt
    } else if (!time1.isEmpty() && !time2.isEmpty()) {  // NT-Buchung
      at->setKommtBuchung(time1);                      // Hinein ins Arbeitsplatz Objekt (QStringList)
      at->setGehtBuchung(time2);                       // Hinein ins Arbeitsplatz Objekt (QStringList)
    }
    mittelteil2 = match2.captured(7);               // Brauchen wir da was von? Ja! "Buchungvergessen"
    if(mittelteil2.contains("Buchung vergessen")){
        at->clear();
        // processed = 0;
        return processed;
    }
    endteil = match2.captured(8);
    if (!endteil.isEmpty()) {                   // Endteil vorhanden ->Abschluss des Arbeitstages
      QRegularExpressionMatch match3 = re3.match(endteil);
      if (match3.hasMatch()) {
          at->setZeitSoll(match3.captured(1));
          at->setZeitZeus(match3.captured(2));
        // Ansonsten nichts was man erstmal brauchen könnte
        processed = 1;          // Rückgabewert auf 1 setzen zum Inkrementieren des Counters
      }
      at->setCompleted(true);   // Arbeitstag Objekt ist fertig
      at->auswerten();          // Einzelbuchungen zusammen fassen
      ui->listWidget_2->addItem(at->getLineSummary());
      // zur Monatssumme hinzufügen...
      currMonth.setSumZeitSoll(currMonth.getSumZeitSoll() + at->getIntZeitSoll());
      currMonth.setSumZeitFA(currMonth.getSumZeitFA() + at->getIntZeitFA());
      currMonth.setSumZeitNT(currMonth.getSumZeitNT() + at->getIntZeitNT());
    }
  }
  return processed;     // Zum Zählen der bearbeiteten Zeilen
}
