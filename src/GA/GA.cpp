#include "GA.h"
#include "../constants.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

GA::GA()
:iterator(0){
  this->importTrain();
  this->generatePopulations(GA_NUM);
  while(++iterator) {

    //std::cout<<iterator<<std::endl;
    this->reproduction();
    std::cout<<this->fitness(&this->best_fit)<<std::endl;

    this->generateChildPopulations();

    if (this->fitness(&this->best_fit)<120)
    {
      break;
    }
  }
}

void GA::generatePopulations(int num){
  srand(time(NULL));
  int i;
  for (i = 0; i < num; ++i)
  {
    int j;

    float theta=rand()%81-40;
    std::vector< std::vector<float> > mean;
    std::vector< float > weight;
    std::vector< float > deviation;
    for (j = 0; j < GA_J; ++j)
    {
      std::vector<float> r_mean;
      r_mean.push_back(rand()%31);
      r_mean.push_back(rand()%31);
      r_mean.push_back(rand()%31);

      mean.push_back(r_mean);
      weight.push_back(rand()%81-40);
      deviation.push_back(rand()%11);
      
    }
    Population gene={theta,weight,mean,deviation};
    this->populations.push_back(gene);
  }
}

void GA::reproduction(){
  this->pool.clear();
  std::vector<Population>::iterator it; 
  //計算總和
  std::map<Population,float> fitness_list; 
  int i;
  float sum=0;
  for(it = this->populations.begin(),i=0; it != this->populations.end(); ++it,++i) {
    float value = this->fitness(&(*it));
    sum += value;
    fitness_list.insert(std::make_pair((*it),value));
  }

  //找出最好的基因
  Population temp2;
  temp2 = min_element(fitness_list.begin(), fitness_list.end(), MinFit())->first;
  if(this->fitness(&temp2)<this->fitness(&(this->best_fit))){
    this->best_fit = temp2;
  }


  //紀錄compare with avg fitness 的結果
  float avg_fit = sum/i;
  std::map<Population,float>::iterator map_it;
  for (map_it=fitness_list.begin(); map_it!=fitness_list.end(); ++map_it)
  {
    map_it->second = map_it->second/avg_fit;
    //std::cout<<map_it->first.theta<<", "<<map_it->second<<std::endl;
  }

  //保留好的去交配
  Population temp;
  std::vector<std::pair<Population,float> > fitness_list_vec(fitness_list.begin(), fitness_list.end());  
  sort(fitness_list_vec.begin(), fitness_list_vec.end(), MinFit());  
  //std::random_shuffle ( fitness_list_vec.begin(), fitness_list_vec.end() );
  this->populations.clear();
  for (i = 0; i < GA_NUM; ++i)
  {
    //method 1
    if(i<50)
    {
      this->pool.push_back(fitness_list_vec[i].first);
    }
    if(i<50)
    {
      this->populations.push_back(fitness_list_vec[i].first);
    }

    //std::cout<<i<<std::endl;
    //if (i%3==2)
    //{
    //  
    //  std::cout<<fitness_list_vec[i].second<<fitness_list_vec[i-1].second<<","<<fitness_list_vec[i-2].second<<std::endl;
    //  if(fitness_list_vec[i].second>fitness_list_vec[i-2].second)
    //  {
    //    if(fitness_list_vec[i].second>fitness_list_vec[i-1].second)
    //      this->populations.push_back(fitness_list_vec[i].first);
    //    else
    //      this->populations.push_back(fitness_list_vec[i-1].first);
    //  }
    //  else{
    //    if(fitness_list_vec[i-2].second>fitness_list_vec[i-1].second)
    //      this->populations.push_back(fitness_list_vec[i].first);
    //    else
    //      this->populations.push_back(fitness_list_vec[i-1].first);
    //  }
    //}
    //temp = min_element(fitness_list.begin(), fitness_list.end(), MinFit())->first;
    //float value = this->fitness(&temp);
    //std::cout<<value<<std::endl;
    ////std::cout<<this->fitness(&temp)<<std::endl;
    ////std::cout<<"test"<<std::endl;
    //map_it=fitness_list.find (temp);
    //fitness_list.erase(map_it);
    //map_it->second+=1000;
  }
}

void GA::generateChildPopulations()
{
  //亂數取出
  std::random_shuffle ( this->pool.begin(), this->pool.end() );
  //std::vector<Population>::iterator it; 
  //for(it = this->pool.begin(); it != this->pool.end(); ++it) {
  //  int value = it->theta;
  //  std::cout<<value<<std::endl;
  //}
  Population p1,p2;
  while (this->pool.size()>1)
  {
    p1 = this->pool.back();
    this->pool.pop_back();
    p2 = this->pool.back();
    this->pool.pop_back();

    this->crossover(&p1, &p2);
  }
}

void GA::mutation(Population *g){
    Population mg;
    float theta;
    std::vector<float> weight;
    std::vector<std::vector<float> > mean;
    std::vector<float> deviation;
    //std::cout<<g->theta<<std::endl;

    if (rand()%100+1<=GA_Pm*100) //GA_Pm 突變機率
    {
      theta = g->theta + GA_SIZE_M * (rand()%81-40);
    }
    else theta = g->theta;
    
    std::vector<float>::iterator it; 
    for(it = g->weight.begin(); it != g->weight.end(); ++it) {
      float fw = (*it) + GA_SIZE_M*(rand()%81-40);
      if (rand()%100+1<=GA_Pm*100) //GA_Pm 突變機率
      {
        weight.push_back(fw);
      }
      else weight.push_back((*it));
    }

    std::vector<std::vector<float> >::iterator v_it; 
    for(v_it = g->mean.begin(); v_it != g->mean.end(); ++v_it) {
      std::vector<float> temp;
      for(it = v_it->begin(); it != v_it->end(); ++it) {
        if (rand()%100+1<=GA_Pm*100) //GA_Pm 突變機率
        {
          float ftemp = (*it) + GA_SIZE_M*(rand()%30);
          temp.push_back(ftemp);
        }
        else temp.push_back(*it);
      }
      mean.push_back(temp);
    }

    for(it = g->deviation.begin(); it != g->deviation.end(); ++it) {
      float fd = (*it) + GA_SIZE_M*(rand()%11);
      if (rand()%100+1<=GA_Pm*100) //GA_Pm 突變機率
      {
        deviation.push_back(fd);
      }
      else deviation.push_back(*it);
    }
    //push to populations;
    mg = {theta,weight,mean,deviation};
    this->populations.push_back(mg);
}

