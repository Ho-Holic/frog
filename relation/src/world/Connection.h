#ifndef FROG_RELATION_CONNECTION_H
#define FROG_RELATION_CONNECTION_H

// qt
#include <QPoint>
#include <QString>
#include <QRect>

namespace nsRelation {

  class Entity;

  class Connection {
  public:
    Connection(); // no connection
    Connection(const QString& relationType, const Entity* from); // pending
    Connection(const QString& relationType, const Entity* from, const Entity* to); // connected
  public:
    bool isDisconnected() const;
    bool isPending() const;
    const QString& relationType() const;
    const Entity* from() const;
    const Entity* to() const;
  private:
    QString mRelationType;
    const Entity* mFrom;
    const Entity* mTo;
  };
}

#endif // FROG_RELATION_CONNECTION_H
