#include <SFML/Audio.hpp>

int main()
{
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("videoplayback.wav"))
    {
        return -1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    sound.play();
    while (sound.getStatus() == sf::Sound::Playing)
    {
    }

    return 0;
}