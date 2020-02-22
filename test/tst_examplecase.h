#ifndef TST_EXAMPLECASE_H
#define TST_EXAMPLECASE_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <QDebug>

#include <caesar_cipher.h>

using namespace testing;
using namespace lib;

class CaesarCipherTest : public Test
{
protected:
  QString alphabet = "abcdef";
  CaesarCipher ciph{ CipherAlphabet::LATIN };
};

TEST_F(CaesarCipherTest, ShouldReturnTrueForCorrectKey)
{
  EXPECT_FALSE(ciph.IsValidKey(1));
}

TEST_F(CaesarCipherTest, ShouldReturnFalseForIncorrectKey)
{
  EXPECT_FALSE(ciph.IsValidKey(-2));
  EXPECT_FALSE(ciph.IsValidKey(alphabet.size() + 10));
}

TEST_F(CaesarCipherTest, ShouldCorrectlyEncryptTexts)
{
  EXPECT_EQ(QString{ "bcd" }, ciph.Encrypt("abc", 1));
  EXPECT_EQ(QString{ "efa" }, ciph.Encrypt("def", 1));
}

TEST_F(CaesarCipherTest, ShouldCorrectlyDecryptTexts)
{
  EXPECT_EQ(QString{ "abc" }, ciph.Decrypt("bcd", 1));
  EXPECT_EQ(QString{ "def" }, ciph.Decrypt("efa", 1));
}

#endif // TST_EXAMPLECASE_H
