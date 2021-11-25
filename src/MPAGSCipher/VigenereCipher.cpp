#include "VigenereCipher.hpp"
#include "Alphabet.hpp"

#include <algorithm>
#include <string>
#include <iostream>

VigenereCipher::VigenereCipher(const std::string& key)
{
    this->setKey(key);
}

void VigenereCipher::setKey(const std::string& key)
{
    // Store the original key
    key_ = key;

    // Make sure the key is uppercase
    std::transform(std::begin(key_), std::end(key_), std::begin(key_),
                   ::toupper);
    // Remove non-alphabet characters
    key_.erase(std::remove_if(std::begin(key_), std::end(key_),
                              [](char c) { return !std::isalpha(c); }),
               std::end(key_));
    // Check if the key is empty and replace with default if so
    if (key_.empty())
    {
        key_ = "default";
        std::cerr << "[error] Key is empty, using \"default\" instead" << std::endl;
    }
    charLookup_.clear();
    std::size_t pos{0};
    // loop over the key
    for (const char letter : key_)
    {
        if(charLookup_.find(letter) != charLookup_.end())
        {
            continue;
        }
        // Find the letter position in the alphabet
        pos = Alphabet::alphabet.find(letter);
        // Create a CaesarCipher using this position as a key
        CaesarCipher currentCaesarCipher{pos};
        // Insert a std::pair of the letter and CaesarCipher into the lookup
        //Can't use charLookup_[letter] = currentCaesarCipher because it tries to construct
        //a CasesarCipher but don't have default constructor.
        charLookup_.emplace(std::piecewise_construct, std::make_tuple(letter), std::make_tuple(currentCaesarCipher));
    }
}

std::string VigenereCipher::applyCipher(const std::string& inputText,
                                        const CipherMode cipherMode) const
{
    std::string outputText{""};
    // For each letter in input:
    for(std::size_t i{0}; i<inputText.length();i++)
    {
        // Find the corresponding letter in the key, 
        // repeating/truncating as required
        const char currentLetter = inputText[i];
        const char currentKey = key_[i%key_.length()];
        // Find the Caesar cipher from the lookup
        const CaesarCipher& currentCaesarCipher = charLookup_.at(currentKey);
        // Run the (de)encryption
        // Add the result to the output
        outputText += currentCaesarCipher.applyCipher(std::string{currentLetter}, cipherMode);
    }
    return outputText;
    /*
    if (key_.length() > inputText.length())
    {
        std::cerr << "[error] key cannot be longer than the input text" << std::endl;
        return inputText;
    }
    std::string strCipherMode{""};
    strCipherMode = (cipherMode == CipherMode::Encrypt) ? "Encrypt" : "Decrypt";
    std::cout << "Vigenere cipher input text: " << inputText << " and cipherMode: " << strCipherMode << std::endl;
    return inputText;
    */
}