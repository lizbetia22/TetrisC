module;
#include <SFML/Audio.hpp>
#include <memory>

export module songController;

export namespace songController {
    class SongPlayer {
    public:
        SongPlayer();
        void loadBackgroundMusic(const std::string& filename) const;
        void playCollisionSound(const std::string& filename) const;
        void playGameOverSound(const std::string& filename) const;
        void stop() const;
        void pause() const;
        void resume() const;
        void setBackgroundVolume(float volume) const;
        void setCollisionSoundVolume(float volume) const;

        void operator()(const std::string& filename, bool isBackground = true) const;
        bool operator==(const SongPlayer& other) const;

        ~SongPlayer();

    private:
        std::unique_ptr<sf::Music> backgroundMusic;
        std::unique_ptr<sf::SoundBuffer> soundBuffer;
        std::unique_ptr<sf::Sound> collisionSound;
    };
}