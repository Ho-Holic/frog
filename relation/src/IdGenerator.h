#ifndef FROG_RELATION_IDGENERATOR_H
#define FROG_RELATION_IDGENERATOR_H

#include <QtGlobal>

namespace nsRelation {

  template <typename T>
  class IdType {
  public:

    IdType()
    : mIsValid(false),
      mId() {
      //
    }

    IdType(const T& id)
    : mIsValid(true),
      mId(id) {
      //
    }

    operator T() const {
      Q_ASSERT(mIsValid);
      return mId;
    }

    bool isValid() const {
      return mIsValid;
    }

  private:
    bool mIsValid;
    T mId;
  };

  template <typename T>
  class IdGenerator {
  public:
    typedef IdType<T> id_type;
  public:
    IdGenerator()
      : mId(T()) {
      //
    }

    id_type next() {
      return mId++;
    }

    bool isFree(id_type newId) {
      return newId > mId;
    }

    void take(id_type newId) {
      mId = newId;
    }

  private:
    T mId;
  };

  // client code: integer id generator

  typedef IdGenerator<int> IntegerId;
}

#endif // FROG_RELATION_IDGENERATOR_H
