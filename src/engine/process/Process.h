#pragma once

/*============================================================================||
| Processes that occurs over many frames
|-----------------------------------------------------------------------------||
| A process knows how to iterate itself (nextIter())
\=============================================================================*/

class Process
{
public:
    // NEXT ITERATION
    virtual void nextIter() = 0;
};