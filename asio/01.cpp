#include <asio.hpp>
#include <iostream>
#include <cstdlib>

using namespace asio;

int main(int argc, char** argv) {
  if (argc > 1) {
    auto ep =
      ip::tcp::endpoint(ip::address_v6::any(), (unsigned short)atol(argv[1]));
  } else
    printf("Usage: %s <port>\n", argv[0]);
  return 0;
}
