// self
#include "MainWindow.h"

// qt
#include <QApplication>

// run as : "./settingspider --isolate=libData.so load.scheme"                // gui mode
// run as : "./settingspider --convert-pgsql=import_20150111.sql load.scheme" // create file .sql
// run as : "./settingspider --generate-scheme=load.scheme.new ./bin/libs     // auto create file

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  nsSettingSpider::MainWindow w;
  w.resize(1000, 500);
  w.show();

  return a.exec();
}
