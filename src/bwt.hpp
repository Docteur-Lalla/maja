#ifndef MAJA_BURROWS_WHEELER_TRANSFORM_HPP
#define MAJA_BURROWS_WHEELER_TRANSFORM_HPP

#include <string>
#include <deque>
#include <vector>

namespace maja
{
  class bwt_encoder
  {
    public:
      bwt_encoder();
      bwt_encoder(const std::string& input);
      std::string operator()();
      std::string operator()(const std::string& input);

      struct permutation
      {
        size_t num;
        size_t shift;
        size_t size;
      };

    private:
      void initialize();
      bool compare(permutation p1, permutation p2);

      std::string text;
      std::deque<permutation> perms;
  };
  
  class bwt_decoder
  {
    public:
      bwt_decoder();
      bwt_decoder(const std::string& input);
      
      std::string operator()();
      std::string operator()(const std::string& input);
    
    private:
      void initialize();
    
      std::string text;
      std::string first;
      
      size_t position;
      
      std::vector<unsigned int> vec;
  };
}

#endif

