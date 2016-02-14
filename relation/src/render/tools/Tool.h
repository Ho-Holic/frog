#ifndef FROG_RELATION_TOOL_HPP
#define FROG_RELATION_TOOL_HPP

class QPoint;

namespace nsRelation {

  class Tool {
  public:
    virtual void beginTouch(const QPoint& pos) = 0;
    virtual void move(const QPoint& from, const QPoint& to) = 0;
    virtual void endTouch(const QPoint& pos) = 0;
  public:
    virtual ~Tool();
  };
}

#endif // FROG_RELATION_TOOL_HPP
