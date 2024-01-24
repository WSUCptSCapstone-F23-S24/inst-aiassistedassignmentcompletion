#ifndef TOKENFORMATTER_H
#define TOKENFORMATTER_H

#include <string>

class TokenFormatter
{
   public:
      static std::string toUpperCase(const std::string &str);
      static char parseLeftmostCharacter(const std::string &str);
      static std::string deleteLeftmostAndRightmostCharacters(const std::string &str);
      static std::string parseCharacters(const std::string &str);
};    

#endif