// self
#include "MainWindow.h"

// qt
#include <QApplication>


// new name -> relation, relationBuilder, relationSpider, relationModeler

// run as : "./settingspider --isolate=libData.so load.scheme"                // gui mode
// run as : "./settingspider --convert-pgsql=import_20150111.sql load.scheme" // create file .sql
// run as : "./settingspider --generate-scheme=load.scheme.new ./bin/libs     // auto create file

// model must have access to settings to?
// how settings works?
// we have plugins in .so files

// libFrogJsonSettings.so, libFrogXmlSettings.so, libFrogYamlSettings.so

// they provide interface how to display settings, store them in "in memory" format
// and save from "in memory" to one of selected

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  nsSettingSpider::MainWindow w;
  w.resize(1000, 500);
  w.show();

  return a.exec();
}
