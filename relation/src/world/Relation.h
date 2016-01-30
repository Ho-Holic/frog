#ifndef FROG_RELATION_RELATION_H
#define FROG_RELATION_RELATION_H

// qt
#include <QString>

namespace nsRelation {

  typedef QString RelationType;

  class Relation {
  public:
    static QString Needed;
    static QString Absorb;
  };
}

#endif // FROG_RELATION_RELATION_H
