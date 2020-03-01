#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <QObject>
#include <QUrl>

namespace lib {

class FileSystem : public QObject {
  Q_OBJECT
 public:
  FileSystem(QObject *parent = nullptr) : QObject(parent) {}
  Q_INVOKABLE QString readFile(QUrl path);
  Q_INVOKABLE void saveFile(QUrl path, QString data);
 signals:
};

}

#endif  // FILESYSTEM_H
