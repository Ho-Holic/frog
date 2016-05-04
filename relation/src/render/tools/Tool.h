#ifndef FROG_RELATION_TOOL_HPP
#define FROG_RELATION_TOOL_HPP

// qt
#include <QList>
#include <QObject>
#include <QPoint>

// self
#include "MarkingMenuItem.h"

class QPoint;

namespace nsRelation {

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
    ~Tool();
  public:
    const QPoint& origin() const;
    void setOrigin(const QPoint& pos);
    const SelectionList& selection() const;
    void addToSelection(Entity* selected);    
    void clearSelection();
    void addToMarkingMenu(const QString& action);
    void reportMenuStatus(const QString& replyId);
    void popMarkingMenu(const QPoint& pos);
  public:
    virtual void beginTouch(const QPoint& pos);
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
    virtual void reset();    
  private:  
    QPoint mOrigin;
    SelectionList mSelectedEntities; // TODO: rename mSelection // you don't need to delete this pointers
    MarkingMenu mMarkingMenu; // this pointers need to be deleted
    bool mIsMarkingMenuOpened;
    QPoint mMarkingMenuPosition;
  };
}

#endif // FROG_RELATION_TOOL_HPP
