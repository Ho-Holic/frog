#ifndef FROG_RELATION_TOOLS_H
#define FROG_RELATION_TOOLS_H

// qt
#include <QVector>
#include <QPoint>

// tools
#include "tools/ConnectTool.h"
#include "tools/HandTool.h"
#include "tools/MoveTool.h"

namespace nsRelation {

  class Tools {
  public:
    Tools();
    ~Tools();
  public:
    HandTool* handTool() const;
    ConnectTool* connectTool() const;
  public:
    QPoint origin() const;
  public:
    void beginTouch(const QPoint& pos);
    void move(const QPoint& from, const QPoint& to);
    void endTouch(const QPoint& pos);
  public:
    void changeToolTo(ToolType tool);
    Tool* currentTool() const;
    ToolType currentToolType() const;
    bool isLocked() const;
  private:
    QVector<Tool*> mTools;
    ToolType mCurrentTool;
    bool mIsLocked;
  };
}

#endif // FROG_RELATION_TOOLS_H
