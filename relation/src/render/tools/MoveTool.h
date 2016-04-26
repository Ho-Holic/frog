#ifndef FROG_RELATION_MOVETOOL_HPP
#define FROG_RELATION_MOVETOOL_HPP

// self
#include "Tool.h"

// qt
#include <QRect>

namespace nsRelation {


  class MoveTool : public Tool {
    Q_OBJECT
  signals:
    void onDestroyRequest(Entity*);
  public:
    enum { DeleteRectHeight = 40 };
  public:
    MoveTool(QObject* parent = 0);
  public:
    void setDeleteArea(const QRect& area);
  public:
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
  private:    
    QRect mDeleteArea;
  };
}

#endif // FROG_RELATION_MOVETOOL_HPP
