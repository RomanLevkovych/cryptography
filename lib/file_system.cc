#include "file_system.h"

#include <QDebug>
#include <QFile>

namespace lib {

QString FileSystem::readFile(QUrl path) {
  QString relative_path = path.toString().remove("file://");
  QFile file{relative_path};
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Error opening file";
    return "";
  }

  return QString{file.readAll()};
}

void FileSystem::saveFile(QUrl path, QString data) {
  QString relative_path = path.toString().remove("file://");
  QFile file{relative_path};
  if (!file.open(QIODevice::WriteOnly)) {
    qDebug() << "Error opening file";
    return;
  }

  file.write(data.toUtf8());
}

}  // namespace lib
