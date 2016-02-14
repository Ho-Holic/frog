// self
#include "ColorScheme.h"

// qt
#include <QRect>
#include <QFontMetrics>
#include <QColor>

QColor nsRelation::ColorScheme::background() {
  return QColor(30, 30, 39);
}

QColor nsRelation::ColorScheme::backgroundDecoration() {
  return QColor(35, 35, 59);
}

QColor nsRelation::ColorScheme::entity() {
  return QColor(207, 191, 173);
}

QColor nsRelation::ColorScheme::connection() {
  return QColor(69, 69, 90);
}

QColor nsRelation::ColorScheme::entityText() {
  return QColor(30, 30, 39);
}

QColor nsRelation::ColorScheme::deleteArea() {
  return QColor(218, 68, 83, 128);
}

QColor nsRelation::ColorScheme::deleteAreaText() {
  return QColor(55, 17, 21);
}

QFont nsRelation::ColorScheme::itemTextFont() {
  return QFont();
}

QSize nsRelation::ColorScheme::boxForText(const QString& name, const QFont& usedFont) {

  static int twoSpacesFromEachSide = 4;
  static int twoLines = 2;

  QFontMetrics metrics(usedFont);
  int w = metrics.boundingRect(name).width() + (metrics.averageCharWidth() * twoSpacesFromEachSide);
  return QSize(w, metrics.height() * twoLines);
}
