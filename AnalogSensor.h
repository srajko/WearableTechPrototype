#include "Sensor.h"
#include <vector>
#include <algorithm>

class AnalogSensor : public Sensor {
  std::vector<int> history;
public:
  AnalogSensor()
    : Sensor("111111111")
  {
    initialized = true;
    values.resize(3);
  }

  void Clear() {
    history.clear();    
  }

  void Loop() {
    history.push_back(analogRead(A0));
  }

  int sign(int x) {
    return (x > 0) - (x < 0);
  }
  
  void UpdateValues() {
    values[0] = analogRead(A0);
    if(history.size()) {
      auto minElement = std::min_element(history.begin(), history.end());
      auto maxElement = std::max_element(history.begin(), history.end());
      values[1] = *maxElement - *minElement;
      
      int midpoint = (*maxElement + *minElement) / 2;
      int crossings = 0;
      for (auto it = history.begin(); it < history.end(); it++) {
        auto it2 = it;
        it2++;
        if(it2 != history.end()) {
          if(sign(*it - midpoint) != sign(*it2 - midpoint)) {
            crossings++;
          }
        }
      }
      values[2] = float(crossings) / history.size();
    }
  }
};

