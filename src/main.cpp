#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "../inc/server.hpp"

int main(int argc, char *argv[]) {
    try {
        // Check command line arguments.
        if (argc != 3) {
            std::cerr << "Usage: http_server <address> <port> \n";
            std::cerr << "  For IPv4, try:\n";
            std::cerr << "    receiver 127.0.0.1 8080 \n";
            return 1;
        }

        // Initialise the server.
        std::size_t num_threads = std::thread::hardware_concurrency();
        server s(argv[1], argv[2], num_threads);

        // Run the server until stopped.
        s.run();
    }
    catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}
