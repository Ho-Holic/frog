#ifndef FROG_RELATION_LIBRARYVIEWWIDGET_H
#define FROG_RELATION_LIBRARYVIEWWIDGET_H

// qt
#include <QTreeView>

namespace nsRelation {

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
#endif // FROG_RELATION_LIBRARYVIEWWIDGET_H
