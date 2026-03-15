#pragma once

#include <functional>
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>

struct Event {
    virtual ~Event() = default;
};

class EventBus {
public:
    template<typename EventType>
    void subscribe(std::function<void(const EventType&)> listener) {
        auto& listeners = subscribers[typeid(EventType)];
        listeners.push_back(
            [listener](const Event& e) {
                listener(static_cast<const EventType&>(e));
            }
        );
    }

    template<typename EventType>
    void emit(const EventType& event) {
        auto it = subscribers.find(typeid(EventType));
        if (it != subscribers.end()) {
            for (auto& listener : it->second) {
                listener(event);
            }
        }
    }

private:
    std::unordered_map<std::type_index, std::vector<std::function<void(const Event&)>>> subscribers;
};