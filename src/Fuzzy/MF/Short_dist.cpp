#include "Membership_func.h" 
#include "Short_dist.h"
float Short_dist::getValue(){
  if (this->x<=8)
  {
    return 1;
  }
  return 0;
}
