#include <numeric>

#include <QDebug>

#include "caesar_cipher.h"

lib::CaesarCipher::CaesarCipher(const CipherAlphabet alphabet) noexcept
{
  SetAlphabet(alphabet);
}

bool
lib::CaesarCipher::IsValidKey(std::int32_t key) const noexcept
{
  return key >= 0 && key < alphabet_.size();
}

void
lib::CaesarCipher::SetAlphabet(const lib::CipherAlphabet alphabet) noexcept
{
  static const QString latin = "abcdefghijklmnopqrstuvwxyz ";
  static const QString cyrillic = "абвгґдеєжзиіїйклмнопрстуфхцчшщьюя ";

  switch (alphabet) {
    case lib::CipherAlphabet::LATIN:
      alphabet_ = latin;
      break;
    case lib::CipherAlphabet::CYRILLIC:
      alphabet_ = cyrillic;
      break;
  }
}

QString
lib::CaesarCipher::Encrypt(const QString data, std::int32_t key) const noexcept
{
  return std::accumulate(
    data.begin(),
    data.end(),
    QString{ "" },
    [key = key % alphabet_.size(), this](auto init, auto item) {
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

QString
lib::CaesarCipher::Decrypt(const QString data, std::int32_t key) const noexcept
{
  return std::accumulate(
    data.begin(),
    data.end(),
    QString{ "" },
    [key = key % alphabet_.size(), this](auto init, auto item) {
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

int
lib::CaesarCipher::GetPosition(QChar ch) const noexcept
{
  return alphabet_.indexOf(ch);
}
