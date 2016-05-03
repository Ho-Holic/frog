#ifndef FROG_RELATION_TOOL_HPP
#define FROG_RELATION_TOOL_HPP

// qt
#include <QList>
#include <QObject>

class QPoint;

namespace nsRelation {

  class MarkingMenuItem {

  };

  // TODO: add Tool word as HandToolType, MoveToolType
  enum ToolType {
    HandType,
    MoveType,
    ConnectType,
    ToolTypeSize
  };

  class Entity;

  class Tool : public QObject {
    Q_OBJECT
  signals:    
    void onMarkingMenuChanged(const QString&, MarkingMenuItem*);
  public:
    typedef QList<Entity*> SelectionList; // TODO: rename Selection
    typedef QList<MarkingMenuItem*> MarkingMenu;
  public:
    Tool(QObject* parent = 0);    
  public:
    const SelectionList& selection() const;
    void addToSelection(Entity* selected);    
    void clearSelection();
    void reportMenuStatus(const QString& replyId);
  public:
    virtual void beginTouch(const QPoint& pos);
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
    virtual void reset();    
  private:
    // you don't need to delete this pointers
    SelectionList mSelectedEntities; // TODO: rename mSelection
    MarkingMenu mMarkingMenu;
  };
}

#endif // FROG_RELATION_TOOL_HPP
