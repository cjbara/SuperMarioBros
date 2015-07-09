//this is the Question class, used to render Questions

#include "NonMoving.h"

#ifndef QUESTION_H
#define QUESTION_H

class Question: public NonMoving{
  public:
        Question(int, int);//constructor
        void collision();//collision animation

};

#endif
