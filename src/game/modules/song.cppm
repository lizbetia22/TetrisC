module;
#include <SFML/Audio.hpp>

export module song;

export namespace song {
    class SongPlayer{
    public:
        SongPlayer();

        void loadAndPlay(const std::string& filename);
        void stop();
        void pause();
        void resume();
        void setVolume(float volume);

       ~SongPlayer();

    private:
        sf::Music music;
    };
};