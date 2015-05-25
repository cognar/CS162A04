/*
Author: Connor McCloskey
Date: 5/22/15
Assignment: assignment 4, build a text based Mp3 player
Sources: StackOverflow.com
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include "LinkedList.h"
#include "Song.h"

using namespace std;

const int PATH_SZ = 256;
LinkedList linkList;

char menu();
void openSong();
void addSong();
void deletesong();
void playSong();
void printSong();
void clearList();

int main(){
    bool endProg = false;
    char usrIn = ' ';
    while(!endProg){
        usrIn = menu();
        switch(usrIn){
            case 'a':
                openSong();
                break;
            case 'b':
                addSong();
                break;
            case 'c':
                deletesong();
                break;
            case 'd':
                playSong();
                break;
            case 'e':
                printSong();
                break;
            case 'f':
                endProg = true;
                break;
            default:
                cout << usrIn << " is not a valid option, please select again." << endl;
        }
    }
}

char menu(){
    char usrIn = ' ';
    cout << "Please make a selection." << endl
         << "a) Open a song file." << endl
         << "b) Add a song." << endl
         << "c) Delete a song." << endl
         << "d) Play a song." << endl
         << "e) Print all songs." << endl
         << "f) Quit." << endl;
    cin >> usrIn;
    cin.ignore();
    usrIn = tolower(usrIn);
    return usrIn;
}

void openSong(){
    if(strcmp(Song::songListFile_, "") != 0){       //clear list if songs are already loaded
        clearList();
    }
    ifstream inFile;
    int songCount = 0;
    char songPath[PATH_SZ];
    cout << "Please enter the file path: ";
    cin >> Song::songListFile_;     //set listfile
    inFile.open(Song::songListFile_);
    while(inFile.getline(songPath, PATH_SZ)){       //read file
        Song *newSong = new Song();
        if(newSong == 0){
            cout << "Memory allocation failed." << endl;
            return;
        }
        if(strcmp(songPath, "") != 0){      //prevents reading of blank lines
            newSong->SetSongPath(songPath);
            linkList.AddLinkToBack(newSong);
            songCount++;
        }
    }
    inFile.close();
    inFile.clear(ios_base::goodbit);
    cout << "successfully loaded " << songCount << " songs." << endl;
}

void addSong(){
    if(strcmp(Song::songListFile_, "") == 0){      //abort if no songfile is spcified
        cout << "No song file has been opened." << endl;
        return;
    }
    Song *newSong = 0;
    char songPath[PATH_SZ];
    cout << "Please enter the file path: ";
    cin.getline(songPath, PATH_SZ);
    newSong = new Song(songPath);
    if(newSong == 0){
        cout << "Memory allocation failed." << endl;
        return;
    }
    linkList.AddLinkToBack(newSong);        //add node to linked list
    newSong->AppendToListFile();        //append the song to songlist file
}

void deletesong(){
    if(strcmp(Song::songListFile_, "") == 0){      //abort if no list file is loaded
        cout << "No song file has been opened." << endl;
        return;
    }
    char songName[PATH_SZ];
    bool found = false;
    cout << "Enter song name including extension to delete: ";
    cin.getline(songName, ENTRY_SZ);
    cout << endl;
    Song *song = 0;
    Node *curSong = linkList.GetFirstNode();
    while(true){        //iterate through linked list
        song = (Song*)(curSong->data_);     //cast void pointer as song
        if(strcmp(songName, song->GetSongName()) == 0){     //compare with name of song to be deleted
            delete ((Song*)linkList.RemoveThisLink(curSong));
            cout << "Song deleted." << endl;
            found = true;
            break;
        }
        if(curSong->next_ == 0){        //break if end of list is reached
            break;
        }
        else{
            curSong = curSong->next_;
        }
    }
    if(!found){
        cout << "Song not in playlist." << endl;
    }
    /*
    The following else statement writes the contents of the file except the song that
    we wish to delete to a temporary txt doc then iterates through that txt file
    copying back everything , then deletes the temp file when done,
    there is probably a better way.
    */
    else{       //Remove entry from file
        ifstream inFile;
        ofstream outFile;
        char lineBuf [PATH_SZ];
        inFile.open(Song::songListFile_);
        outFile.open("temp.txt");
        while(inFile.getline(lineBuf, PATH_SZ)){
            char *ptr = strrchr(lineBuf, '\\');     //check name of each file
            if(ptr != 0){
                if(strcmp(songName, ptr+1) != 0){       //don't write if it is out deleted song
                    outFile << lineBuf << endl;
                }
            }
            else{       //if no '\' is found look for a '/'
                ptr = strrchr(lineBuf, '/');
                if(ptr != 0){       //if ptr == 0 lineBuf was blankLine or erroneous data
                    if(strcmp(songName, ptr+1) != 0){
                        outFile << lineBuf << endl;
                    }
                }
            }
        }
        inFile.close();
        inFile.clear(ios_base::goodbit);
        outFile.close();
        outFile.clear(ios_base::goodbit);
        Song::ClearListFile();
        inFile.open("temp.txt");
        outFile.open(Song::songListFile_);
        while(inFile.getline(lineBuf, PATH_SZ)){        //writes everything back to song list file
            outFile << lineBuf << endl;
        }
        inFile.close();
        inFile.clear(ios_base::goodbit);
        outFile.close();
        outFile.clear(ios_base::goodbit);
        remove("temp.txt");
    }
}

void playSong(){
    if(strcmp(Song::songListFile_, "") == 0){       //abort if no list file is open.
        cout << "No song file has been opened." << endl;
        return;
    }
    char songName [ENTRY_SZ];
    cout << "Enter the song title, including extension: ";
    cin.getline(songName, ENTRY_SZ);
    Song *song = 0;
    Node *curSong = linkList.GetFirstNode();        //iterate through linked list
    while(true){
        song = (Song*)(curSong->data_);
        if(strcmp(songName, song->GetSongName()) == 0){     //if song is found, play song
            song->PlaySong();
            return;
        }
        if(curSong->next_ == 0){        //abort if end of list is reached.
            break;
        }
        else{
            curSong = curSong->next_;
        }
    }
    cout << endl << "That song is not in the playlist." << endl;        //only ran if no match found
}

void printSong(){
    if(linkList.GetListLength() == 0){      //abort if no song is loaded.
        cout << "No songs loaded." << endl;
        return;
    }
    Song *song = 0;
    Node *curSong = linkList.GetFirstNode();
    while(true){        //iterate through linked list
        song = (Song*)(curSong->data_);
        cout << song->GetSongName() << endl;
        if(curSong->next_ == 0){        //abort if end of list is reached.
            break;
        }
        curSong = curSong->next_;
    }
}

void clearList(){
    Song *song = 0;
    for(int i = 0; i < linkList.GetListLength(); i++){      //this is a better way to iterate through the list but not worth replacing the previous while loops.
        song = (Song*)linkList.RemoveLinkFromFront();       //cast void pointer as song and delete
        delete song;
    }
}
