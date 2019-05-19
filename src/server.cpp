#include "../inc/server.hpp"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>


        server::server(const std::string &address, const std::string &port,
                        std::size_t threads_num)
                : threads_num(threads_num),
                  signals_(io_context_),
                  acceptor_(io_context_),
                  new_connection_(),
                  request_handler_() {
            signals_.add(SIGINT);
            signals_.add(SIGTERM);

            signals_.async_wait(boost::bind(&server::handle_stop, this));

            boost::asio::ip::tcp::resolver resolver(io_context_);
            boost::asio::ip::tcp::endpoint endpoint =
                    *resolver.resolve(address, port).begin();
            acceptor_.open(endpoint.protocol());
            acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
            acceptor_.bind(endpoint);
            acceptor_.listen();
            start_accept();
        }

        void server::run() {
            std::vector<std::thread> threads;
            for (std::size_t i = 0; i < 4; ++i) {
                threads.emplace_back([&] { io_context_.run(); });
            }
            for (auto &thread : threads)
                thread.join();
        }

        void server::start_accept() {
            new_connection_.reset(new connection(io_context_, request_handler_));
            acceptor_.async_accept(new_connection_->socket(),
                                   boost::bind(&server::handle_accept, this,
                                               boost::asio::placeholders::error));
        }

        void server::handle_accept(const boost::system::error_code &e) {
            if (!e) {
                new_connection_->start();
            }
            start_accept();
        }

        void server::handle_stop() {
            io_context_.stop();
        }

