#include "../src/lz77.h"
#include <iostream>

int main(int argc, char *argv[])
{
  if(argc > 1)
  {
    std::string str(argv[1]);
    std::string lz77 = maja::lz77_encoder()(str);
    std::cout << maja::lz77_decoder()(lz77) << std::endl;
  }

  return 0;
}

