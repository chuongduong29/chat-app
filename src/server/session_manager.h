#pragma once
#include <unordered_set>
#include <memory>
#include <mutex>

class Session;

class SessionManager {
public:
    void join(std::shared_ptr<Session> session);
    void leave(std::shared_ptr<Session> session);

private:
    std::unordered_set<std::shared_ptr<Session>> sessions_;
    std::mutex mutex_;
};
