
#ifndef HTTP_SERVER3_SERVER_HPP
#define HTTP_SERVER3_SERVER_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "connection.hpp"
#include "response.hpp"



class server
  : private boost::noncopyable
{
public:

  explicit server(const std::string& address, const std::string& port,
       std::size_t thread_pool_size);

  void run();

private:

  void start_accept();

  void handle_accept(const boost::system::error_code& e);


  void handle_stop();
  std::size_t threads_num;
  boost::asio::io_context io_context_;
  boost::asio::signal_set signals_;
  boost::asio::ip::tcp::acceptor acceptor_;
  connection_ptr new_connection_;
  response request_handler_;
};


#endif // HTTP_SERVER3_SERVER_HPP
