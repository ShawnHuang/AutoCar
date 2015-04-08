#include "Membership_func.h" 
#include "Left_offset.h"
float Left_offset::getValue(){
  if (this->x<=-20)
  {
    return 1;
  }
  if (this->x<-17&&this->x>-20)
  {
    return this->x/-20;
  }
  return 0;
}
