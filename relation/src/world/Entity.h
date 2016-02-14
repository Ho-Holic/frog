#ifndef FROG_RELATION_ENTITY_H
#define FROG_RELATION_ENTITY_H

// qt
#include <QMap>
#include <QList>
#include <QRect>
#include <QFont>

// self
#include "IdGenerator.h"
#include "Relation.h"

namespace nsRelation {

  class Entity {
  public:
    typedef QList<Entity*> RelationList;
    typedef QMap<RelationType, RelationList> RelationBinding;
  public:
    static Entity* create(const QPoint& center,
                          const QString& shortPath,
                          IntegerId::id_type id = IntegerId::id_type());
  private:
    Entity(const QPoint& center,
           const QString& shortPath,
           IntegerId::id_type id);
  public:
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
    IntegerId::id_type sequentialId() const;
    QString idString() const;    
    const QRect& rect() const;
    QRect connectionRect() const;
    QRect connectionSlotRect() const;
    QRect captionRect() const;
    const QString& libraryName() const;    
    void setTopLeft(const QPoint& pos);
  private:
    IntegerId::id_type mId;
    QString mLibraryName;    
    QRect mRect;
    RelationBinding mInRelation;
    RelationBinding mOutRelation;
  };    

}

#endif // FROG_RELATION_ENTITY_H
