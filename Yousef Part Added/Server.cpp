#include <iostream>
#include <vector>
#include <memory>
#include <mutex>
#include <algorithm>

#include <boost/asio.hpp>
#include "json.hpp"

using boost::asio::ip::tcp;
using boost::asio::awaitable;
using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::use_awaitable;
using boost::asio::as_tuple;

using json = nlohmann::json;

std::vector<std::shared_ptr<tcp::socket>> clients;
std::mutex clients_mutex;

awaitable<void> broadcast_message(const std::string& message,
                                  std::shared_ptr<tcp::socket> sender_socket)
{
    std::vector<std::shared_ptr<tcp::socket>> clients_copy;

    {
        std::lock_guard<std::mutex> lock(clients_mutex);
        clients_copy = clients;
    }

    for (auto& client : clients_copy)
    {
        if (client && client->is_open() && client != sender_socket)
        {
            boost::system::error_code ec;

            co_await boost::asio::async_write(
                *client,
                boost::asio::buffer(message + "\n"),
                boost::asio::redirect_error(use_awaitable, ec)
                );

            if (ec)
            {
                std::cout << "Broadcast error: " << ec.message() << std::endl;
            }
        }
    }
}

void remove_client(std::shared_ptr<tcp::socket> socket)
{
    std::lock_guard<std::mutex> lock(clients_mutex);

    clients.erase(
        std::remove(clients.begin(), clients.end(), socket),
        clients.end()
        );
}

awaitable<void> handle_client(std::shared_ptr<tcp::socket> socket)
{
    char data[2048];

    while (true)
    {
        auto [read_ec, bytes_read] = co_await socket->async_read_some(
            boost::asio::buffer(data),
            as_tuple(use_awaitable)
            );

        if (read_ec)
        {
            std::cout << "Client disconnected: " << read_ec.message() << std::endl;
            remove_client(socket);
            break;
        }

        std::string received_text(data, bytes_read);

        try
        {
            json incoming_json = json::parse(received_text);

            std::string action = incoming_json.value("action", "");

            if (action == "CHAT_MSG")
            {
                std::string sender = incoming_json.value("sender", "Unknown");
                std::string content = incoming_json.value("content", "");
                std::string room = incoming_json.value("room_id", "");

                std::cout << "[" << room << "] "
                          << sender << ": "
                          << content << std::endl;

                json outgoing;
                outgoing["action"] = "CHAT_MSG";
                outgoing["room_id"] = room;
                outgoing["sender"] = sender;
                outgoing["content"] = content;

                co_await broadcast_message(outgoing.dump(), socket);
            }
            else if (action == "JOIN_GROUP")
            {
                std::string username = incoming_json.value("username", "Unknown");
                std::string room = incoming_json.value("room_id", "");

                std::cout << username
                          << " joined room "
                          << room << std::endl;
            }
            else
            {
                std::cout << "Unknown action: " << action << std::endl;
            }
        }
        catch (std::exception& e)
        {
            std::cout << "JSON error: "
                      << e.what()
                      << std::endl;
        }
    }
}

awaitable<void> listener()
{
    auto executor = co_await boost::asio::this_coro::executor;

    tcp::acceptor acceptor(executor, {tcp::v4(), 54321});

    std::cout << "StudyBuddy Server running on 127.0.0.1:54321"
              << std::endl;

    while (true)
    {
        auto [ec, socket] =
            co_await acceptor.async_accept(as_tuple(use_awaitable));

        if (!ec)
        {
            auto client =
                std::make_shared<tcp::socket>(std::move(socket));

            {
                std::lock_guard<std::mutex> lock(clients_mutex);
                clients.push_back(client);
            }

            std::cout << "Client connected!" << std::endl;

            co_spawn(executor,
                     handle_client(client),
                     detached);
        }
        else
        {
            std::cout << "Accept error: " << ec.message() << std::endl;
        }
    }
}

int main()
{
    boost::asio::io_context io_context;

    co_spawn(io_context,
             listener(),
             detached);

    io_context.run();

    return 0;
}
