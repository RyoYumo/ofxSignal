#ifndef OFX_SIGNAL_H_
#define OFX_SIGNAL_H_

#include <functional>
#include "ofEvents.h"

namespace ofx{
template<typename T>
class Signal {
public:
    Signal(){
        ofAddListener(event_, this, &Signal::call);
    }
    ~Signal(){
        ofRemoveListener(event_, this, &Signal::call);
    }
    template<typename Callback>
    void connect(Callback&& callback){
        callback_obj_ = std::forward<Callback>(callback);
    }
    
    void emit(T& arg){
        ofNotifyEvent(event_, arg);
    }
    
    
private:
    ofEvent<T> event_;
    std::function<void(T&)> callback_obj_;
    void call(T& arg){
        if(callback_obj_){
            callback_obj_(arg);
        }
    }
};

template<>
class Signal<void> {
public:
    Signal(){
        ofAddListener(event_, this, &Signal::call);
    }
    ~Signal(){
        ofRemoveListener(event_, this, &Signal::call);
    }
    
    template<typename Callback>
    void connect(Callback&& callback){
        callback_obj_ = std::forward<Callback>(callback);
    }
    
    void emit(){
        ofNotifyEvent(event_);
    }
    
private:
    ofEvent<void> event_;
    std::function<void(void)> callback_obj_;
    void call(){
        if(callback_obj_){
            callback_obj_();
        }
    }
};
} // namespace ofx

template<typename T>
using ofxSignal = ofx::Signal<T>;

using ofxSignalVoid  = ofxSignal<void>;
using ofxSignalInt   = ofxSignal<int>;
using ofxSignalFloat = ofxSignal<float>;
using ofxSignalVec3  = ofxSignal<glm::vec3>;


#endif // OFX_SIGNAL_H_
