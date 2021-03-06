#ifndef FROG_RELATION_HANDTOOL_HPP
#define FROG_RELATION_HANDTOOL_HPP

// self
#include "Tool.h"

// qt
#include <QPoint>

namespace nsRelation {

  class HandTool : public Tool {
    Q_OBJECT
  signals:
    void onOriginChanged(const QPoint& origin);
  public:
    HandTool(QObject* parent = 0);    
  public:    
    virtual void move(const QPoint& from, const QPoint& to);    
  };
}

#endif // FROG_RELATION_HANDTOOL_HPP
