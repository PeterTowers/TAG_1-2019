#include <iostream>

template <class T> class digraph
{
private:
    T* data;
    std::vector<digraph<T>*> edges;

public:
    digraph(T value) : data(value) { };
    ~digraph() {};
};