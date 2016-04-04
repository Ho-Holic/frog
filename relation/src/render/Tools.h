#ifndef FROG_RELATION_TOOLS_H
#define FROG_RELATION_TOOLS_H

// qt
#include <QVector>
#include <QPoint>

namespace nsRelation {

  class Tool;

  class Tools {
  public:
    enum ToolType {
      HandType,
      MoveType,
      ConnectType,
      ToolTypeSize
    };

  public:
    Tools();
    ~Tools();
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
