// self
#include "ColorScheme.h"

// qt
#include <QRect>
#include <QFontMetrics>
#include <QColor>
#include <QApplication>

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

QSize nsRelation::ColorScheme::boxForText(const QString& name) {

  static int twoSpacesFromEachSide = 4;
  static int twoLines = 2;

  QFontMetrics metrics(qApp->font());
  int w = metrics.boundingRect(name).width() + (metrics.averageCharWidth() * twoSpacesFromEachSide);
  return QSize(w, metrics.height() * twoLines);
}
