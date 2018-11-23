// Standard library includes
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

// Out project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key )
  : key_{""},
   mymap {},
   myrevmap {}
{
      setKey(key);
}


void PlayfairCipher::setKey ( const std::string& key) 
{
    // store the original key
    key_ = key;

    // Append the alphabet
    for ( auto letter : alphabet_ ) {
        key_.push_back(letter);
    }

    // Use std::transform with the ::toupper function to capitalize
    std::string newKey {""};
    std::transform( key_.begin(), key_.end(), std::back_inserter(newKey),  ::toupper );
    key_ = newKey;

    // Remove non-alpha characters:: define a function that returns a space if 
    auto copy_iter = std::copy_if(key_.begin(), key_.end(), key_.begin(), ::isalpha );
    key_.erase(copy_iter, key_.end() );

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

    // Remove duplicated letters -----------------------------------------------------------------|

    // Going to need a string of encountered letters. This will start blank 
    std::string used_letters {""};

    // Define a lambda to check if the character is in used_letters, if not push_back & return false
    auto duplicate_func = [&used_letters] ( char x ) { 
        std::size_t found {used_letters.find( x )};
        if (found!=std::string::npos) 
            return true;            // Returns true if the letter is already in used_letters 
        else 
            used_letters.push_back( x );
            return false;
    };
 
    // remove_if iterates over key_, checks if duplicate_func is true, if so it "removes" the character
    auto rem_iter = std::remove_if( key_.begin(), key_.end(), duplicate_func);
    key_.erase(rem_iter, key_.end() );
   // std::cout << key_ << std::endl;
    
    // Store the coords of each letter in maps: Letter -> Coords & Coords -> Letter
    // Typedef the maps you want to use & instantiate
    /*using Str2CoordMap = std::map< char, std::vector<int> >;
    Str2CoordMap mymap;
   
    using Coord2StrMap = std::map< std::vector<int>, char >;
    Coord2StrMap myrevmap;
   */
    int count {0};
    // Loop over the key_ container, write down the coords & instantiate a pair, save to map. 
    for ( auto letter : key_ ) {
        std::vector<int> coord {count/5, count%5};
        Str2CoordMap::value_type pair { letter, coord };
        mymap.insert( pair );
    
        Coord2StrMap::value_type revpair { coord, letter };
        myrevmap.insert( revpair );
    
        ++count;
    } 

    // Range-based loop to print the map out 
    /*for ( auto p : mymap )
    {
        std::cout << p.first << ": [" << p.second[0] << "," << p.second[1] << "]." << std::endl;
    }*/

    // Store the playfair cihper key map
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const 
{
    
    // Create the output string 
    std::string outputText {""};
    
    // Change J → I
    auto replace_func = [] (char x) {
        char out_letter {'x'};
        if (x == 'J') 
            out_letter = 'I'; 
        else 
            out_letter = x;
        return out_letter;
    }; 
    std::transform( inputText.begin(), inputText.end(), std::back_inserter(outputText), replace_func );
    std::cout << outputText << std::endl;
    // If repeated chars in a digraph add an X or Q if XX & if the size of input is odd, add a trailing Z
    std::string new_mess {""};
    //std::cout << outputText.size() << std::endl;
    size_t count{0};
    while( count < outputText.size() )
    {
            new_mess += outputText[count];
            //dealing with odd numbers of letters
            // if at the end, add a Z, unless it's already a Z -> add an X
            if(count == outputText.size()-1) 
            {
                    new_mess += (outputText[count] == 'Z' ? 'X' : 'Z');
                    break;
            }
            // Adds Q if outputText == X, add X otherwise.
            if(outputText[count+1] == outputText[count])
            {
                    new_mess += (outputText[count] == 'X' ? 'Q' : 'X');
                    ++count;
            }
            // If not a duplicate and not the last, add the next letter & advance past it. 
            else
            {
                    new_mess += outputText[count+1];
                    count += 2;
            }
    }
    //std::cout << "After duplicate  testing:" << new_mess << std::endl;
    outputText = new_mess;

    std::string cipher_string {""};  
    std::vector<int> new_coords1 {0,0}; 
    std::vector<int> new_coords2 {0,0};
    // Loop over the input in Digraphs
    for (size_t j {0}; j<outputText.size(); j += 2) {
        // Get the coordinates of the digraph, set them equal to some x,y 
        // If the second is the same, have same column, so push_back directly below
        
        // Get the coordinates in the map of the digraph
        auto map_iter1 = mymap.find(outputText[j]);
        std::vector<int> coords1 { (*map_iter1).second[0], (*map_iter1).second[1]};    
        auto map_iter2 = mymap.find(outputText[j+1]);
        std::vector<int> coords2 { (*map_iter2).second[0], (*map_iter2).second[1]};    
        //std::cout << "Coordinates before the cipher" << std::endl;
        //std::cout << outputText[j] << ": [" << coords1[0] << "," << coords1[1] << "]." << std::endl;
        //std::cout << outputText[j+1] << ": [" << coords2[0] << "," << coords2[1] << "]." << std::endl;
        
        // If the first number is the same, have same row, so push_back the letters on the right 
        if (coords1[0] == coords2[0]) {
            new_coords1 = {coords1[0], (coords1[1]+1) % 5 }; //modulo 5 to allow for wraparound, wrapround on same row 
            new_coords2 = {coords2[0], (coords2[1]+1) % 5 };
        }   // if same column, second number is the same, push_back letters below 
        else if (coords1[1] == coords2[1]) {
            new_coords1 = { (coords1[0]+1) % 5, coords1[1] };
            new_coords2 = { (coords2[0]+1) % 5, coords2[1] };
        } // If they form a rectangle, replace with ones from corner on the same row
        else {
            // Don't need any modulo, there's no incrementation. 
            new_coords1[0] = coords1[0];
            new_coords2[0] = coords2[0];
            new_coords1[1] = coords2[1];
            new_coords2[1] = coords1[1]; 
        }

        // Find the letter associated with the new coordinates 
        auto revMap_iter1 = myrevmap.find({new_coords1[0], new_coords1[1]});
        auto revMap_iter2 = myrevmap.find({new_coords2[0], new_coords2[1]});
        char new_let1 { (*revMap_iter1).second};
        char new_let2 { (*revMap_iter2).second};
        
        // Print out the new coordinates & letter to check. 
        //std::cout << " New digraph" << std::endl;
        //std::cout << new_let1 << ": [" << new_coords1[0] << "," << new_coords1[1] << "]." << std::endl; 
        //std::cout << new_let2 << ": [" << new_coords2[0] << "," << new_coords2[1] << "]." << std::endl; 
   
        // Append the new characters to the new string 
        cipher_string += new_let1;
        cipher_string += new_let2;
    }
    // return the text   
    //std::cout << cipher_string << std::endl;
    if (cipherMode == CipherMode::Encrypt) {  
        outputText = cipher_string;
        return outputText;
    }
    else {
        std::cout << "Sorry, I haven't the decrypt yet" << std::endl;
        return inputText;
    }
}

