#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <cstdint>

#include <QString>

namespace lib {

enum class CipherAlphabet : std::int8_t
{
  LATIN,
  CYRILLIC
};

class CaesarCipher
{
public:
  CaesarCipher(const CipherAlphabet alphabet) noexcept;
  bool IsValidKey(std::int32_t key) const noexcept;
  void SetAlphabet(const lib::CipherAlphabet alphabet) noexcept;
  QString Encrypt(const QString data, std::int32_t key) const noexcept;
  QString Decrypt(const QString data, std::int32_t key) const noexcept;

private:
  int GetPosition(QChar ch) const noexcept;

  QString alphabet_;
};

} // namespace lib

#endif // CAESARCIPHER_H
