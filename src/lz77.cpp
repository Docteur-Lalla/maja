#include "lz77.h"

#include <queue>
#include <algorithm>
#include <sstream>

#include <iostream>

namespace maja
{
  lz77_encoder::lz77_encoder() : text(std::string())
  {
  }
  
  lz77_encoder::lz77_encoder(const std::string& input) : text(input)
  {
  }
  
  std::string lz77_encoder::apply(const std::string& input)
  {
    text = input;
    return (*this)();
  }
  
  std::string lz77_encoder::operator()()
  {
    lz77::lookahead_buffer lk_buffer = initialize();
    std::queue<lz77_encoder::reference> refs;
    
    for(size_t i = 0; i < lk_buffer.buffer; ++i)
    {
      lz77_encoder::reference ref;
      
      ref.pos = 0;
      ref.size = 0;
      ref.next = text[i];
      
      refs.push(ref);
    }
    
    while(lk_buffer.buffer < lk_buffer.end)
    {
      refs.push(next_reference(lk_buffer));
    }
    
    std::stringstream ss;
    
    while(!refs.empty())
    {
      lz77_encoder::reference ref = refs.front();
      refs.pop();
      
      short pos = static_cast<short>(ref.pos);
      short size = static_cast<short>(ref.size);
      char next = ref.next;
      
      ss.write(reinterpret_cast<char*>(&pos), sizeof(short));
      ss.write(reinterpret_cast<char*>(&size), sizeof(short));
      ss.put(next);
    }
    
    return ss.str();
  }
  
  std::string lz77_encoder::operator()(const std::string& input)
  {
    text = input;
    return (*this)();
  }
  
  lz77::lookahead_buffer lz77_encoder::initialize()
  {
    lz77::lookahead_buffer lk_buffer;
    
    lk_buffer.window = 0;
    lk_buffer.buffer = 10;
    lk_buffer.end = 15;
    
    return lk_buffer;
  }
  
  lz77_encoder::reference lz77_encoder::next_reference(lz77::lookahead_buffer& lk_buffer)
  {
    size_t size = lk_buffer.end - lk_buffer.buffer;
    size_t found = lk_buffer.buffer;
    
    while(size != 0 && found == lk_buffer.buffer)
    {
      std::string pattern = text.substr(lk_buffer.buffer, size);
      found = text.find(pattern, lk_buffer.window);
      
      if(found == lk_buffer.buffer)
        size--;
    }
    
    lz77_encoder::reference ref;
    
    if(size != 0)
    {
      ref.pos = lk_buffer.buffer - found;
      ref.size = size;
      ref.next = text[lk_buffer.buffer + size];
      
      lk_buffer.window += size + 1;
      lk_buffer.buffer += size + 1;
      lk_buffer.end = std::min(lk_buffer.end + size + 1, text.size() - 1);
    }
    
    else
    {
      ref.pos = 0;
      ref.size = 0;
      ref.next = text[lk_buffer.buffer];
      
      lk_buffer.window += 1;
      lk_buffer.buffer += 1;
      lk_buffer.end = std::min(lk_buffer.end + 1, text.size() - 1);
    }
    
    return ref;
  }
  
  lz77_decoder::lz77_decoder() : text(std::string())
  {
  }
  
  lz77_decoder::lz77_decoder(const std::string& input) : text(input)
  {
  }
  
  std::string lz77_decoder::apply(const std::string& input)
  {
    text = input;
    return (*this)();
  }
  
  std::string lz77_decoder::operator()()
  {
    //std::stringstream ss(text);
    std::string input(text);
    std::string result;
    
    while(!text.empty())
    {
      short pos;
      short size;
      char next;
      
      pos = text[0] + (text[1] << 4);
      size = text[2] + (text[3] << 4);
      next = text[4];
      
      text.erase(0, 5);
      
      if(size == 0)
      {
        result += next;
      }
      
      else
      {  
        std::string add = result.substr(result.size() - pos, size);
        result += add + next;
      }
    }
    
    return result;
  }
  
  std::string lz77_decoder::operator()(const std::string& input)
  {
    text = input;
    return (*this)();
  }
}

