#include "PSO.h"
#include "../constants.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

PSO::PSO()
  :iterator(0),
   train(importTrain())
{
  generateAgentsX( &agents_x, PSO_NUM, 1);
  generateAgentsV( &agents_v, PSO_NUM, 0.04);
  generateAgentsX( &agents_good, PSO_NUM, 0);

  while(++iterator) {
    
    int i;
    for (i = 0; i < PSO_NUM; ++i)
    {
      if (iterator==1&&i==0)
      {
        agents_good[i] = agents_x[i];
        agent_good = agents_x[i];
        agent_good_v = agents_v[i];
      }
      if (fitness(agents_x[i]) < fitness(agents_good[i]))
      {
        agents_good[i] = agents_x[i];
      } 
      if (fitness(agents_x[i]) < fitness(agent_good))
      {
        agent_good = agents_x[i];
        agent_good_v = agents_v[i];
      }
      if(i==(PSO_NUM-1))
      {
        std::cout<<iterator<<": "<<fitness(agent_good)<<", "<<std::endl;
      }
      //update
      pso_update(i, agent_good, agents_good[i], &agents_v[i], &agents_x[i]);
      boundAgent(&agents_v[i],&agents_x[i]);
    }
    float result = fitness(agent_good);
    if (result<130||iterator==PSO_TMAX)
    {
      break;
    }
    
  }
}

float PSO::fitness(const Agent &gene){
  float sum=0;
  std::vector<psoTrainData>::iterator it;
  for (it = this->train.begin();it != this->train.end();++it)
  {
     float value;
     value=(*it).y-this->simulate((*it).front, (*it).left, (*it).right, gene);
     sum+=(value*value);
  } 
  return sum/2;
}

std::vector<psoTrainData> PSO::importTrain(){
  std::vector<psoTrainData> train;
  int i;
  for (i = 0; i < 2; ++i)
  {
    std::ostringstream s;
    s << "../src/PSO/train/train_" << i << "_D2.txt";
    std::ifstream infile(s.str().c_str());
    std::string line;
    while (std::getline(infile, line))
    {
      std::istringstream iss(line);
      float temp,temp2;
      float front, left, right, y;
      if (!(iss >> temp >> temp2 >> front >> right >> left >> y)) { break; } // error
      //std::cout<<front<<", "<<left<<", "<<right<<", "<<y<<std::endl;
      psoTrainData td = {front,left,right,y};
      train.push_back(td);
    }
  }

  return train;
}

float PSO::simulate(float xfront, float xleft, float xright, const Agent &g)
{
  float sum=0;
  std::vector<float>::const_iterator it1;
  std::vector<std::vector<float> >::const_iterator it2;
  std::vector<float>::const_iterator it3;
  for (it1 = g.weight.begin(),it2 = g.mean.begin(),it3 = g.deviation.begin();
    it1 != g.weight.end();++it1,++it2,++it3)
  {
    //std::cout<<(*it1)<<", "<<(*it2)[0]<<", "<<(*it2)[1]<<", "<<(*it2)[2]<<", "<<(*it3)<<std::endl;
    float w=(*it1);
    float front=(*it2)[0];
    float left=(*it2)[1];
    float right=(*it2)[2];
    float deviation=(*it3);
    float value = w*exp(-1*(front*xfront+left*xleft+right*xright)/(2*deviation*deviation));
    if(value!=value) value = w*exp(0);
    sum+=value;
  }
  sum+=g.theta;
  return sum;
}

float PSO::getSteer(float left, float center, float right)
{
  return this->simulate(center, left, right, agent_good);
}


