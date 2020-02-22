#ifndef CAESARCIPHERINTERFACE_H
#define CAESARCIPHERINTERFACE_H

#include <cstdint>

#include <QByteArray>

#include "lib_global.h"

namespace lib {

class LIB_EXPORT CaesarCipherInterface
{
public:
  virtual bool isValidKey(std::int32_t) const noexcept = 0;
  virtual QByteArray encrypt(const QByteArray data, std::int32_t key) const
    noexcept = 0;
  virtual QByteArray decrypt(const QByteArray data, std::int32_t key) const
    noexcept = 0;

  ~CaesarCipherInterface() = default;
};

} // namespace lib
#endif // CAESARCIPHERINTERFACE_H
