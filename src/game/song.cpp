module;
#include <SFML/Audio.hpp>
#include <stdexcept>
#include <string>

module song;
namespace song {

    SongPlayer::SongPlayer() : music() {}

    void SongPlayer::loadAndPlay(const std::string& filename) {
        if (!music.openFromFile(filename)) {
            throw std::runtime_error("Unable to load music file: " + filename);
        }
        music.setLoop(true);
        music.play();
    }

    void SongPlayer::stop() {
        music.stop();
    }

    void SongPlayer::pause() {
        music.pause();
    }

    void SongPlayer::resume() {
        music.play();
    }

    void SongPlayer::setVolume(float volume) {
        music.setVolume(volume);
    }

    SongPlayer::~SongPlayer() {
        stop();
    }

}