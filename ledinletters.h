#ifndef LEDINLETTERS_H
#define LEDINLETTERS_H

#include "objectclass.h"

class ledinletters : public ComplexObject
{
public:
    ledinletters();
};

#endif // LEDINLETTERS_H



// ledinletters* ledinLetters = new ledinletters();
// scene->addItem(ledinLetters);
// connect(timer, &QTimer::timeout, [ledinLetters, view]() { ledinLetters->move(view); });
// ledinLetters->setPos(500, 500);
