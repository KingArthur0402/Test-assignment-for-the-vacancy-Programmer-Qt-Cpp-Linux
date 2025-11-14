#ifndef CPUGRAPH_H
#define CPUGRAPH_H

#include <QUdpSocket>
#include <QVector>
#include <QWidget>

#include "qcustomplot.h"

class CpuGraph : public QWidget {
  Q_OBJECT
 public:
  CpuGraph(QWidget *parent = nullptr);

 private slots:
  void readPendingDatagrams();

 private:
  QUdpSocket *udpSocket;
  QCustomPlot *customPlot;
  QVector<QVector<double> > cpuData;
  QVector<double> timeData;
  int maxPoints = 100;
  double elapsedTime = 0.0;
};

#endif  // CPUGRAPH_H
