#ifndef OFX_SIGNAL_H_
#define OFX_SIGNAL_H_

#include <functional>
#include <vector>
#include "ofEvents.h"

namespace ofx{
template<typename T>
class Signal {
public:
    using CallbackType = std::function<void(T&)>;
    Signal(){ ofAddListener(event_, this, &Signal::call);}
    ~Signal(){ofRemoveListener(event_, this, &Signal::call);}
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_collection_.push_back(std::forward<Callback>(callback));
    }
    
    void emit(T& arg){ ofNotifyEvent(event_, arg);}
    
private:
    ofEvent<T> event_;
    std::vector<CallbackType> callback_collection_;
    void call(T& arg){
        for(auto& c : callback_collection_) {
            if(c) c(arg);
        }
    }
};

template<>
class Signal<void> {
public:
    using CallbackType = std::function<void(void)>;
    Signal(){ ofAddListener(event_, this, &Signal::call);}
    ~Signal(){ ofRemoveListener(event_, this, &Signal::call);}
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_collection_.push_back(std::forward<Callback>(callback));
    }
    
    void emit(){ ofNotifyEvent(event_);}
private:
    ofEvent<void> event_;
    std::vector<CallbackType> callback_collection_;
    void call(){
        for(auto& c : callback_collection_) {
            if(c) c();
        }
    }
};
} // namespace ofx

template<typename T>
using ofxSignal = ofx::Signal<T>;


#endif // OFX_SIGNAL_H_
