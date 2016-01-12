#ifndef SETTINGSPIDER_CONVERTOR_H
#define SETTINGSPIDER_CONVERTOR_H

// qt
#include <QObject>
#include <QFile>
#include <QTextStream>

namespace nsSettingSpider {

  class Entity;
  class Connection;

  class Convertor : public QObject {
    Q_OBJECT
  private:
    Q_DISABLE_COPY(Convertor)
  private:
    enum Mode { Disable, SaveToOwnFormat, SaveToGraphviz, SaveToPostgreSQL };
  public:
    explicit Convertor(QObject* parent = 0);
    bool isActive() const;
  signals:
    void onSaveRequestInformation(const QString&);
  public slots:
    void saveTo(const QString& path);
    void saveEntity(const QString& replyId, Entity* entity);
    void saveConnection(const QString& replyId, Connection* connection);
  private:
    QString mId;
    Mode mMode;
    QString mPath;
    QFile mFile;
    QTextStream mFileOut;
  };

}

#endif // SETTINGSPIDER_CONVERTOR_H
