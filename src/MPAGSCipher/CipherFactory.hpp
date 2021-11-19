#ifndef CIPHERFACTORY_HPP
#define CIPHERFACTORY_HPP

#include "Cipher.hpp"
#include "CipherType.hpp"

#include <memory>
#include <string>


std::unique_ptr<Cipher> cipherFactory( const CipherType type,
                                        const std::string& key);

#endif // CIPHERFACTORY_HPP