#include "SoundManager.hpp"
#include <iostream>
#include <algorithm>

SoundManager::SoundManager() {
    loadSound(SoundEffect::PlayerShoot, "assets/audio/playerShoot.wav");
    loadSound(SoundEffect::InvaderShoot, "assets/audio/invaderShoot.wav");
    loadSound(SoundEffect::PlayerKilled, "assets/audio/playerKilled.wav");
    loadSound(SoundEffect::InvaderKilled, "assets/audio/invaderKilled.wav");
}

void SoundManager::loadSound(SoundEffect effect, const std::string& filename) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) {
        std::cerr << "Error loading sound file: " << filename << std::endl;
        return;
    }
    soundBuffers[effect] = buffer;
}

void SoundManager::play(SoundEffect effect) {
    // Finde einen freien Sound-Slot oder erstelle einen neuen
    auto it = std::find_if(sounds.begin(), sounds.end(), [](const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Status::Stopped;
    });

    if (it != sounds.end()) {
        it->setBuffer(soundBuffers[effect]);
        it->play();
    } else {
        sounds.emplace_back(soundBuffers[effect]);
        sounds.back().play();
    }
}
