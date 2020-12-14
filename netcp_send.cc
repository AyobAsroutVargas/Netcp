#include "netcp.hpp"

int protected_main() {
  netcp::Socket socket_send("10.0.2.15", 1024);
  char* filename = "prueba.txt";
  netcp::File file_send(filename, O_RDONLY);

  netcp::Message message;
  size_t count = 1023;
  std::array<char , 1024> clean_message{};
  sockaddr_in address{netcp::make_ip_address(1024, "127.0.0.1")};
  while ( file_send.read_from_file(&message.text, count) != 0 ) {
    message.text[1023] = '\0';
    //std::cout << message.text.data() << std::endl;
    socket_send.send_to(message,address);
    //message.text=clean_message;
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