// self
#include "Convertor.h"
#include "world/Entity.h"
#include "world/Connection.h"
#include "world/Header.h"

// qt
#include <QUuid>

// common
#include "cplusplus11.h"
#include <frog/io/src/io.hpp>

nsRelation::Convertor::Convertor(QObject* parent)
: QObject(parent)
, mId(QUuid::createUuid().toString())
, mMode(Disable)
, mPath()
, mFile()
, mFileOut() {
  //
}

bool nsRelation::Convertor::isActive() const {
  return mMode != Disable;
}

void nsRelation::Convertor::saveTo(const QString& path) {

  mMode = SaveToOwnFormat;
  mPath = path;

  Q_ASSERT( ! mFile.isOpen());
  mFile.setFileName(path);
  mFile.open(QIODevice::WriteOnly);
  mFileOut.setDevice(&mFile);
  emit onSaveRequestInformation(mId);

  mMode = Disable;
  mFileOut.flush();
  mFileOut.setDevice(nullptr);
  mFile.close();

}

void nsRelation::Convertor::saveEntity(const QString& replyId, nsRelation::Entity* entity) {

  if (replyId != mId) {
    return;
  }

  Q_ASSERT(isActive() && mFile.isOpen());

  QPoint pos = entity->rect().center();
  mFileOut << Header::entity     << " "
           << entity->idString() << " "
           << pos.x()            << " "
           << pos.y()            << " "
           << "\"" << entity->libraryName() << "\"" << " "
           << endl;
}

void nsRelation::Convertor::saveConnection(const QString& replyId, nsRelation::Connection* connection) {

  if (replyId != mId) {
    return;
  }

  Q_ASSERT(isActive() && mFile.isOpen());

  mFileOut << Header::connection             << " "
           << connection->relationType()     << " "
           << connection->from()->idString() << " "
           << connection->to()->idString()   << " "
           << endl;
}

void nsRelation::Convertor::loadFrom(const QString& path) {

  QStringList list = io::getFileAsStringList(path);
  foreach (const QString& item, list) {
    emit onItemLoaded(item);
  }
}
