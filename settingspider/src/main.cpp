// self
#include "MainWindow.h"

// qt
#include <QApplication>

// run as : "./settingspider load.scheme --isolate=libData.so"                // gui mode
// run as : "./settingspider load.scheme --convert-pgsql=import_20150111.sql" //

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  nsSettingSpider::MainWindow w;
  w.resize(500, 500);
  w.show();

  return a.exec();
}
