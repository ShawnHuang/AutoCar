#include <iostream>
#include <algorithm>

#include "MF/Membership_func.h"

#include "MF/Left_offset.h"
#include "MF/Slight_Left_offset.h"
#include "MF/None_offset.h"
#include "MF/Slight_Right_offset.h"
#include "MF/Right_offset.h"

#include "MF/Short_dist.h"
#include "MF/Slight_Short_dist.h"
#include "MF/Slight_Long_dist.h"
#include "MF/Long_dist.h"

#include "MF/Left_steer.h"
#include "MF/Slight_Left_steer.h"
#include "MF/Slight_Right_steer.h"
#include "MF/Right_steer.h"

#include "Rule.h"
#include "Fuzzy.h"

Fuzzy::Fuzzy()
{
  //None_offset* no = new None_offset();
  //Short_dist* sd = new Short_dist();
  //Right_steer* rs = new Right_steer();
  //r1 = new Rule(no,sd,rs);

  Slight_Left_offset* slo = new Slight_Left_offset();
  //Long_dist* ld = new Long_dist();
  //Slight_Left_steer* sls = new Slight_Left_steer();
  //r1 = new Rule( slo, ld, sls);
  //
  Slight_Right_offset* sro = new Slight_Right_offset();
  ////Long_dist* ld = new Long_dist();
  //Slight_Right_steer* srs = new Slight_Right_steer();
  //r2 = new Rule( sro, ld, srs);

  //Slight_Left_offset* slo = new Slight_Left_offset();
  Short_dist* sd = new Short_dist();
  Left_steer* ls = new Left_steer();
  r3 = new Rule( slo, sd, ls);
  
  //Slight_Right_offset* sro = new Slight_Right_offset();
  //Short_dist* ld = new Short_dist();
  Right_steer* rs = new Right_steer();
  r4 = new Rule( sro, sd, rs);
  
  //Left_offset* lo = new Left_offset();
  Long_dist* ld = new Long_dist();
  Slight_Left_steer* sls = new Slight_Left_steer();
  r5 = new Rule( slo, ld, sls);

  //Right_offset* ro = new Right_offset();
  //Long_dist* ld = new Long_dist();
  Slight_Right_steer* srs = new Slight_Right_steer();
  r6 = new Rule( sro, ld, srs);
}

Fuzzy::Fuzzy(float left, float center, float right){
 this->offset = right - left; 
 this->dist = center;
}
void Fuzzy::init(float left, float center, float right){
 this->offset = right - left; 
 this->dist = center;


 //this->r1->setOffset(this->offset);
 //this->r1->setDist(this->dist);

 //this->r2->setOffset(this->offset);
 //this->r2->setDist(this->dist);
 
 this->r3->setOffset(this->offset);
 this->r3->setDist(this->dist);
 
 this->r4->setOffset(this->offset);
 this->r4->setDist(this->dist);

 this->r5->setOffset(this->offset);
 this->r5->setDist(this->dist);
 
 this->r6->setOffset(this->offset);
 this->r6->setDist(this->dist);
 
 //for range
 //max r1~n getresult*x
 //div sum of x
 float sum=0,result=0,i;
 for (i = -40; i <= 40; i+=0.1)
 {
   //float rule1 = this->r1->getResult(i);
   //float rule2 = this->r2->getResult(i);
   float rule3 = this->r3->getResult(i);
   float rule4 = this->r4->getResult(i);
   float rule5 = this->r5->getResult(i);
   float rule6 = this->r6->getResult(i);

   //std::cout<<rule1<<", "<<rule2<<", "<<i<<std::endl;
   //float rule3 = this->r3->getResult(i);
   //if(rule1!=0||rule2!=0||rule3!=0||rule4!=0||rule5!=0||rule6!=0){
   if(rule3!=0||rule4!=0||rule5!=0||rule6!=0){
     //sum+=std::max(rule1,std::max(rule2,std::max(rule3,std::max(rule4,std::max(rule5,rule6)))));
     //result+=(i*std::max(rule1,std::max(rule2,std::max(rule3,std::max(rule4,std::max(rule5,rule6))))));
     //sum+=std::max(rule3,std::max(rule4,0.0f));//std::max(rule5,rule6)));
     //result+=(i*std::max(rule3,std::max(rule4,0.0f)));//std::max(rule5,rule6))));
     sum+=std::max(rule3,std::max(rule4,std::max(rule5,rule6)));
     result+=(i*std::max(rule3,std::max(rule4,std::max(rule5,rule6))));
   }
 }
 if (result==0&&sum==0)
 {
   this->steer=0;
 }
 else this->steer=(result/sum);
 if (this->dist>10)
 {
   this->steer=0;
 }

 std::cout<<this->steer<<": offset "<<this->offset<<", dist: "<<this->dist<<std::endl;
}

float Fuzzy::getSteer(){
  return this->steer;
}

float Fuzzy::getSpeed(){
  return 0.0;
}
