#ifndef SETTINGSPIDER_LIBRARYVIEWWIDGET_H
#define SETTINGSPIDER_LIBRARYVIEWWIDGET_H

// qt
#include <QTreeView>

namespace nsSettingSpider {

  class LibraryViewWidget : public QTreeView {
    Q_OBJECT
  public:
    LibraryViewWidget(QWidget* parent = 0);
  signals:
    void onLibraryAddClicked();
  private slots:
    void createMenuAt(const QPoint& pos);
  };
}
#endif // SETTINGSPIDER_LIBRARYVIEWWIDGET_H
