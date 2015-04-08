#include "Membership_func.h" 
#include "Left_steer.h"
float Left_steer::getValue(){
  if (this->x<-39&&this->x>-40)
  {
    return 1;
  }
  return 0;
}
