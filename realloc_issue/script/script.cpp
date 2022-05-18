// #include <string>
// #include <iostream>
// #include <cstdio>

// void sayHello(){
//     std::cout << "hello!" << std::endl;
// }

// auto main(int argc, char* argv[]) -> int {
//     static int rc = 0;
// #if __wasi__
//     if (argc == 0) rc += 1;
//     std::string str{"hello form wasm"};
// #else
//     if (argc == 0) rc += 2;
//     std::string str{"hello form cxx"};
// #endif
//     std::cout << str << std::endl;
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

extern "C" {

void test()
{
  void* holder = malloc(3145);
  printf("holder=%p\n", holder);
  void* buf = NULL;
  printf("buf=%p \n", buf);
  buf = realloc(buf, 1256);
  printf("buf=%p \n", buf);
}
}