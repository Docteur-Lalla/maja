#ifndef MAJA_LZ77_H
#define MAJA_LZ77_H

#include <string>

namespace maja
{
  namespace lz77
  {
    struct lookahead_buffer
    {
      size_t window;
      size_t buffer;
      size_t end;
    };
  }

  class lz77_encoder
  {
    public:
      lz77_encoder();
      lz77_encoder(const std::string& input);
      
      std::string apply(const std::string& input);
      std::string operator()();
      std::string operator()(const std::string& input);
      
      struct reference
      {
        size_t pos;
        size_t size;
        char next;
      };
    
    private:
      lz77::lookahead_buffer initialize();
      reference next_reference(lz77::lookahead_buffer& lk_buffer);
    
      std::string text;
  };
  
  class lz77_decoder
  {
    public:
      lz77_decoder();
      lz77_decoder(const std::string& input);
      
      std::string apply(const std::string& input);
      std::string operator()();
      std::string operator()(const std::string& input);
    
    private:      
      std::string text;
  };
}

#endif

