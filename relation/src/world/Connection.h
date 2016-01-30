#ifndef FROG_RELATION_CONNECTION_H
#define FROG_RELATION_CONNECTION_H

// qt
#include <QPoint>
#include <QString>
#include <QRect>

namespace nsRelation {

  class Connection {
  public:
    Connection();
    Connection(const QString& relationType, const QPoint& from, const QRect& to);
  public:
    bool isNull() const;
    const QString& relationType() const;
    const QPoint& from() const;
    const QRect& to() const;
  private:
    QString mRelationType;
    QPoint mFrom;
    QRect mTo;
  };
}

#endif // FROG_RELATION_CONNECTION_H
