#include "cpu_graph.h"

#include <QDebug>
#include <QStringList>
#include <QVBoxLayout>

CpuGraph::CpuGraph(QWidget *parent) : QWidget(parent) {
  QVBoxLayout *layout = new QVBoxLayout(this);
  customPlot = new QCustomPlot(this);
  layout->addWidget(customPlot);
  customPlot->xAxis->setLabel("Time (s)");
  customPlot->yAxis->setLabel("CPU Usage (%)");
  customPlot->yAxis->setRange(0, 100);
  customPlot->legend->setVisible(true);
  customPlot->legend->setBrush(QBrush(QColor(255, 255, 255, 150)));
  customPlot->axisRect()->insetLayout()->setInsetAlignment(
      0, Qt::AlignTop | Qt::AlignRight);
  udpSocket = new QUdpSocket(this);
  bool ok = udpSocket->bind(QHostAddress::LocalHost, 1234,
                            QUdpSocket::ReuseAddressHint);
  qDebug() << "Bind success:" << ok;
  connect(udpSocket, &QUdpSocket::readyRead, this,
          &CpuGraph::readPendingDatagrams);
}

void CpuGraph::readPendingDatagrams() {
  while (udpSocket->hasPendingDatagrams()) {
    QByteArray datagram;
    datagram.resize(int(udpSocket->pendingDatagramSize()));
    udpSocket->readDatagram(datagram.data(), datagram.size());
    QString dataStr(datagram);
    QStringList values = dataStr.split(',');
    if (cpuData.isEmpty()) {
      for (int i = 0; i != values.size(); ++i) {
        cpuData.append(QVector<double>());
        customPlot->addGraph();
        customPlot->graph(i)->setPen(
            QPen(QColor::fromHsv(i * 40 % 360, 255, 200)));
        QString cpuName = (i == 0) ? "CPU" : QString("CPU%1").arg(i - 1);
        customPlot->graph(i)->setName(cpuName);
      }
    }
    timeData.append(elapsedTime);
    for (int i = 0; i != values.size() && i != cpuData.size(); ++i) {
      double val = values[i].toDouble();
      cpuData[i].append(val);
      customPlot->graph(i)->setData(timeData, cpuData[i]);
    }
    elapsedTime += 1.0;
    if (timeData.size() > maxPoints) {
      timeData.remove(0);
      for (auto &v : cpuData) v.remove(0);
    }
    if (!timeData.isEmpty()) {
      double t_end = timeData.last();
      double t_start = t_end - 5.0;
      if (t_start < 0) t_start = 0;
      customPlot->xAxis->setRange(t_start, t_end);
      customPlot->replot();
    }
  }
}
