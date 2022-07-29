#ifndef GIFT_H
#define GIFT_H

#include <random>
#include "SDL.h"

class Gift
{
public:
    Gift();
    Gift(int x, int y);
    ~Gift();

    //Getter functions
    SDL_Point GetPosition() const;
    bool Exists() const;
    bool JustEaten() const;

    int GetTimeSinceCreation() const;
    int GetTimeLimitMS() const;
    int GetTimeCounter() const;
    int JustEatenTimePoint() const;

    //Setter Functions
    void SetPosition(int x, int y);
    void JustEaten(bool value);
    void JustEatenTimePoint(Uint32 timepoint);
    void SetTimeCounter(Uint32 timepoint);

private:

    SDL_Point giftPosition;

    std::uniform_int_distribution<int> random_foodcount; //if reaches randomCount: gift appearance  
    int randomCount; //Values between 5 and 7, for gift appearance, see constructor

    int timeCounter; // Time Counter to make gift disappear
    int timeLimitMS{5000}; //Maximum time limit for gift in ms
    bool justEaten {false}; //Flag whether gift was just eaten
    int justEatenTimePoint {INT32_MAX}; //Big value to avoid color change in the beginning, as if the gift had been eaten recently

};

#endif