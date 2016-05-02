#ifndef FROG_RELATION_TOOLS_H
#define FROG_RELATION_TOOLS_H

// qt
#include <QObject>
#include <QVector>
#include <QPoint>

// tools
#include "tools/ConnectTool.h"
#include "tools/HandTool.h"
#include "tools/MoveTool.h"

namespace nsRelation {

  class Tools : public QObject {
  public:
    explicit Tools(QObject* parent = 0);
  public:
    HandTool* handTool() const;
    ConnectTool* connectTool() const;
    MoveTool* moveTool() const;
    // isMoveTool() const; // and so on
  public:
    QPoint origin() const;
  public:
    void beginTouch(const QPoint& pos);
    void move(const QPoint& from, const QPoint& to);
    void endTouch(const QPoint& pos);
    void reset();
  public:
    void changeToolTo(ToolType tool);
    Tool* currentTool() const;
    ToolType currentToolType() const;    
  private:
    QVector<Tool*> mTools;
    ToolType mCurrentTool;    
  };
}

#endif // FROG_RELATION_TOOLS_H
