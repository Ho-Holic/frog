#ifndef FROG_RELATION_CONNECTTOOL_HPP
#define FROG_RELATION_CONNECTTOOL_HPP

// self
#include "Tool.h"

namespace nsRelation {

  class ConnectTool  : public Tool {
  public:
    ConnectTool();
  public:
    virtual void beginTouch(const QPoint& pos);
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
  };
}
#endif // FROG_RELATION_CONNECTTOOL_HPP
