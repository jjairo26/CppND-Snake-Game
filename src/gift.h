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

    int timeCounter; // Time Counter to make gift disappear
    int timeLimitMS; //Maximum time limit for gift in ms
    bool justEaten; //Flag whether gift was just eaten
    int justEatenTimePoint; //Big value (See initializer list) to avoid color change in the beginning, as if the gift had been eaten recently

};

#endif