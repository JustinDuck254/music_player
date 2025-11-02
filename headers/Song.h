#pragma once
#ifndef SONG_H
#include <string>
class Song{
    private:
        std::string title, artist;
        int duration; //seconds
    public:
        void setTitle(std::string title);
        void setartist(std::string artist);
        void setduration(int duration);

        std::string getTitle();
        std::string getAritst();
        int getDuration();

        void displayInfo();
};
#endif