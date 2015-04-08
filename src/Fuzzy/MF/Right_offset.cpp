#include "Membership_func.h" 
#include "Right_offset.h"
float Right_offset::getValue(){
  if (this->x>=20)
  {
    return 1;
  }
  if (this->x>17&&this->x<20)
  {
    return this->x/20;
  }
  return 0;
}
