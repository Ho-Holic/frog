#ifndef SETTINGSPIDER_LIBRARYIMPORTWIDGET_H
#define SETTINGSPIDER_LIBRARYIMPORTWIDGET_H

// qt
#include <QStackedWidget>

class QTreeWidget;

namespace nsSettingSpider {

  class LibraryModel;

  class LibraryImportWidget : public QStackedWidget {
  private:
    Q_OBJECT
  private:
    enum { LibraryViewMode, LibraryAddMode };
  public:
    LibraryImportWidget(QWidget* parent = 0);    
  public slots:
    void switchToLibraryViewMode();
    void switchToLibraryAddMode();
  private:
    LibraryModel* mModel;
  };
}

#endif // SETTINGSPIDER_LIBRARYIMPORTWIDGET_H
