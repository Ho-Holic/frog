#ifndef FROG_RELATION_MOVETOOL_HPP
#define FROG_RELATION_MOVETOOL_HPP

// self
#include "Tool.h"

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
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
  private:
    bool mIsDeleteAllowed;
  };
}

#endif // FROG_RELATION_MOVETOOL_HPP
