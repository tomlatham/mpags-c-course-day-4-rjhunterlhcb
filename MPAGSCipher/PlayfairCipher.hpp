#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <iostream>
#include <string>
#include <vector>

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
        
        std::string key_ = {""};
        const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        const std::vector<char>::size_type alphabetSize_ = alphabet_.size();



    };
  
#endif
