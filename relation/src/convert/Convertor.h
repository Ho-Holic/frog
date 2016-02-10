#ifndef FROG_RELATION_CONVERTOR_H
#define FROG_RELATION_CONVERTOR_H

// qt
#include <QObject>
#include <QFile>
#include <QTextStream>

namespace nsRelation {

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
    void onItemLoaded(const QString&);
  public slots:
    void saveTo(const QString& path);
    void saveEntity(const QString& replyId, Entity* entity);
    void saveConnection(const QString& replyId, Connection* connection);
    void loadFrom(const QString& path);
  private:
    QString mId;
    Mode mMode;
    QString mPath;
    QFile mFile;
    QTextStream mFileOut;
  };

}

#endif // FROG_RELATION_CONVERTOR_H
