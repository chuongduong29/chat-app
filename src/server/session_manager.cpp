#include "session_manager.h"
#include "session.h"
#include <iostream>

void SessionManager::join(std::shared_ptr<Session> session) {
    std::lock_guard<std::mutex> lock(mutex_);
    sessions_.insert(session);
    std::cout << "Client joined. Total: " << sessions_.size() << std::endl;
}

void SessionManager::leave(std::shared_ptr<Session> session) {
    std::lock_guard<std::mutex> lock(mutex_);
    sessions_.erase(session);
    std::cout << "Client left. Total: " << sessions_.size() << std::endl;
}

void SessionManager::broadcast(const std::string& msg,
                               std::shared_ptr<Session> sender) {
    std::lock_guard<std::mutex> lock(mutex_);

    for (auto& session : sessions_) {
        if (session != sender) {
            session->send(msg);
        }
    }
}

