#include "../src/bwt.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[])
{
  if(argc > 2)
  {
    if(std::string(argv[1]) == "-f")
    {
      std::string filename(argv[2]);
      std::ifstream input(filename.c_str(), std::ios::binary | std::ios::in | std::ios::ate);
      
      if(input)
      {
        std::string str;
        
        {
          std::streampos size;
          
          size = input.tellg();
          char* memblock = new char[size];
          input.seekg(0, std::ios::beg);
          input.read(memblock, size);
          
          str.resize(size);
          for(int i = 0; i < size; ++i)
          {
            str[i] = memblock[i];
          }
          
          delete[] memblock;
          
          input.close();
        }
      
        if(filename.find(".bwt") != std::string::npos)
        {
          std::ofstream output(filename.substr(0, filename.size() - 4).c_str());
          
          std::string bwt = maja::bwt_decoder()(str);
          output << bwt;
        }
        
        else
        {
          std::ofstream output((filename + ".bwt").c_str(),
            std::ofstream::binary | std::ofstream::trunc);
          
          std::string bwt = maja::bwt_encoder()(str);
          output << bwt;
        }
      }
    }
    
    else if(std::string(argv[1]) == "-r")
    {
      std::string str(argv[2]);
      std::string bwt = maja::bwt_decoder()(str);
      
      std::cout << bwt << std::endl;
      std::cout << maja::bwt_encoder()(bwt) << std::endl;
    }
  }
  
  else if(argc == 2)
    {
      std::string str(argv[1]);
      std::string bwt = maja::bwt_encoder()(str);
      
      std::cout << bwt << std::endl;
      std::cout << maja::bwt_decoder()(bwt) << std::endl;
    }

  return 0;
}

