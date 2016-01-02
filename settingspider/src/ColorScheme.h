#ifndef SETTINGSPIDER_COLORSCHEME_HPP
#define SETTINGSPIDER_COLORSCHEME_HPP

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
#endif // SETTINGSPIDER_COLORSCHEME_HPP
