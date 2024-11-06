#include "objects/animation.h"

// Keyframe functions
void AnimationTrack::addKeyframe(Keyframe keyframe) {
    this->keyframes.push_back(keyframe);
}

void AnimationTrack::putKeyframe(int index, Keyframe keyframe) {
    if(index < 0 || index >= this->keyframes.size()) return;
    this->keyframes[index] = keyframe;
}

void AnimationTrack::removeKeyframe(int index) {
    this->keyframes.erase(this->keyframes.begin() + index);
}

// Animation functions

void AnimationTrack::play() {
    this->playing = true;
}

void AnimationTrack::stop() {
    this->playing = false;
    this->currentKeyframeIdx = 0;
    this->currentTime = 0;
}

void AnimationTrack::pause() {
    this->playing = false;
}

// Update function, called by scene
void AnimationTrack::update(float deltaTime) {
    if (!this->playing) return;

    this->currentTime += deltaTime;

    if (this->currentTime >= this->duration) {
        if (this->loop) {
            this->currentTime = 0;
            this->currentKeyframeIdx = 0;
        } else {
            this->playing = false;
            return;
        }
    }

    // Check time to see if we need to move to the next keyframe
    if(this->currentTime >= this->keyframes[this->currentKeyframeIdx].time) {
        this->currentKeyframeIdx++;

        if(this.onKeyframe) {
            this.onKeyframe(this->keyframes[this->currentKeyframeIdx]);
        }

        if(this->currentKeyframeIdx >= this->keyframes.size()) {
            if(this->loop) {
                this->currentKeyframeIdx = 0;
            } else {
                this->playing = false;
            }
        }
    }
}


