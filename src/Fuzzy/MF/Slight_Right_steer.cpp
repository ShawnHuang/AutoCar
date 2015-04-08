#include "Membership_func.h" 
#include "Slight_Right_steer.h"
float Slight_Right_steer::getValue(){
  if (this->x>0&&this->x<20)
  {
    return 1;
  }
  //if (this->x>30&&this->x<40)
  //{
  //  return 1;
  //}
  return 0;
}
