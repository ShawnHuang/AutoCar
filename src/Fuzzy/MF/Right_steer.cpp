#include "Membership_func.h" 
#include "Right_steer.h"
float Right_steer::getValue(){
  if (this->x>39&&this->x<40)
  {
    return 1;
  }
  return 0;
}
