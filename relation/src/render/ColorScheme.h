#ifndef FROG_RELATION_COLORSCHEME_H
#define FROG_RELATION_COLORSCHEME_H

class QColor;
class QSize;
class QString;

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
    static QSize  boxForText(const QString& name);
  };

}
#endif // FROG_RELATION_COLORSCHEME_H
