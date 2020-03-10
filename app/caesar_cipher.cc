#include "caesar_cipher.h"

#include <QDebug>
#include <QFile>
#include <algorithm>
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
        if (-1 != getPosition(item)) {
          int e_pos = getPosition(item) + key;
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
        if (-1 != getPosition(item)) {
          auto e_pos = getPosition(item) - key;
          auto d_pos = (e_pos < 0) ? (e_pos + alphabet_.size()) : e_pos;
          init += alphabet_[d_pos];
        } else {
          init += item;
        }

        return init;
      });
}

QString lib::CaesarCipher::bruteForce(const QString text, QString alpha) const {
  QMap<QString, QString> str = {{"en", ":/wordsEN.txt"},
                                {"ua", ":/wordsUK.txt"}};
  QByteArrayList t_dict;
  qDebug() << str[alpha];
  QFile file{str[alpha]};
  if (!file.open(QIODevice::ReadOnly)) {
    qDebug() << "Error";
  }
  t_dict = file.readAll().split('\n');
  QStringList dict;
  for (QByteArray item : t_dict) {
    if (item.contains('\r')) {
      item.remove(item.indexOf('\r'), 1);
    }
    dict.push_back(QString{item});
  }
  for (int i = 0; i < alphabet_.size(); ++i) {
    QString decrypted = decrypt(text, i);
    QStringList res = filterSymbols(decrypted).split(' ');
    qint32 count = 0;
    for (QString item : res) {
      if (dict.contains(item.toLower())) {
        qDebug() << "WTF increase count";
        count++;
      }
    }

    if (count >= res.size() * 0.6) {
      return decrypted;
    }
  }
  return "No success";
}

int lib::CaesarCipher::getPosition(QChar ch) const noexcept {
  return alphabet_.indexOf(ch);
}

QString lib::CaesarCipher::filterSymbols(QString input) const {
  QString result;
  std::copy_if(
      input.begin(), input.end(), std::back_inserter(result),
      [](QChar symbol) { return symbol.isLetter() || symbol.isSpace(); });

  return result;
}
