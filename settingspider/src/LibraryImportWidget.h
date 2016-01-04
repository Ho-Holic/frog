#ifndef SETTINGSPIDER_LIBRARYIMPORTWIDGET_H
#define SETTINGSPIDER_LIBRARYIMPORTWIDGET_H

// qt
#include <QStackedWidget>

class QTreeWidget;

namespace nsSettingSpider {

  class LibraryAddWidget;

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
  private slots:
    void createMenuAt(const QPoint& pos);
  private:
    static QTreeWidget* createLibraryViewWidget(QWidget* parent);
    static LibraryAddWidget* createLibraryAddWidget(QWidget* parent);
  private:
    QTreeWidget* mLibraryView;
  };
}

#endif // SETTINGSPIDER_LIBRARYIMPORTWIDGET_H
