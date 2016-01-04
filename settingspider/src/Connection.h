#ifndef SETTINGSPIDER_CONNECTION_H
#define SETTINGSPIDER_CONNECTION_H

// qt
#include <QPoint>
#include <QString>
#include <QRect>

namespace nsSettingSpider {

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

#endif // SETTINGSPIDER_CONNECTION_H
