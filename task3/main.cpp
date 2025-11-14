#include <QApplication>

#include "cpu_graph.h"
#include "qcustomplot.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CpuGraph w;
  w.resize(800, 600);
  w.show();

  return a.exec();
}
