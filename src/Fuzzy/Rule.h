#include <vector>
#include <iostream>

class Membership_func;
class Rule
{
public:
  float alpha_cut;
  float offset,dist;
  Membership_func *pre_offset,*pre_dist;
  Membership_func *post_steer;
  Rule (Membership_func* pre_offset, Membership_func* pre_dist, Membership_func* post_steer);
  void setOffset(float offset){
    this->offset = offset;
  }
  void setDist(float dist){
    this->dist = dist;
  }
  float getResult(float input){
    this->pre_offset->setValue(this->offset);
    this->pre_dist->setValue(this->dist);
    this->alpha_cut = this->pre_offset->getValue()*this->pre_dist->getValue();
    this->post_steer->setValue(input);
    if (this->post_steer->getValue()<=this->alpha_cut)
    {
      return this->post_steer->getValue();
    }
    else return this->alpha_cut;
  }
};
