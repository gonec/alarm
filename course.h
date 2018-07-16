#ifndef COURSE_H
#define COURSE_H


struct Course
{
public:
   Course();
   unsigned mSpeed : 10;
   unsigned mCourse : 9;

   unsigned mTemperature : 7;
   unsigned mTemperatureSign : 1;

   unsigned mRezerv : 5;
};

#endif // COURSE_H
