#ifndef FROG_RELATION_COLORSCHEME_H
#define FROG_RELATION_COLORSCHEME_H

class QColor;

namespace nsRelation {

  class ColorScheme {
  public:
    static QColor background();
    static QColor backgroundDecoration();
    static QColor entity();
    static QColor connection();
    static QColor entityText();
    static QColor deleteArea();
    static QColor deleteAreaText();
  };

}
#endif // FROG_RELATION_COLORSCHEME_H
