#ifndef MPAGSCIPHER_VIGENERECIPHER_HPP
#define MPAGSCIPHER_VIGENERECIPHER_HPP

#include "CipherMode.hpp"
#include "CaesarCipher.hpp"
#include "Cipher.hpp"

#include <map>
#include <string>

/**
 * \file VigenereCipher.hpp
 * \brief Contains the declaration of the VigenereCipher class
 */

/**
 * \class VigenereCipher
 * \brief Encrypt or decrypt text using the Vigenere cipher with the given key
 */
class VigenereCipher : public Cipher {
  public:
    /**
     * \brief Create a new VigenereCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    explicit VigenereCipher(const std::string& key);

    /**
     * \brief Set the key to be used for the encryption/decryption
     *
     * \param key the key to use in the cipher
     */
    void setKey(const std::string& key);

    /**
     * \brief Apply the cipher to the provided text
     *
     * \param inputText the text to encrypt or decrypt
     * \param cipherMode whether to encrypt or decrypt the input text
     * \return the result of applying the cipher to the input text
     */
    std::string applyCipher(const std::string& inputText,
                            const CipherMode cipherMode) const override;

  private:
    /// The grid size
    //const std::string::size_type gridSize_{5};

    /// The key length = grid size^2
    //const std::string::size_type keyLength_{gridSize_ * gridSize_};

    /// The cipher key
    std::string key_{""};

    /// Lookup table
    std::map<char, CaesarCipher> charLookup_;
};

#endif