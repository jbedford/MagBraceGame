#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "charon.h"
#include "magbrace.h"

class Controller{
    public:
        void HandleInput(bool &running, Charon &charon, MagBrace &magbrace) const;

    private:
        void ChangeDirection(Charon &charon, Charon::Direction input) const;

        void RightBraceLaunch(MagBrace &magbrace, int dir) const;

        void RightBraceRelease(MagBrace &magbrace) const;

};

#endif