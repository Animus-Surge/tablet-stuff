#pragma once

/**
 * @brief AnimationTrack class and animation functions
 */

#include <cmath>
#include <functional>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

// Keyframe struct
template <typename T> // T is the type of the value of the keyframe
struct Keyframe {
    std::string widgetName;
    float time;
    T value;
};

// AnimationTrack class
template <typename T> // T is the type of the value of the keyframe
class AnimationTrack {
private:
    // Keyframes
    std::vector<Keyframe> keyframes;

    // Animation properties
    float duration;
    bool loop;
    bool playing;

    // Timing
    int currentKeyframeIdx;
    float currentTime;

    // Callback function to be called when a keyframe is reached
    std::function<void(Keyframe)> onKeyframe;

public:
    AnimationTrack();
    ~AnimationTrack();

    // Keyframe functions
    void addKeyframe(Keyframe keyframe);
    void putKeyframe(int index, Keyframe keyframe);
    void removeKeyframe(int index);

    // Animation functions
    void play();
    void stop();
    void pause();

    // Update function, called by scene
    void update(float deltaTime);

    // Setters
    void setLoop(bool loop) { this->loop = loop; }
    void setDuration(float duration) { this->duration = duration; }
    void setPlaying(bool playing) { this->playing = playing; }
    void setKeyframes(std::vector<Keyframe> keyframes) { this->keyframes = keyframes; }
    void setKeyframe(int index, Keyframe keyframe) { this->keyframes[index] = keyframe; }
    void setKeyframeValue(int index, T value) { this->keyframes[index].value = value; }
    void setKeyframeTime(int index, float time) { this->keyframes[index].time = time; }
    void setKeyframeWidgetName(int index, std::string widgetName) { this->keyframes[index].widgetName = widgetName; }

    // Getters
    bool isPlaying() { return playing; }
    bool isLooping() { return loop; }
    float getDuration() { return duration; }
    std::vector<Keyframe> getKeyframes() { return keyframes; }
    Keyframe getKeyframe(int index) { return keyframes[index]; }
    T getKeyframeValue(int index) { return keyframes[index].value; }
    float getKeyframeTime(int index) { return keyframes[index].time; }
    std::string getKeyframeWidgetName(int index);
    int getKeyframeCount();
    int getKeyframeIndex(float time);

    // Clear all properties to default values
    void clear();

};

// Linear interpolation function
template <typename T>
T lerp(T a, T b, float t) {
    return a + (b - a) * t;
}

// Easing functions
template <typename T>
T easeInQuad(T a, T b, float t) {
    return lerp(a, b, t * t);
}

template <typename T>
T easeOutQuad(T a, T b, float t) {
    return lerp(a, b, 1 - (1 - t) * (1 - t));
}

template <typename T>
T easeInOutQuad(T a, T b, float t) {
    return lerp(a, b, t < 0.5 ? 2 * t * t : 1 - pow(-2 * t + 2, 2) / 2);
}

// Serialization
void to_json(json& j, const Keyframe& keyframe);
void from_json(const json& j, Keyframe& keyframe);

void to_json(json& j, const AnimationTrack& animation);
void from_json(const json& j, AnimationTrack& animation);
