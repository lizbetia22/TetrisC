module;

#include <SFML/Audio.hpp>

export module songController;

export namespace songController {
    class SongPlayer{
    public:
        SongPlayer();

        void loadBackgroundMusic(const std::string& filename);
        void playCollisionSound(const std::string& filename);
        void playGameOverSound(const std::string& filename);
        void stop();
        void pause();
        void resume();
        void setBackgroundVolume(float volume);
        void setCollisionSoundVolume(float volume);

       ~SongPlayer();

    private:
        sf::Music backgroundMusic;
        sf::SoundBuffer soundBuffer;
        sf::Sound collisionSound;
    };
};