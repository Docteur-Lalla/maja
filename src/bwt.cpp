#include "bwt.hpp"

#include <sstream>
#include <functional>
#include <algorithm>

#include <iostream>

namespace maja
{
  bwt_encoder::bwt_encoder() : text(std::string())
  {
  }
  
  bwt_encoder::bwt_encoder(const std::string& input) : text(input)
  {
  }

  std::string bwt_encoder::operator()()
  {
    initialize();
    std::deque<permutation> sorted = perms;

    auto compare_fn = std::bind(&bwt_encoder::compare, this, std::placeholders::_1, std::placeholders::_2);
    std::sort(sorted.begin(), sorted.end(), compare_fn);

    std::stringstream ss;
    size_t i;
    for(i = 0; i < sorted.size(); ++i)
    {
      if(sorted[i].num == 0)
        break;
    }

    ss.write(reinterpret_cast<const char*>(&i), sizeof(i));

    for(auto it = sorted.begin(); it != sorted.end(); ++it)
    {
      ss.put(text[(it->size - 1 + it->num) % it->size]);
    }

    return ss.str();
  }
  
  std::string bwt_encoder::operator()(const std::string& input)
  {
    text = input;
    return (*this)();
  }

  void bwt_encoder::initialize()
  {
    permutation p;
    p.shift = 0;
    p.size = text.size();

    for(size_t i = 0; i < text.size(); ++i)
    {
      p.num = i;
      perms.push_back(p);
    }
  }

  bool bwt_encoder::compare(permutation p1, permutation p2)
  {
    if(p1.size - p1.shift == 0)
      return true;

    size_t at1 = (p1.num + p1.shift) % p1.size;
    char c1 = text[at1];

    size_t at2 = (p2.num + p2.shift) % p2.size;
    char c2 = text[at2];

    if(c1 < c2)
      return true;
    else if(c1 == c2)
    {
      ++(p1.shift);
      ++(p2.shift);

      return compare(p1, p2);
    }

    else
      return false;
  }
  
  
  bwt_decoder::bwt_decoder() : text(std::string())
  {
  }
  
  bwt_decoder::bwt_decoder(const std::string& input) : text(input)
  {
  }
  
  std::string bwt_decoder::operator()()
  {
    initialize();
    
    std::string result;
    size_t at = vec[position];
    
    while(result.size() < text.size())
    {
      result.insert(result.begin(), first[at]);
      at = vec[at];
    }
    
    return result;
  }
  
  std::string bwt_decoder::operator()(const std::string& input)
  {
    text = input;
    return (*this)();
  }
  
  void bwt_decoder::initialize()
  {
    std::stringstream ss(text);
    ss.read(reinterpret_cast<char*>(&position), sizeof(position));
    
    text = ss.str().substr(sizeof(position));
    
    first = text;
    std::sort(first.begin(), first.end());
    
    vec.resize(text.size(), text.size());
    for(size_t i = 0; i < text.size(); ++i)
    {
      size_t pos = 0;
      size_t pos_in_vec;
      size_t n;
      
      do
      {
        pos = first.find_first_of(text[i], pos); /*n | f(n) = l(i)*/
        n = pos;
        pos_in_vec = static_cast<size_t>(std::find(vec.begin(), vec.end(), n) - vec.begin());
        
        ++pos;
      } while(pos_in_vec != vec.size());
      
      vec[i] = n;
    }
  }
}

