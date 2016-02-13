#ifndef FROG_IO_ARGUMENTLIST_HPP
#define FROG_IO_ARGUMENTLIST_HPP

// qt
#include <QString>

namespace io {

  template <typename T>
  class ArgumentList {
  public:
    ArgumentList(QString gluedArgs);
  };

}

// implementation

template <typename T>
io::ArgumentList<T>::ArgumentList(QString gluedArgs) {
  //
}

#endif // FROG_IO_ARGUMENTLIST_HPP