void GA::crossover(Population *g1, Population *g2){
  if (rand()%10+1<=GA_Pc*10) //GA_Pc 交配機率
  { 
    Population child1,child2;
    float theta1,theta2;
    std::vector<float> weight1,weight2;
    std::vector<std::vector<float> > mean1,mean2;
    std::vector<float> deviation1,deviation2;

    //std::cout<<g1->theta<<", "<<g2->theta<<std::endl;    
    theta1 = g1->theta + GA_SIGMAL_C*(g1->theta - g2->theta);
    theta2 = g2->theta - GA_SIGMAL_C*(g1->theta - g2->theta);

    /*--------------- weight -----------------*/
    typedef std::vector<float>::iterator w1Iter;
    typedef std::vector<float>::iterator w2Iter;
    for (std::pair<w1Iter, w2Iter> i(g1->weight.begin(), g2->weight.begin());
     i.first != g1->weight.end() /* && i.second != g2->weight.end() */;
     ++i.first, ++i.second)
    {
      //std::cout<<(*i.first) * (*i.second)<<std::endl;
      
      float fw1 = (*i.first) + GA_SIGMAL_C*((*i.first) - (*i.second));
      float fw2 = (*i.second) - GA_SIGMAL_C*((*i.first) - (*i.second));
      weight1.push_back(fw1);
      weight2.push_back(fw2);
    }

    /*--------------- mean -----------------*/
    typedef std::vector<std::vector<float> >::iterator m1Iter;
    typedef std::vector<std::vector<float> >::iterator m2Iter;
    for (std::pair<m1Iter, m2Iter> i(g1->mean.begin(), g2->mean.begin());
     i.first != g1->mean.end() /* && i.second != g2->mean.end() */;
     ++i.first, ++i.second)
    {
      std::vector<float> vm1,vm2;
      //std::cout<<(*i.first) * (*i.second)<<std::endl;
      typedef std::vector<float>::iterator p1Iter;
      typedef std::vector<float>::iterator p2Iter;
      for (std::pair<p1Iter, p2Iter> j((*i.first).begin(), (*i.second).begin());
       j.first != (*i.first).end() /* && j.second != g2->weight.end() */;
       ++j.first, ++j.second)
      {
        //std::cout<<(*j.first) * (*j.second)<<std::endl;
        float fm1 = (*j.first) + GA_SIGMAL_C*((*j.first) - (*j.second));
        float fm2 = (*j.second) - GA_SIGMAL_C*((*j.first) - (*j.second));
        
        vm1.push_back(fm1);
        vm2.push_back(fm2);
      }
      mean1.push_back(vm1);
      mean2.push_back(vm2);
    }

    /*-------------- deviation ---------------*/
    typedef std::vector<float>::iterator d1Iter;
    typedef std::vector<float>::iterator d2Iter;
    for (std::pair<d1Iter, d2Iter> i(g1->deviation.begin(), g2->deviation.begin());
     i.first != g1->deviation.end() /* && i.second != g2->deviation.end() */;
     ++i.first, ++i.second)
    {
      //std::cout<<(*i.first) * (*i.second)<<std::endl;
      float fd1 = (*i.first) + GA_SIGMAL_C*((*i.first) - (*i.second));
      float fd2 = (*i.second) - GA_SIGMAL_C*((*i.first) - (*i.second));
      deviation1.push_back(fd1);
      deviation2.push_back(fd2);
    }
    child1={theta1,weight1,mean1,deviation1};
    this->mutation(&child1);
    child2={theta2,weight2,mean2,deviation2};
    this->mutation(&child2);
  }
}

float GA::fitness(Population *gene){
  float sum=0;
  std::vector<TrainData>::iterator it;
  for (it = this->train.begin();it != this->train.end();++it)
  {
     float value;
     value=(*it).y-this->simulate((*it).front, (*it).left, (*it).right, gene);
     sum+=(value*value);
  } 
  return sum/2;
}

void GA::importTrain(){
  std::ifstream infile("../src/GA/train/train_0_D2.txt");
  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream iss(line);
    float temp,temp2;
    float front, left, right, y;
    if (!(iss >> temp >> temp2 >> front >> right >> left >> y)) { break; } // error
    //std::cout<<front<<", "<<left<<", "<<right<<", "<<y<<std::endl;
    TrainData td = {front,left,right,y};
    this->train.push_back(td);
  }
}

float GA::simulate(float xfront, float xleft, float xright, Population *g)
{
  float sum=0;
  std::vector<float>::iterator it1;
  std::vector<std::vector<float> >::iterator it2;
  std::vector<float>::iterator it3;
  for (it1 = g->weight.begin(),it2 = g->mean.begin(),it3 = g->deviation.begin();
    it1 != g->weight.end();++it1,++it2,++it3)
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
  sum+=g->theta;
  return sum;
}

float GA::getSteer(float left, float center, float right)
{
  return this->simulate(center, left, right, &this->best_fit);
}
