//! Unit Tests for MPAGSCipher CaesarCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Cipher.hpp"
#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"
#include "CipherFactory.hpp"

#include <map>
#include <string>
#include <memory>
#include <vector>


bool testCipher(const Cipher& cipher, const CipherMode mode,
                 const std::string& inputText, const std::string& outputText)
{
        return outputText == cipher.applyCipher(inputText, mode);
}

/*
//I wanted to use this function below in the require statements but the compiler
//gave me an error I couldn't figure out:
//error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = Cipher; _Dp = std::default_delete<Cipher>]’
//       REQUIRE(testCipher(cipher, CipherMode::Encrypt, encryptText.at(cipherType), decryptText.at(cipherType)));

bool testCipher(const std::unique_ptr<Cipher>& cipher, const CipherMode mode,
                 const std::string& inputText, const std::string& outputText)
{
        return outputText == cipher->applyCipher(inputText, mode);
}
*/

std::map<CipherType, std::string> encryptText {
    {CipherType::Caesar, "HELLOWORLD"},
    {CipherType::Playfair, "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING"},
    {CipherType::Vigenere, "ABCDEFGHIJKLMNOPQRSTUVWXYZ"}
};

std::map<CipherType, std::string> decryptText {
    {CipherType::Caesar, "ROVVYGYBVN"},
    {CipherType::Playfair, "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA"},
    {CipherType::Vigenere, "KFANIDQLGTOJWRMZUPCXSFAVID"}
};

std::map<CipherType, std::unique_ptr<Cipher>> cipherCollection;



TEST_CASE("Cipher encryption", "encrypt")
{
    cipherCollection.clear();
    cipherCollection.emplace(std::piecewise_construct, std::make_tuple(CipherType::Caesar), std::make_tuple(cipherFactory(CipherType::Caesar, "10")));
    cipherCollection.emplace(std::piecewise_construct, std::make_tuple(CipherType::Playfair), std::make_tuple(cipherFactory(CipherType::Playfair, "hello")));
    cipherCollection.emplace(std::piecewise_construct, std::make_tuple(CipherType::Vigenere), std::make_tuple(cipherFactory(CipherType::Vigenere, "key")));
    for(const auto& [cipherType, cipher] : cipherCollection)
    {
        REQUIRE(cipher->applyCipher(encryptText.at(cipherType), CipherMode::Encrypt) == decryptText.at(cipherType));
    }
}

TEST_CASE("Cipher decryption", "decrypt")
{
    cipherCollection.clear();
    cipherCollection.emplace(std::piecewise_construct, std::make_tuple(CipherType::Caesar), std::make_tuple(cipherFactory(CipherType::Caesar, "10")));
    //cipherCollection.emplace(std::piecewise_construct, std::make_tuple(CipherType::Playfair), std::make_tuple(cipherFactory(CipherType::Playfair, "hello")));
    cipherCollection.emplace(std::piecewise_construct, std::make_tuple(CipherType::Vigenere), std::make_tuple(cipherFactory(CipherType::Vigenere, "key")));
    for(const auto& [cipherType, cipher] : cipherCollection)
    {
        REQUIRE(cipher->applyCipher(decryptText.at(cipherType), CipherMode::Decrypt) == encryptText.at(cipherType));
    }
    //Don't get back what you started with with Playfair (if you want to test it all anyway)
    //so do the decryption test separately
    PlayfairCipher pc{"hello"};
    REQUIRE(testCipher(pc, CipherMode::Decrypt, "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "BOBISXSOMESORTOFIUNIORCOMPLEXQXENOPHONEONEZEROTHINGZ"));
}
/*
TEST_CASE("Caesar Cipher encryption", "[caesar]")
{
    CaesarCipher cc{10};
    REQUIRE(testCipher(cc, CipherMode::Encrypt, "HELLOWORLD", "ROVVYGYBVN"));
}

TEST_CASE("Caesar Cipher decryption", "[caesar]")
{
    CaesarCipher cc{10};
    REQUIRE(testCipher(cc, CipherMode::Decrypt, "ROVVYGYBVN", "HELLOWORLD"));
}

TEST_CASE("Playfair Cipher encryption", "[playfair]") {
  PlayfairCipher pc{"hello"};
  REQUIRE(testCipher(pc, CipherMode::Encrypt, "BOBISSOMESORTOFJUNIORCOMPLEXXENOPHONEONEZEROTHING", "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA"));
}

TEST_CASE("Playfair Cipher decryption", "[playfair]") {
  PlayfairCipher pc{"hello"};
  REQUIRE(testCipher(pc, CipherMode::Decrypt, "FHIQXLTLKLTLSUFNPQPKETFENIOLVSWLTFIAFTLAKOWATEQOKPPA", "BOBISXSOMESORTOFIUNIORCOMPLEXQXENOPHONEONEZEROTHINGZ"));
}

TEST_CASE("Vigenere Cipher encryption", "[vigenere]") {
  VigenereCipher vc{"key"};
  REQUIRE(testCipher(vc, CipherMode::Encrypt, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "KFANIDQLGTOJWRMZUPCXSFAVID"));
}

TEST_CASE("Vigenere Cipher decryption", "[vigenere]") {
  VigenereCipher vc{"key"};
  REQUIRE(testCipher(vc, CipherMode::Decrypt, "KFANIDQLGTOJWRMZUPCXSFAVID", "ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
}
*/