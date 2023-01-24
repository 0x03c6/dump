#include <asio.hpp>
#include <iostream>
#include <cstdlib>

using namespace asio;

// overload << operator for std::ostream for easier debugging
class dbg_err : public error_code {
  friend std::ostream& operator<<(std::ostream& out, const dbg_err& e) {
    out << e.value() << ". Message: " << e.message();
    return out;
  }
};

int main(int argc, char** argv) {
  // instantiate custom debug error code class
  dbg_err err;
  // handle to our io service
  io_service io;
  if (argc > 2) {
    // ip protocol version independent address representation
    ip::address addr =
      ip::address::from_string(std::string(argv[1]), err);
    // check error code value  
    if (err.value() != 0) {
      std::cout << "Failed to parse ip address" << err;
      return err.value();
    }
    // establish endpoint
    auto ep = ip::tcp::endpoint(addr, (unsigned short)atol(argv[2]));

    // instantiate protocol class
    auto proto = ip::tcp::v4();
    // active tcp socket object
    auto sock = ip::tcp::socket(io); 
    // open socket
    sock.open(proto, err);
    if (err.value() != 0) {
      std::cout << "Failed to open socket" << err;
      return err.value();
    }

  } else
    printf("Usage: %s <address> <port>\n", argv[0]);
  return 0;
}
