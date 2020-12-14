/** 
 * Universidad de La Laguna
 * Asignatura: Sistemas Operativos
 * Primer prototipo netcp
 * @author Ayob Asrout Vargas
 * @date 14/12/2020
 * Contact: alu0101350158@ull.edu.es
 * 
 * Namespace que contiene todo lo necesario para la ejecucion tanto de netcp-send
 * como de netcp-receive
 */

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <system_error>
#include <unistd.h>

namespace netcp{

  struct Message {
    std::array<char, 1024> text;
  };

  class Socket {
   public:
    Socket(const std::string& ip_address, int port);
    ~Socket();

    void send_to(const Message& message, const sockaddr_in& address);
    void send_to(const std::string& message, const sockaddr_in& address);

    void receive_from(Message& message, sockaddr_in& address);
   private:
    void create_socket(const sockaddr_in& address);
    int fd_;
  };

  class File {
   public:
    File(const char* pathname, int flags);
    ~File();
    ssize_t read_from_file(void* buf, size_t count);
    ssize_t write_to_file(void* buf, size_t count);
    int fd;
  };

  sockaddr_in make_ip_address(int port, const std::string& ip_address = "kk");
}
