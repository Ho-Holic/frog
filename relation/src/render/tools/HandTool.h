#ifndef FROG_RELATION_HANDTOOL_HPP
#define FROG_RELATION_HANDTOOL_HPP

// self
#include "Tool.h"

// qt
#include <QPoint>

namespace nsRelation {

  class HandTool : public Tool {
  public:
    HandTool(QObject* parent = 0);
  public:
    const QPoint& origin() const;
  public:    
    virtual void move(const QPoint& from, const QPoint& to);    
  private:
    QPoint mOrigin;
  };
}

#endif // FROG_RELATION_HANDTOOL_HPP
