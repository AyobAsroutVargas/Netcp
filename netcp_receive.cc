#include "netcp.hpp"

int protected_main() {
  netcp::Socket socket_receive("127.0.0.1", 1024);
  netcp::Message message;
  sockaddr_in address{netcp::make_ip_address(1024, "10.0.2.15")};
  while (1 == 1) {
    socket_receive.receive_from(message, address);
  }
  return 0;
}

int main() {
  try {
    return protected_main();
  }    
  catch(std::bad_alloc& e) {
    std::cerr << "mytalk" << ": memoria insuficiente\n";
    return 1;
  }
  catch(std::system_error& e) {
    std::cerr << "mitalk" << ": " << e.what() << '\n';
    return 2;
  }
  catch (...) {
    std::cout << "Error desconocido\n";
    return 99;
  }
}