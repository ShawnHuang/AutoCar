#ifndef GA_H
#define GA_H

#include <vector>
#include <iostream>

struct TrainData{
  float front, left, right;
  float y;
};

struct Population{
  float theta;
  std::vector<float> weight;
  std::vector< std::vector< float > > mean;
  std::vector<float> deviation;

  //bool operator=(const coord &o) {
  //  return x == o.x && y == o.y;
  //}

  bool const operator<(const Population &p) const{
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
};

//找最小fit value
typedef std::pair<Population, float> gene_fit;
struct MinFit
{
    bool operator()(const gene_fit& left, const gene_fit& right) const
    {
        return left.second < right.second;
    }
};

class GA
{
  public:
    GA ();
    void init();
    float getSteer(float left, float center, float right);
  private:
    void generatePopulations(int num);
    void reproduction();
    void generateChildPopulations();
    void crossover(Population *g1, Population *g2);
    void mutation(Population *g);

    float fitness(Population *gene);
    float simulate(float xfront, float xleft, float xright, Population *g);
    void importTrain();

    std::vector<TrainData> train;
    std::vector<Population> populations;
    std::vector<Population> pool;

    int iterator;
    Population best_fit;
};
#endif
