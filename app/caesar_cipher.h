#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <QString>
#include <QObject>


#include "alphabet.h"

namespace lib {

class CaesarCipher : public QObject {
  Q_OBJECT

 public:

  CaesarCipher(QObject* parent = nullptr);
  Q_INVOKABLE qint32 convertKey(qint32 key) const noexcept;
  Q_INVOKABLE void setAlphabet(const QString alphabet) noexcept;
  Q_INVOKABLE QString encrypt(const QString data, qint32 key) const
      noexcept;
  Q_INVOKABLE QString decrypt(const QString data, qint32 key) const
      noexcept;
  Q_INVOKABLE QString bruteForce(const QString text, QString alpha) const;

 private:
  int getPosition(QChar ch) const noexcept;
  QString filterSymbols(QString input) const;


 private:
  QString alphabet_;
  QString type_;
};

}  // namespace lib

#endif  // CAESARCIPHER_H
