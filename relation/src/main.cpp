// self
#include "MainWindow.h"

// qt
#include <QApplication>


// run as : "./relation --isolate=libData.so load.scheme"                // gui mode
// run as : "./relation --convert-pgsql=import_20150111.sql load.scheme" // create file .sql
// run as : "./relation --generate-scheme=load.scheme.new ./bin/libs     // auto create file

// model must have access to settings?
// how settings works?
// we have plugins in .so files

// libFrogJsonSettings.so, libFrogXmlSettings.so, libFrogYamlSettings.so

// they provide interface how to display settings, store them in "in memory" format
// and save from "in memory" to one of selected

int main(int argc, char* argv[]) {
  // TODO: set locale
  QApplication a(argc, argv);
  nsRelation::MainWindow w;
  w.resize(1000, 500);
  w.show();

  return a.exec();
}
