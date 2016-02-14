#ifndef FROG_RELATION_HANDTOOL_HPP
#define FROG_RELATION_HANDTOOL_HPP

// self
#include "Tool.h"

namespace nsRelation {

  class HandTool : public Tool {
  public:
    HandTool();
  public:    
    virtual void move(const QPoint& from, const QPoint& to);    
  };
}

#endif // FROG_RELATION_HANDTOOL_HPP
