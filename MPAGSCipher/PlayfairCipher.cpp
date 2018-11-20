// Standard library includes
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
// Out project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key )
  : key_{""}
{
//    std::cout << key_ << std::endl;
      setKey(key);
  //  std::cout << key_ << std::endl;
}

//PlayfairCipher::PlayfairCipher( ) {}

void PlayfairCipher::setKey ( const std::string& key) 
{
    // store the original key
    key_ = key;

    // Append the alphabet: loop over the alphabet, then nested loop over the key. If the letter isn't present, then append it to the end of the key. 
    
    for ( size_t j {0}; j<alphabetSize_; ++j ) {
      //  for ( size_t i {0}; i<key_.size(); ++i ) {
        //    std::size_t found {key_.find(alphabet_[j])}; 
          //  if (found==std::string::npos) { 
                     key_.push_back(alphabet_[j]);    
           // }
          
       // }

    }

    // Use std::transform with the ::toupper function to capitalize
    std::string newKey {""};
    std::transform( key_.begin(), key_.end(), std::back_inserter(newKey),  ::toupper );
    key_ = newKey;

    //std::cout << key_ << std::endl; 

    // Remove non-alpha characters:: define a function that returns a space if 
    auto copy_iter = std::copy_if(key_.begin(), key_.end(), key_.begin(), ::isalpha );
    key_.erase(copy_iter, key_.end() );
    //std::cout << key_ << std::endl;

    // Change J -> I
    auto replace_func = [] (char x) {
        char out_letter {'x'};
        if (x == 'J') 
            out_letter = 'I'; 
        else 
            out_letter = x;
        return out_letter;
    }; 
    
    std::transform( key_.begin(), key_.end(), key_.begin(), replace_func );
    std::cout << key_ << std::endl;

    // Remove duplicated letters

    // Going to need a string of encountered letters. This will start blank 
    std::string used_letters {""};

    // Will need to use the remove_if algorithm to remove the letter if it has already been encountered, e.g 
    // Then define the encounter function as a lambda
    // the iterator will go over the chars, so it should take the char, then loop over used_letters,
    // checking if it's in there (use string::find?) yes - the lambda should return a boolean 
    //  for ( size_t i {0}; i<key_.size(); ++i ) {
    //    std::size_t found {key_.find(alphabet_[j])}; 
    //  if (found!=std::string::npos) {  

    auto duplicate_func = [&used_letters] ( char x ) { 
        //for ( size_t i {0}; i < used_letters.size(); ++i)  
            std::size_t found {used_letters.find( x )};
            if (found!=std::string::npos) 
                return true;            // Returns true if the letter is already in used_letters 
            else 
                used_letters.push_back( x );
                return false;
    };
 
    auto rem_iter = std::remove_if( key_.begin(), key_.end(), duplicate_func);
    key_.erase(rem_iter, key_.end() );
    std::cout << key_ << std::endl;
    // Store the coords of each letter

    // Store the playfair cihper key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const 
{
    // store the original key
    //key_ = key;

    // Append the alphabet

    // Make sure the key is upper case
    // Remove non-alpha characters
    // Change J -> I

    // Remove duplicated letters

    // Store the coords of each letter

    // Store the playfair cihper key map    
    
    // Create the output string 
    std::string outputText {""};
        if (cipherMode == CipherMode::Encrypt) {
        outputText = inputText;}

    std::cout << "Sorry, I haven't implemented the cipher yet" << std::endl;
    return outputText;
}

