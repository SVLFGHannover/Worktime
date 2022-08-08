#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Proof of Concept für eine eigene Zeusauswertung

#include "arbeitstag.h"
#include "monat.h"
#include <QDebug>
#include <QFileDialog>
#include <QMainWindow>
#include <QStandardPaths>
#include <QVarLengthArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void loadFile();

private:
  Ui::MainWindow *ui;
  QString fileName;
  qint64 countLines;
  qint64 countLinesProcessed;
  qint64 process_line(Arbeitstag *, QString);
  QVarLengthArray<Arbeitstag> atArray;
  Monat currMonth;
  QString appVersion;
};
#endif // MAINWINDOW_H
