#ifndef MAJA_BURROWS_WHEELER_TRANSFORM_HPP
#define MAJA_BURROWS_WHEELER_TRANSFORM_HPP

#include <string>
#include <deque>
#include <vector>

namespace maja
{
  /* Encoder for the Burrows-Wheeler Transform */
  class bwt_encoder
  {
    public:
      bwt_encoder();
      bwt_encoder(const std::string& input);
      
      std::string apply(const std::string& input);
      std::string operator()();
      std::string operator()(const std::string& input);

      /*
         A permutation is the input string whose characters
         have been shifted by num to the right with the last
         characters put at the begining of the new string
       */
      struct permutation
      {
        size_t num;
        size_t shift;
        size_t size;
      };

    private:
      void initialize(); // Initialize the permutations
      bool compare(permutation p1, permutation p2);

      std::string text;
      std::deque<permutation> perms;
  };
  
  /* Decoder for the Burrows-Wheeler Transform */
  class bwt_decoder
  {
    public:
      bwt_decoder();
      bwt_decoder(const std::string& input);
      
      std::string apply(const std::string& input);
      std::string operator()();
      std::string operator()(const std::string& input);
    
    private:
      void initialize();
    
      std::string text;
      std::string first;
      
      size_t position;
      
      std::vector<unsigned int> vec; // Transform vector
  };
}

#endif

