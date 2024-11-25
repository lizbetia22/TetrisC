module;

#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>

module songController;

namespace songController {

    SongPlayer::SongPlayer() : backgroundMusic(), soundBuffer(), collisionSound() {}

    void SongPlayer::loadBackgroundMusic(const std::string& filename) {
        if (!backgroundMusic.openFromFile(filename)) {
            throw std::runtime_error("Unable to load background music file: " + filename);
        }
        backgroundMusic.setLoop(true);
        backgroundMusic.play();
    }

    void SongPlayer::playCollisionSound(const std::string& filename) {
        if (!soundBuffer.loadFromFile(filename)) {
            throw std::runtime_error("Unable to load collision sound file: " + filename);
        }
        collisionSound.setBuffer(soundBuffer);
        collisionSound.play();
    }

    void SongPlayer::playGameOverSound(const std::string& filename) {
        if (!soundBuffer.loadFromFile(filename)) {
            throw std::runtime_error("Unable to load game over sound file: " + filename);
        }
        collisionSound.setBuffer(soundBuffer);
        collisionSound.play();
    }

    void SongPlayer::stop() {
        backgroundMusic.stop();
    }

    void SongPlayer::pause() {
        backgroundMusic.pause();
    }

    void SongPlayer::resume() {
        backgroundMusic.play();
    }

    void SongPlayer::setBackgroundVolume(float volume) {
        backgroundMusic.setVolume(volume);
    }

    void SongPlayer::setCollisionSoundVolume(float volume) {
        collisionSound.setVolume(volume);
    }

    SongPlayer::~SongPlayer() {
        stop();
    }
}