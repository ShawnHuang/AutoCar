#include "Membership_func.h" 
#include "Long_dist.h"
float Long_dist::getValue(){
  if (this->x>8)
  {
    return 1;
  }
  return 0;
}
