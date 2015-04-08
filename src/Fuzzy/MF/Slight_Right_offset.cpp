#include "Membership_func.h" 
#include "Slight_Right_offset.h"
float Slight_Right_offset::getValue(){
  if (this->x>12&&this->x<20)
  {
    return this->x/20;
  }
  if (this->x>0&&this->x<13)
  {
    return this->x/5;
  }

  return 0;
}
