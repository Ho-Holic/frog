#ifndef FROG_RELATION_MARKINGMENUITEM_H
#define FROG_RELATION_MARKINGMENUITEM_H

// qt
#include <QString>
#include <QRect>

namespace nsRelation {

  class MarkingMenuItem {
  public:
    MarkingMenuItem(const QString& actionName);
  public:
    void setTopLeft(const QPoint& pos);
    const QString& actionName() const;
    const QRect& rect() const;
  private:
    QString mActionName;
    QRect mRect;
  };
}
#endif // FROG_RELATION_MARKINGMENUITEM_H
