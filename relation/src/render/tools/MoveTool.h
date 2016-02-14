#ifndef FROG_RELATION_MOVETOOL_HPP
#define FROG_RELATION_MOVETOOL_HPP

// self
#include "Tool.h"

namespace nsRelation {


  class MoveTool : public Tool {
  public:
    MoveTool();
  public:
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
  };
}

#endif // FROG_RELATION_MOVETOOL_HPP
