#ifndef FROG_RELATION_IDGENERATOR_H
#define FROG_RELATION_IDGENERATOR_H

namespace nsRelation {

  template <typename T> struct InitialId { static T value(); };

  template <typename T>
  class IdGenerator {
  public:
    typedef T id_type;
  public:
    IdGenerator()
      : id(InitialId<T>::value()) {
      //
    }

    T next() {
      return id++;
    }

  private:
    T id;
  };

  // integer id generator

  template<> struct InitialId<int> { static int value() { return 0; } };

  typedef IdGenerator<int> IntegerIdGenerator;
}

#endif // FROG_RELATION_IDGENERATOR_H
