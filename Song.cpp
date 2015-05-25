#include <iostream>
#include <fstream>
#include <string.h>
#include "Song.h"

char Song::songListFile_[ENTRY_SZ] = "";
char Song::currentMP3_[ENTRY_SZ] = "";

const int PATH_SZ = 256;

Song::Song(){

}

Song::~Song(){
    //dtor
}

Song::Song(char *name){
    Song::SetSongPath(name);
}

void Song::ClearListFile(){     //Opens file not in append mode and writes nothing to it clearing the file
    std::ofstream outFile;
    outFile.open(Song::songListFile_);
    outFile << "";
    outFile.close();
    outFile.clear(std::ios_base::goodbit);
}

void Song::SetSongPath(char *path){
    strcpy(songPath_, path);        //Set song Path
    // Rest of this function sets the name of the song.
    char *ptr = strrchr(path, '\\');
    if(ptr == 0){       //if no backslashes are found look for forward slashes.
        ptr = strrchr(path, '/');
        if(ptr == 0){       //if no forward slashes, just copy everything.
            strcpy(songName_, path);
        }
        else{
            strcpy(songName_, ptr+1);
        }
    }
    else{
        strcpy(songName_, ptr+1);
    }
}

const char *Song::GetSongName(){
    return songName_;
}

void Song::AppendToListFile(){
    std::ofstream outFile;
    outFile.open(songListFile_, std::ios_base::app);
    outFile << std::endl << songPath_;
    outFile.close();
    outFile.clear(std::ios_base::goodbit);
}

void Song::PlaySong(){
    //sum gives a unique numeric identified for each song
    unsigned int sum = 0;
    Song::StopSong();
    strcpy(Song::currentMP3_, songName_);
    for(int i = 0; i < strlen(songPath_); i++){
        sum += int(songPath_[i]);
    }
    sum++;
    sum = ~sum;
    sum = sum & 0x000000FF;
    std::cout << std::endl << "Currently Playing " << Song::currentMP3_ << " " << sum << std::endl;
    return;

}

void Song::StopSong(){
    if(currentMP3_[0] == 0){    //no song playing
        return;
    }
    strcpy(Song::currentMP3_, "");
}
