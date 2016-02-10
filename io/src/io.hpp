#ifndef FROG_IO_IO_HPP
#define FROG_IO_IO_HPP

// qt
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDir>

// tmp
#include <QDebug>

namespace io {

  enum FileProcessingMode { Regular, WithoutEmptyLines };

  inline QStringList getFileAsStringList(const QString& fileName, FileProcessingMode mode = Regular) {
    QFile file(fileName);
    bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);

    QStringList result;
    if (isOpen) {

      QTextStream in(&file);
      while ( ! in.atEnd()) {
        QString line = in.readLine();
        if (mode == WithoutEmptyLines && line.trimmed().isEmpty()) {
          continue; // пропускаем пустые строки
        }
        result << line;
      }
    }

    return result;
  }

  inline QString getFileAsString(const QString& fileName) {
    QFile file(fileName);
    bool isOpen = file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (isOpen) {
      QTextStream in(&file);
      return in.readAll(); // оптимизация возвращаемого значения
    }
    return QString();
  }

  enum FileSavingMode { Normal, EnsurePath };

  inline void saveStringAsFile(const QString& data,
                               const QString& filePath,
                               FileSavingMode mode = Normal) {

    if (mode == EnsurePath) {

      QFileInfo info(filePath);
      QDir().mkpath(info.path());
    }


    QFile file(filePath);
    bool isOpen = file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (isOpen) {
      QTextStream out(&file);
      out << data;
    }
  }

  inline QStringList splitStringToList(const QString& string) {
    QStringList result;
    QString copy = string;

    QTextStream in(&copy);
    while ( ! in.atEnd()) {
      result << in.readLine();
    }
    return result;
  }

  inline int findCommentPosition(const QString& commentSymbol, const QString& line) {

    const QChar QUOTE = '"';

    enum State { Search, Skip };
    State state = Search;

    for (int i = 0; i < line.size(); ++i) {
      const QChar c = line.at(i);

      switch (state) {

      case Search:
        if (c == QUOTE) {
          state = Skip;
          break;
        }
        if (line.mid(i, commentSymbol.size()) == commentSymbol) {
          return i;
        }
        break;

      case Skip:
        if (c == QUOTE) {
          state = Search;
        }
        break;

      }
    }
    return line.length();
  }

  inline void removeCommentsFromList(const QString& commentSymbol,
                                     QStringList& list,
                                     FileProcessingMode mode = Regular) {

    QStringList::iterator i = list.begin();

    while ( i != list.end()) {

      QString& line = *i;
      int pos = findCommentPosition(commentSymbol, line);

      // условие pos < line.length() нужно, чтобы понять, что в строке есть комментарий
      // тогда есть режим при котором мы убираем пустые строки. Пустые строки не содержащие комментариев
      // изначально - остаются
      if (pos < line.length()) {
        line.replace(pos, line.length() - pos, QString());

        // если после очистки комментария строка пуста, убираем её
        if (mode == WithoutEmptyLines && line.trimmed().isEmpty()) {
          i = list.erase(i);
        }
        else {
          ++i;
        }
      }
      else {
        ++i;
      }
    }

  }

  inline void removeCommentsFromString(const QString& commentSymbol,
                                       QString& stringWithLines,
                                       FileProcessingMode mode = Regular) {

    QStringList splitted = io::splitStringToList(stringWithLines);
    io::removeCommentsFromList(commentSymbol, splitted, mode);
    QString joined;

    // QTextStream был использован для согласованности с функцией разбиения splitStringToList()
    QTextStream out(&joined);
    foreach (const QString& item, splitted) out << item;

    // возвращает значение, кто-то позже может сделать более адекватную реализацию
    // которая отрабатывает саму строку без конвертации в список
    // это можно сделать вызывая findCommentPosition() и удалять сегмент от полученной
    // позиции до перехода на новую строку. Но так как я избежал перехода на новых строк
    // через QTextStream в данной реализации это не возможно сделать.
    stringWithLines = joined;

  }

}

#endif // FROG_IO_IO_HPP
