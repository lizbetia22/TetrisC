module;
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>
#include <functional>

module songController;

namespace songController {
    SongPlayer::SongPlayer() :
        backgroundMusic(std::make_unique<sf::Music>()),
        soundBuffer(std::make_unique<sf::SoundBuffer>()),
        collisionSound(std::make_unique<sf::Sound>()) {}

    void SongPlayer::operator()(const std::string& filename, bool isBackground) const {
        auto playMusic = [this, &filename, isBackground]() {
            if (isBackground) {
                loadBackgroundMusic(filename);
            } else {
                playCollisionSound(filename);
            }
        };
        playMusic();
    }

    bool SongPlayer::operator==(const SongPlayer& other) const {
        return backgroundMusic.get() == other.backgroundMusic.get();
    }

    void SongPlayer::loadBackgroundMusic(const std::string& filename) const {
        if (!backgroundMusic->openFromFile(filename)) {
            throw std::runtime_error("Unable to load background music file: " + filename);
        }
        backgroundMusic->setLoop(true);
        backgroundMusic->play();
    }

    void SongPlayer::playCollisionSound(const std::string& filename) const {
        auto playSound = [this, &filename]() {
            if (!soundBuffer->loadFromFile(filename)) {
                throw std::runtime_error("Unable to load collision sound file: " + filename);
            }
            collisionSound->setBuffer(*soundBuffer);
            collisionSound->play();
        };
        playSound();
    }

    void SongPlayer::playGameOverSound(const std::string& filename) const {
        playCollisionSound(filename);
    }

    void SongPlayer::stop() const {
        if (backgroundMusic) backgroundMusic->stop();
    }

    void SongPlayer::pause() const {
        if (backgroundMusic) backgroundMusic->pause();
    }

    void SongPlayer::resume() const {
        if (backgroundMusic) backgroundMusic->play();
    }

    void SongPlayer::setBackgroundVolume(float volume) const {
        if (backgroundMusic) backgroundMusic->setVolume(volume);
    }

    void SongPlayer::setCollisionSoundVolume(float volume) const {
        if (collisionSound) collisionSound->setVolume(volume);
    }

    SongPlayer::~SongPlayer() {
        stop();
    }
}