#ifndef CIPHER_HPP
#define CIPHER_HPP

#include <string>
#include <CipherMode.hpp>

/**
 * \file Cipher.hpp
 * \brief Contains the declaration of the Cipher class
 */

/**
 * \class Cipher
 * \brief Purely Abstract Base Class for a generic cipher with an applyCipher function
 */
class Cipher {
    public:
        /**
         * \brief Default constructor for the Cipher
         */
        Cipher() = default;
        /**
         * \brief Default C++ copy constructor
         *
         * \param rhs Existing Cipher to copy
         */
        Cipher(const Cipher& rhs) = default;
        /**
         * \brief Default C++ move constructor
         *
         * \param rhs Existing Cipher to move
         */
        Cipher(Cipher&& rhs) = default;
        /**
         * \brief Default C++ copy assignment operator
         *
         * \param rhs Existing Cipher to copy for assignment
         */
        Cipher& operator=(const Cipher& rhs) = default;
        /**
         * \brief Default C++ move assignment operator
         *
         * \param rhs Existing Cipher to move for assignment
         */
        Cipher& operator=(Cipher&& rhs) = default;
        /**
         * \brief Default C++ destructor
         */
        virtual ~Cipher() = default;

        /**
         * \brief Base applyCipher function to encrypt/decrypt text
         *        using a cipher method.
         *
         * \param input The text to be encrypted/decrypted
         * \param mode  The mode to specify whether it should encrypt
         *              (decrpyt) using CipherMode::Encrypt
         *              (CipherMode::Decrypt) 
         */
        virtual std::string applyCipher( const std::string& input,
                                         const CipherMode mode ) const = 0;
};

#endif // CIPHER_HPP