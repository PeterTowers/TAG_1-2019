#include <iostream>

#pragma once
#include <iostream>


// TODO: Implement class properly
template <class T> class matrix {
  private:
    std::vector<std::vector<T*>> cells;

  public:
    edge(std::vector<std::vector<T*>> cells) : cells(cells) {};
    edge(std::vector<edge<T*>> edges) {
      std::vector<T*> targets;
      std::vector<T*> sources;

      for (auto& edge : edges){
        auto t = std::find(targets.begin(), output.end(), edge.target());
        auto s = std::find(sources.begin(), output.end(), edge.source());

        if(s == sources.end()) {};

        if(t == targets.end()) { };
      }
        
    };

    std::vector<T*>

    bool operator<<() { return true };
    T* operator[](const unsigned int i, const unsigned int i) { return cells[i][j]; };
}