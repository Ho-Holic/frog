#ifndef SETTINGSPIDER_CONVERTOR_H
#define SETTINGSPIDER_CONVERTOR_H

// qt
#include <QObject>

namespace nsSettingSpider {

  class Convertor : public QObject {
    Q_OBJECT
  private:
    Q_DISABLE_COPY(Convertor)
  public:
    explicit Convertor(QObject* parent = 0);
  public slots:
    //
  };

}

#endif // SETTINGSPIDER_CONVERTOR_H
