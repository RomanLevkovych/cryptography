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
  CaesarCipher ciph{ CaesarCipher::CipherAlphabet::LATIN };
};

TEST_F(CaesarCipherTest, ShouldReturnTrueForCorrectKey)
{
  EXPECT_TRUE(ciph.IsValidKey(1));
}

TEST_F(CaesarCipherTest, ShouldReturnFalseForIncorrectKey)
{
  EXPECT_FALSE(ciph.IsValidKey(-2));
  EXPECT_FALSE(ciph.IsValidKey(36));
}

TEST_F(CaesarCipherTest, ShouldCorrectlyEncryptTexts)
{
  EXPECT_EQ(QString{ "bcd" }, ciph.Encrypt("abc", 1));
  EXPECT_EQ(QString{ "tpnfaufyu" }, ciph.Encrypt("some text", 1));
}

TEST_F(CaesarCipherTest, ShouldCorrectlyDecryptTexts)
{
  EXPECT_EQ(QString{ "abc" }, ciph.Decrypt("bcd", 1));
  EXPECT_EQ(QString{ "some text" }, ciph.Decrypt("tpnfaufyu", 1));
}

#endif // TST_EXAMPLECASE_H
