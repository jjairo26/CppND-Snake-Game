#include "gift.h"

Gift::Gift() : timeCounter(0), timeLimitMS(5000), justEaten(false), justEatenTimePoint(INT32_MAX){
    // Default Position(x = -1, y = -1) encode a non-available gift
    SetPosition(-1,-1);
};

Gift::Gift(int x, int y) {
    SetPosition(x, y);
}

Gift::~Gift(){}

/**
 *  \brief Returns the SDL_Point with the gift position. Includes an x and y coordinate.
 */
SDL_Point Gift::GetPosition() const {
    return giftPosition;
}

/**
 *  \brief Returns whether the gift is in a valid visible position
 */
bool Gift::Exists() const {
    return (giftPosition.x != -1 && giftPosition.y != -1);
}

/**
 *  \brief Returns whether the gift has just been eaten
 */
bool Gift::JustEaten() const { return justEaten; }

/**
 *  \brief Time in ms since gift is available
 */
int Gift::GetTimeSinceCreation() const {
   return SDL_GetTicks() - GetTimeCounter(); 
   }

/**
 *  \brief Time limit in ms after which the gift disappears
 */
int Gift::GetTimeLimitMS() const { return timeLimitMS; }

/**
 *  \brief Time limit in ms after which the gift disappears
 */
int Gift::GetTimeCounter() const { return timeCounter; }

/**
 *  \brief Time point in which the gift has been eaten
 */
int Gift::JustEatenTimePoint() const { return justEatenTimePoint;}

//Setter functions

/**
 *  \brief Sets the gift coordinates to x and y values
 */
void Gift::SetPosition(int x, int y) {
    giftPosition.x = x;
    giftPosition.y = y;
}

/**
 *  \brief Sets the gift eaten flag
 */
void Gift::JustEaten(bool value) { justEaten = value; }

/**
 *  \brief Sets the time point where the gift has been eaten, is usually called with SDL_GetTicks() as an argument.
 */
void Gift::JustEatenTimePoint(Uint32 timepoint) {justEatenTimePoint = timepoint;}

/**
 *  \brief Sets the gift eaten flag
 */
void Gift::SetTimeCounter(Uint32 timepoint) { timeCounter = timepoint; }
