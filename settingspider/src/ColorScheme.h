#ifndef SETTINGSPIDER_COLORSCHEME_H
#define SETTINGSPIDER_COLORSCHEME_H

// qt
#include <QColor>

namespace nsSettingSpider {

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
#endif // SETTINGSPIDER_COLORSCHEME_H
