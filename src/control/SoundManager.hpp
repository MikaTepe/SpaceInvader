#ifndef SOUNDMANAGER_HPP
#define SOUNDMANAGER_HPP

#include <SFML/Audio.hpp>
#include <map>
#include <string>

enum class SoundEffect {
    PlayerShoot,
    InvaderShoot,
    PlayerKilled,
    InvaderKilled
};

class SoundManager {
public:
    SoundManager();
    void play(SoundEffect effect);

private:
    void loadSound(SoundEffect effect, const std::string& filename);

    std::map<SoundEffect, sf::SoundBuffer> soundBuffers;
    std::vector<sf::Sound> sounds; // Vektor, um mehrere Sounds gleichzeitig abspielen zu können
};

#endif //SOUNDMANAGER_HPP
