#ifndef FROG_RELATION_LIBRARYADDWIDGET_H
#define FROG_RELATION_LIBRARYADDWIDGET_H

// qt
#include <QWidget>

class QLabel;
class QFileSystemModel;
class QSlider;

namespace nsRelation {

  class LibraryItemData;

  class LibraryAddWidget : public QWidget {
    Q_OBJECT
  public:
    LibraryAddWidget(QWidget* parent = 0);
  signals:
    void onCancelClicked();
    void onPathAddition(const LibraryItemData&);
  private slots:
    void libraryPathChanged(const QModelIndex&);
    void addLibrary();
    void dividePathAt(int pos);
  private:
    QFileSystemModel* mFileSystemModel;
    QLabel* mPathLabel;
    QSlider* mPathSlider;
    QString mPath;
    QString mPathForAddition;
  };
}

#endif // FROG_RELATION_LIBRARYADDWIDGET_H
