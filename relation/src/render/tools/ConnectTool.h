#ifndef FROG_RELATION_CONNECTTOOL_HPP
#define FROG_RELATION_CONNECTTOOL_HPP

// self
#include "Tool.h"
#include "world/Relation.h"
#include "world/Connection.h"

namespace nsRelation {

  class ConnectTool  : public Tool {
  public:

    enum ConnectMode {
      Idle,
      AboutToConnect,
      AboutToDisconnect
    };

  public:
    ConnectTool(QObject* parent = 0);
  public:
    RelationType relationType() const;
    void setRelationType(const RelationType& type);
    Connection pendingConnection() const;    
    void setConnectMode(ConnectMode mode);

  public:
    virtual void beginTouch(const QPoint& pos);
    virtual void move(const QPoint& from, const QPoint& to);
    virtual void endTouch(const QPoint& pos);
    virtual void reset();
  private:
    RelationType mRelationType;
    Connection mPendingConnection;  
    ConnectMode mConnectMode;
  };
}
#endif // FROG_RELATION_CONNECTTOOL_HPP
