#ifndef PSO_H
#define PSO_H

#include <vector>
#include <iostream>

struct psoTrainData{
  float front, left, right;
  float y;
};

struct Agent{
  float theta;
  std::vector<float> weight;
  std::vector< std::vector< float > > mean;
  std::vector<float> deviation;

  //bool operator=(const coord &o) {
  //  return x == o.x && y == o.y;
  //}

  bool operator<(const Agent &p) const{
    if (theta<p.theta)
    {
      return true;
    }
    else if(theta==p.theta)
    {
      int w1size = weight.size();
      int i,j;
      for (i = 0; i < w1size; ++i)
      {
          if(weight[i]<p.weight[i])
          {
            return true;
          }
          else if(weight[i]==p.weight[i]){
            continue;
          }
          else return false;
      }

      int m1size = mean.size();
      for (i = 0; i < m1size; ++i)
      {
        int temp = (mean[i]).size();
        std::vector<float> vtemp = mean[i];
        std::vector<float> vtemp2 = p.mean[i];
        for (j = 0; j < temp; ++j)
        {
          if(vtemp[j]<vtemp2[j])
          {
            return true;
          }
          else if(vtemp[j]==vtemp2[j]){
            continue;
          }
          else return false;
        }
      }

      int d1size = deviation.size();
      for (i = 0; i < d1size; ++i)
      {
          if(deviation[i]<p.deviation[i])
          {
            return true;
          }
          else if(deviation[i]==p.deviation[i]){
            continue;
          }
          else return false;
      }
    }
    return false;
  }

  friend Agent operator* (float scalar, const Agent& p){
    float rtheta=scalar*p.theta;

    int wsize = p.weight.size();
    int i,j;
    std::vector< float > rweight(wsize);
    for (i = 0; i < wsize; ++i)
    {
        rweight[i] = scalar*p.weight[i];
    }

    int msize = p.mean.size();
    std::vector< std::vector<float> > rmean(msize);
    for (i = 0; i < msize; ++i)
    {
      int temp = (p.mean[i]).size();
      std::vector<float> rvtemp(temp);

      std::vector<float> vtemp = p.mean[i];
      std::vector<float> vtemp2 = p.mean[i];
      for (j = 0; j < temp; ++j)
      {
        rvtemp[j] = scalar*vtemp2[j];
      }
      rmean[i]=rvtemp;
    }

    int dsize = p.deviation.size();
    std::vector< float > rdeviation(dsize);
    for (i = 0; i < dsize; ++i)
    {
      rdeviation[i] = scalar*p.deviation[i];
    }

    return {rtheta,rweight,rmean,rdeviation};
  }

  Agent operator+(const Agent &p) const{
    float rtheta=theta+p.theta;

    int wsize = weight.size();
    int i,j;
    std::vector< float > rweight(wsize);
    for (i = 0; i < wsize; ++i)
    {
        rweight[i] = weight[i]+p.weight[i];
    }

    int msize = mean.size();
    std::vector< std::vector<float> > rmean(msize);
    for (i = 0; i < msize; ++i)
    {
      int temp = (mean[i]).size();
      std::vector<float> rvtemp(temp);

      std::vector<float> vtemp = mean[i];
      std::vector<float> vtemp2 = p.mean[i];
      for (j = 0; j < temp; ++j)
      {
        rvtemp[j] = vtemp[j]+vtemp2[j];
      }
      rmean[i]=rvtemp;
    }

    int dsize = deviation.size();
    std::vector< float > rdeviation(dsize);
    for (i = 0; i < dsize; ++i)
    {
      rdeviation[i] = deviation[i]+p.deviation[i];
    }

    return {rtheta,rweight,rmean,rdeviation};
  }

  Agent operator-(const Agent &p) const{
    float rtheta=theta-p.theta;

    int wsize = weight.size();
    int i,j;
    std::vector< float > rweight(wsize);
    for (i = 0; i < wsize; ++i)
    {
        rweight[i] = weight[i]-p.weight[i];
    }

    int msize = mean.size();
    std::vector< std::vector<float> > rmean(msize);
    for (i = 0; i < msize; ++i)
    {
      int temp = (mean[i]).size();
      std::vector<float> rvtemp(temp);

      std::vector<float> vtemp = mean[i];
      std::vector<float> vtemp2 = p.mean[i];
      for (j = 0; j < temp; ++j)
      {
        rvtemp[j] = vtemp[j]-vtemp2[j];
      }
      rmean[i]=rvtemp;
    }

    int dsize = deviation.size();
    std::vector< float > rdeviation(dsize);
    for (i = 0; i < dsize; ++i)
    {
      rdeviation[i] = deviation[i]-p.deviation[i];
    }

    return {rtheta,rweight,rmean,rdeviation};
  }
  friend std::ostream& operator<< (std::ostream& os, const Agent& p){
    os<<"{"<<std::endl;
    os<<"\ttheta: "<<p.theta<<","<<std::endl;

    os<<"\tweight: [";
    int wsize = p.weight.size();
    int i,j;
    for (i = 0; i < wsize; ++i)
    {
        os<<" "<<p.weight[i];
        if(i!=(wsize-1)) os<<",";
    }
    os<<"],"<<std::endl;

    os<<"\tmean: [";
    int msize = p.mean.size();
    for (i = 0; i < msize; ++i)
    {
      os<<"[";
      int temp = (p.mean[i]).size();
      std::vector<float> vtemp = p.mean[i];
      for (j = 0; j < temp; ++j)
      {
        os<<" "<<vtemp[j];
        if(j!=(temp-1)) os<<",";
      }
      os<<"]";
      if(j!=(temp-1)) os<<",";
      if(i%3==2) os<<std::endl<<"\t";
    }
    os<<"],"<<std::endl;

    os<<"\tdeviation: [";
    int dsize = p.deviation.size();
    for (i = 0; i < dsize; ++i)
    {
      os<<" "<<p.deviation[i];
      if(i!=(dsize-1)) os<<",";
    }
    os<<"]"<<std::endl;
    os<<"}";

    return os;
  }
};


class PSO
{
  public:
    PSO ();
    float getSteer(float left, float center, float right);

  private:
    int iterator;

    std::vector<Agent> agents_x;
    std::vector<Agent> agents_v;
    std::vector<Agent> agents_good;
    Agent agent_good,agent_good_v;

    std::vector<psoTrainData> train;

    void generateAgentsX(std::vector<Agent> *agents, int num,float ratio);
    void generateAgentsV(std::vector<Agent> *agents, int num,float ratio);
    float fitness(const Agent &gene);
    float simulate(float xfront, float xleft, float xright, const Agent &g);
    std::vector<psoTrainData> importTrain();

    void pso_update(int i,const Agent &agent_good, const Agent &agent_good_i, Agent *agent_v, Agent *agent_x);
    void boundAgent( Agent *agent_v, Agent *agent_x);
};
#endif
