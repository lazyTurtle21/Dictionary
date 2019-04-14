//
// Created by tymchenko on 14.04.2019.
//

#include "../inc/session.hpp"

void Session::read_body(const std::shared_ptr<Session> &pThis) {
    size_t nbuffer = 1000;
    std::shared_ptr<std::vector<char>> bufptr =
            std::make_shared<std::vector<char>>(nbuffer);
    boost::asio::async_read(pThis->socket, boost::asio::buffer(*bufptr, nbuffer),
                            [pThis](const std::error_code &e, std::size_t s) {
                            });
}

void Session::read_next_line(const std::shared_ptr<Session> &pThis) {
    boost::asio::async_read_until(pThis->socket, pThis->buff, '\r',
                                  [pThis](const std::error_code &e, std::size_t s) {
                                      std::string line, ignore;
                                      std::istream stream{&pThis->buff};
                                      std::getline(stream, line, '\r');
                                      std::getline(stream, ignore, '\n');
                                      pThis->headers.on_read_header(line);

                                      if (line.length() == 0) {
                                          if (pThis->headers.content_length() == 0) {
                                              std::shared_ptr<std::string> str =
                                                      std::make_shared<std::string>(pThis->headers.get_response());
                                              boost::asio::async_write(
                                                      pThis->socket,
                                                      boost::asio::buffer(str->c_str(), str->length()),
                                                      [pThis, str](const std::error_code &e, std::size_t s) {
                                                          std::cout << "done" << std::endl;
                                                      });
                                          } else {
                                              pThis->read_body(pThis);
                                          }
                                      } else {
                                          pThis->read_next_line(pThis);
                                      }
                                  });
}

void Session::read_first_line(const std::shared_ptr<Session> &pThis) {
    boost::asio::async_read_until(pThis->socket, pThis->buff, '\r',
                                  [pThis](const std::error_code &e, std::size_t s) {
                                      std::string line, ignore;
                                      std::istream stream{&pThis->buff};
                                      std::getline(stream, line, '\r');
                                      std::getline(stream, ignore, '\n');
                                      pThis->headers.on_read_request_line(line);
                                      pThis->read_next_line(pThis);
                                  });
}

