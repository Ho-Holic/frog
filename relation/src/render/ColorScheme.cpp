// self
#include "ColorScheme.h"

// qt
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
