#include "caesar_cipher.h"

#include <QDebug>
#include <QFile>
#include <numeric>

lib::CaesarCipher::CaesarCipher(QObject* parent) : QObject(parent) {
  setAlphabet("en");
}

qint32 lib::CaesarCipher::convertKey(qint32 key) const noexcept {
  return abs(key) % alphabet_.size();
}

void lib::CaesarCipher::setAlphabet(const QString alphabet) noexcept {
  static const QString latin = "abcdefghijklmnopqrstuvwxyz ";
  static const QString cyrillic = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя ";

  if ("en" == alphabet) {
    alphabet_ = latin;
  } else {
    alphabet_ = cyrillic;
  }
  type_ = alphabet;
}

QString lib::CaesarCipher::encrypt(const QString data, qint32 key) const
    noexcept {
  return std::accumulate(
      data.begin(), data.end(), QString{""}, [key, this](auto init, auto item) {
        if (-1 != GetPosition(item)) {
          int e_pos = GetPosition(item) + key;
          e_pos -= e_pos >= alphabet_.size() ? alphabet_.size() : 0;
          init += alphabet_[e_pos];
        } else {
          init += item;
        }
        return init;
      });
}

QString lib::CaesarCipher::decrypt(const QString data, qint32 key) const
    noexcept {
  return std::accumulate(
      data.begin(), data.end(), QString{""}, [key, this](auto init, auto item) {
        if (-1 != GetPosition(item)) {
          auto e_pos = GetPosition(item) - key;
          auto d_pos = (e_pos < 0) ? (e_pos + alphabet_.size()) : e_pos;
          init += alphabet_[d_pos];
        } else {
          init += item;
        }

        return init;
      });
}

qint32 lib::CaesarCipher::bruteForce(const QString text, QString alpha) const {
  QMap<QString, QString> str = {
      {"en", "/Users/roman_levkovych/Projects/cryptography/wordsEN.txt"},
      {"ua", "/Users/roman_levkovych/Projects/cryptography/wordsUK.txt"}};
  QByteArrayList t_dict;
  qDebug() << str[alpha];
  QFile file{str[alpha]};
  if (!file.open(QIODevice::ReadOnly)) {
  }
  t_dict = file.readAll().split('\n');
  QStringList dict;
  for (QByteArray item : t_dict) {
    dict.push_back(QString{item});
  }
  for (int i = 0; i < alphabet_.size(); ++i) {
    QString res = decrypt(text, i);
//    int count = 0;
    for (QString item : res.split(' ')) {
        qDebug() << item;
      if (dict.contains(item.toLower())) {
        return i;
      }
    }

    qDebug() << "\n\n";

//    if (count >= res.split(' ').size() * 0.7) {
//      return i;
//    }
  }
  return 0;
}

int lib::CaesarCipher::GetPosition(QChar ch) const noexcept {
  return alphabet_.indexOf(ch);
}
