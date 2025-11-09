#include "Song.hpp"

Song::Song(std::string title, std::string artist, int duration)
{
    this->title = title;
    this->artist = artist;
    this->duration = duration;
}

void Song::setTitle(std::string title)
{
    this->title = title;
}

void Song::setArtist(std::string artist)
{
    this->artist = artist;
}

void Song::setDuration(int duration)
{
    this->duration = duration;
}

std::string Song::getTitle()
{
    return title;
}

std::string Song::getAritst()
{
    return artist;
}

int Song::getDuration()
{
    return duration;
}

std::string Song::toString()
{
    std::ostringstream info;
    info << title << ", " << artist << ", " << duration;
    return info.str();
}