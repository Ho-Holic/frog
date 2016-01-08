#ifndef SETTINGSPIDER_ENTITY_H
#define SETTINGSPIDER_ENTITY_H

// qt
#include <QMap>
#include <QList>
#include <QRect>
#include <QFont>

// self
#include "IdGenerator.h"
#include "Relation.h"

namespace nsSettingSpider {

  class Entity {
  public:
    typedef QList<Entity*> RelationList;
    typedef QMap<RelationType, RelationList> RelationBinding;
  public:
    Entity(const QPoint& center, const QString& shortPath);
  public:
    IntegerIdGenerator::id_type sequentialId() const;
    void inAttach(const RelationType& type, Entity* from);
    void outAttach(const RelationType& type, Entity* to);
    void inDetach(const RelationType& type, Entity* from);
    void outDetach(const RelationType& type, Entity* to);

    const RelationBinding& inRelations() const;
    const RelationBinding& outRelations() const;
    const RelationList& inRelations(const RelationType& type) const;
    const RelationList& outRelations(const RelationType& type) const;
    bool hasInRelations(const RelationType& type) const;
    bool hasOutRelations(const RelationType& type) const;
  public:
    const QRect& rect() const;
    QRect connectionRect() const;
    QRect connectionSlotRect() const;
    QRect captionRect() const;
    const QString& libraryName() const;
    const QFont& font() const;
    void setTopLeft(const QPoint& pos);
  private:
    IntegerIdGenerator::id_type mId;
    QString mLibraryName;
    QFont mFont;
    QRect mRect;
    RelationBinding mInRelation;
    RelationBinding mOutRelation;
  private:
    static QSize fromName(const QString& name, const QFont& usedFont);    
  private:
    static IntegerIdGenerator s_idGenerator;
  };

}

#endif // SETTINGSPIDER_ENTITY_H
