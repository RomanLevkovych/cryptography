#ifndef ALPHABET_H
#define ALPHABET_H

#include <QObject>

namespace lib {

class Alphabet  {
    Q_GADGET
public:
    explicit Alphabet() = default;

    enum CipherAlphabet : qint8 { LATIN, CYRILLIC };
    Q_ENUM(CipherAlphabet);
};

}


#endif // ALPHABET_H
