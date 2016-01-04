#ifndef LIBRARYADDWIDGET_H
#define LIBRARYADDWIDGET_H

// qt
#include <QWidget>

class QLabel;
class QFileSystemModel;
class QSlider;

namespace nsSettingSpider {
  class LibraryAddWidget : public QWidget {
    Q_OBJECT
  public:
    LibraryAddWidget(QWidget* parent = 0);
  signals:
    void onCancelClicked();
    void onPathAddition(const QString& path);
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

#endif // LIBRARYADDWIDGET_H
