class Membership_func 
{
public:
   // pure virtual function providing interface framework.
   float x;
   virtual float getValue() = 0;
   void setValue(float x){
    this->x = x;
   }
   /* no use
   float operator^(Membership_func& mf) {
     float temp ;
     temp = this->getValue() * mf.getValue() ; 
     return temp ;
   }
   */
};
