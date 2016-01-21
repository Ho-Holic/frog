// self
#include "Convertor.h"
#include "world/Entity.h"

// qt
#include <QUuid>

// common
#include "cplusplus11.h"

nsSettingSpider::Convertor::Convertor(QObject* parent)
: QObject(parent)
, mId(QUuid::createUuid().toString())
, mMode(Disable)
, mPath()
, mFile()
, mFileOut() {
  //
}

bool nsSettingSpider::Convertor::isActive() const {
  return mMode != Disable;
}

void nsSettingSpider::Convertor::saveTo(const QString& path) {

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

void nsSettingSpider::Convertor::saveEntity(const QString& replyId, nsSettingSpider::Entity* entity) {

  if (replyId != mId) {
    return;
  }

  Q_ASSERT(isActive() && mFile.isOpen());

  QPoint pos = entity->rect().center();
  mFileOut << tr("entity")       << " "
           << entity->idString() << " "
           << pos.x()            << " "
           << pos.y()            << " "
           << "\"" + entity->libraryName() << "\"" << " "
           << endl;
}

void nsSettingSpider::Convertor::saveConnection(const QString& replyId, nsSettingSpider::Connection* connection) {

  if (replyId != mId) {
    return;
  }

  Q_ASSERT(isActive() && mFile.isOpen());

  mFileOut << 2 << endl;
}