void PSO::generateAgentsX(std::vector<Agent> *agents, int num,float ratio)
{
  srand(time(NULL));
  int i;
  for (i = 0; i < num; ++i)
  {
    int j;

    float theta=(rand()%81-40)*ratio;
    std::vector< std::vector<float> > mean;
    std::vector< float > weight;
    std::vector< float > deviation;
    for (j = 0; j < GA_J; ++j)
    {
      std::vector<float> r_mean;
      r_mean.push_back(rand()%31*ratio);
      r_mean.push_back(rand()%31*ratio);
      r_mean.push_back(rand()%31*ratio);

      mean.push_back(r_mean);
      weight.push_back((rand()%81-40)*ratio);
      deviation.push_back(rand()%11*ratio);
      
    }
    Agent gene={theta,weight,mean,deviation};
    agents->push_back(gene);
  }
}
void PSO::generateAgentsV(std::vector<Agent> *agents, int num,float ratio)
{
  srand(time(NULL));
  int i;
  for (i = 0; i < num; ++i)
  {
    int j;

    float theta=(rand()%81-40)*ratio;
    std::vector< std::vector<float> > mean;
    std::vector< float > weight;
    std::vector< float > deviation;
    for (j = 0; j < GA_J; ++j)
    {
      std::vector<float> r_mean;
      r_mean.push_back((rand()%31-15)*ratio);
      r_mean.push_back((rand()%31-15)*ratio);
      r_mean.push_back((rand()%31-15)*ratio);

      mean.push_back(r_mean);
      weight.push_back((rand()%81-40)*ratio);
      deviation.push_back((rand()%11-5)*ratio);
      
    }
    Agent gene={theta,weight,mean,deviation};
    agents->push_back(gene);
  }
}
void PSO::pso_update(int i, const Agent &agent_good, const Agent &agent_good_i, Agent *agent_v, Agent *agent_x)
{
  float w = PSO_W_START - (PSO_W_START - PSO_W_END)/PSO_TMAX*iterator;
  float c1 = PSO_C1_START - (PSO_C1_START - PSO_C1_END)/PSO_TMAX*iterator;
  float c2 = PSO_C2_START - (PSO_C2_START - PSO_C2_END)/PSO_TMAX*iterator;
  float r1 = (float)(rand()%100)/100;
  float r2 = (float)(rand()%100)/100;

  *agent_v = w*(*agent_v) + c1*r1*(agent_good_i - (*agent_x)) + c2*r2*(agent_good - (*agent_x)); 
  *agent_x = (*agent_x)+(*agent_v); 
}

void PSO::boundAgent( Agent *agent_v, Agent *agent_x)
{
    if(agent_v->theta < -1.6) agent_v->theta = -1.6;
    if(agent_v->theta > 1.6) agent_v->theta = 1.6;

    if(agent_x->theta > 40 && agent_x->theta <-40) agent_v->theta *= -1;

    if(agent_x->theta < -40) agent_x->theta = -40;
    if(agent_x->theta > 40) agent_x->theta = 40;

    int wsize = agent_v->weight.size();
    int i,j;
    for (i = 0; i < wsize; ++i)
    {
        if(agent_v->weight[i] < -1.6) agent_v->weight[i] = -1.6;
        if(agent_v->weight[i] > 1.6) agent_v->weight[i] = 1.6;

        if(agent_x->weight[i] > 40 && agent_x->weight[i] <-40) agent_v->weight[i] *= -1;

        if(agent_x->weight[i] < -40) agent_x->weight[i] = -40;
        if(agent_x->weight[i] > 40) agent_x->weight[i] = 40;
    }

    int msize = agent_v->mean.size();
    for (i = 0; i < msize; ++i)
    {
      int temp = (agent_v->mean[i]).size();
      std::vector<float> vtemp = agent_v->mean[i];
      std::vector<float> xtemp = agent_x->mean[i];
      for (j = 0; j < temp; ++j)
      {
        if(vtemp[j] < 0) vtemp[j] = 0;
        if(vtemp[j] > 1.2) vtemp[j] = 1.2;

        if(xtemp[j] > 30 && xtemp[j] <0) vtemp[j] *= -1;

        if(xtemp[j] < 0) xtemp[j] = 0;
        if(xtemp[j] > 30) xtemp[j] = 30;
      }
      agent_v->mean[i] = vtemp;
      agent_x->mean[i] = xtemp;
    }

    int dsize = agent_v->deviation.size();
    for (i = 0; i < dsize; ++i)
    {
      if(agent_v->deviation[i] < 0) agent_v->deviation[i] = 0;
      if(agent_v->deviation[i] > 0.4) agent_v->deviation[i] = 0.4;

      if(agent_x->deviation[i] > 10 && agent_x->deviation[i] <0) agent_v->deviation[i] *= -1;

      if(agent_x->deviation[i] < 0) agent_x->deviation[i] = 0;
      if(agent_x->deviation[i] > 10) agent_x->deviation[i] = 10;
    }
}
