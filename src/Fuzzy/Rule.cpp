#include "MF/Membership_func.h"
#include "Rule.h"

Rule::Rule(Membership_func* pre_offset, Membership_func* pre_dist, Membership_func* post_steer)
{
   this->pre_offset = pre_offset;
   this->pre_dist = pre_dist;
   this->post_steer = post_steer;
}
