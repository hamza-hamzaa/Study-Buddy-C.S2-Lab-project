 #include <iostream>
// #include <string_view>
#include <boost/asio.hpp>
#include "json.hpp" // Ahmed's JSON library!

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::as_tuple;

// Give the JSON library a simple nickname
using json = nlohmann::json;

awaitable<void> handle_client(tcp::socket socket) {
    char data[1024];

    while (true) {
        auto [read_ec, bytes_read] = co_await socket.async_read_some(
            boost::asio::buffer(data),
            as_tuple(use_awaitable)
            );

        if (read_ec) {
            std::cout << "Client disconnected: " << read_ec.message() << "\n";
            break;
        }

        // 1. Convert the raw data into a C++ string
        std::string received_text(data, bytes_read);

        try {
            // 2. Parse the text into a JSON object
            json incoming_json = json::parse(received_text);

            // 3. Create an empty JSON object for our reply
            json reply_json;

            // 4. Check what "action" the client wants to do
            std::string action = incoming_json.value("action", "unknown");

            if (action == "login") {
                std::string username = incoming_json.value("username", "Guest");
                std::cout << "[SERVER] " << username << " just logged in!\n";

                reply_json["status"] = "success";
                reply_json["message"] = "Welcome to StudyBuddy, " + username + "!";

            }
            else if (action == "send_message") {
                std::string text = incoming_json.value("text", "");
                std::cout << "[SERVER] Chat received: " << text << "\n";

                reply_json["status"] = "delivered";
            }
            else {
                reply_json["error"] = "Unknown action requested.";
            }

            // 5. Convert our JSON reply back to raw text so we can send it
            std::string reply_text = reply_json.dump();

            auto [write_ec, bytes_written] = co_await boost::asio::async_write(
                socket,
                boost::asio::buffer(reply_text),
                as_tuple(use_awaitable)
                );

            if (write_ec) {
                std::cout << "Write error: " << write_ec.message() << "\n";
                break;
            }

        } catch (json::parse_error& e) {
            // If the client sends random garbage that isn't JSON, it safely catches the error here
            std::cout << "Received bad JSON format: " << e.what() << "\n";
        }
    }
}

awaitable<void> listener() {
    auto io_ctx = co_await boost::asio::this_coro::executor;
    tcp::acceptor acceptor(io_ctx, { tcp::v4(), 54321 });

    std::cout << "Server is listening on 127.0.0.1: port 54321...\n";

    while (true) {
        auto [ec, socket] = co_await acceptor.async_accept(as_tuple(use_awaitable));

        if (!ec) {
            std::cout << "New client connected!\n";
            co_spawn(io_ctx, handle_client(std::move(socket)), detached);
        }
        else {
            std::cout << "Accept error: " << ec.message() << "\n";
        }
    }
}

int main() {
    boost::asio::io_context io_context;
    co_spawn(io_context, listener(), detached);
    io_context.run();
    return 0;
}