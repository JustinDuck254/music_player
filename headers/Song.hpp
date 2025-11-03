#pragma once
#ifndef SONG_HPP
#include <string>
#include <sstream>
class Song{
    private:
        std::string title, artist;
        int duration; //seconds
    public:
        Song(){};
        Song(std::string title, std::string artist, int duration);
        void setTitle(std::string title);
        void setArtist(std::string artist);
        void setDuration(int duration);

        std::string getTitle();
        std::string getAritst();
        int getDuration();

        std::string toString();
};
#endif