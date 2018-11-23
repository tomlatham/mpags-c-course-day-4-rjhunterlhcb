#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <iostream>
#include <string>
#include <vector>
#include <map>
// Our project headers
#include "CipherMode.hpp"

/** 
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt test using the Playfair cipher with the given key, which is a string rather than an integer for the Caesar Cipher. 
 */

class PlayfairCipher {
    public:
        /** 
         * Create a new Playfair Cipher with the given key
         * 
         * \param key the key to use in the cipher 
         */
        explicit PlayfairCipher( const std::string& key ); 

       /**
         * Apply the cipher to the provided text
         *
         * \param inputText the text to encrypt or decrypt
         * \param cipherMode whether to encrypt or decrypt the input text
         * \return the result of applying the cipher to the input text
         */
        std::string applyCipher( const std::string& inputText, const CipherMode cipherMode) const;

       /**
        * Set the cipher key 
        *
        * \param newKey the new key to be set
        */
        void setKey( const std::string& key);        

    private:
        /// The cipher key
        std::string key_ = {""};

        /// Define the type to represent the Playfair grid coordinates
        using PlayfairCoords = std::pair<std::size_t,std::size_t>;

        /// Lookup table from character to grid coordinate
        std::map< char, PlayfairCoords > charLookup_;

        /// Lookup table from grid coordinate to character
        std::map< PlayfairCoords, char > coordLookup_;

        /// The alphabet
        const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
};

#endif
