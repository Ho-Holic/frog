#ifndef FROG_RELATION_TOOL_HPP
#define FROG_RELATION_TOOL_HPP

// qt
#include <QList>

class QPoint;

namespace nsRelation {

  class Entity;

  class Tool {
  public:
    typedef QList<Entity*> SelectionList; // TODO: rename Selection
  public:
    Tool();
    virtual ~Tool();
  public:
    const SelectionList& selection() const;
    void addToSelection(Entity* newOne);
    void subtractFromSelection(Entity* oldOne);
    void clearSelection();
  public:
    virtual void beginTouch(const QPoint& pos);
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
  private:
    SelectionList mSelectedEntities; // TODO: rename mSelection
  };
}

#endif // FROG_RELATION_TOOL_HPP
