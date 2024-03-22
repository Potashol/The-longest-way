#include <iostream>
#include<stack>
#include<list> 
#include<vector>

using namespace std;

//задание 21, наидлиннейший путь 

class adj_list_node 
{
private:
    int v;
    int weight;
public:
    adj_list_node(int _v, int _w);
    int get_v();
    int get_weight();
};

class graph {
private:
    int v;                    
    list<adj_list_node>* adj; // указатель на массив смежности
public:
    void pre_longest_way(int a, vector<bool>& v, stack<int>& s); //вспомогательная функция
    void longest_way(int a);
    graph(int v);
    ~graph(); 
    void add_edge(int a, int v, int weight);
};

graph::graph(int v)
{
    this->v = v;
    adj = new list<adj_list_node>[v];
}
graph::~graph() 
{
    delete[] adj;
}

void graph::add_edge(int a, int v, int weight)
{
    adj_list_node node(v, weight);
    adj[a].push_back(node); 
}


adj_list_node::adj_list_node(int _v, int _w)
{
    v = _v;
    weight = _w;
}

int adj_list_node::get_v()
{
    return v;
}

int adj_list_node::get_weight()
{
    return weight; 
}

void graph::pre_longest_way(int v, vector<bool>& visited,
    stack<int>& s)
{
    visited[v] = true; //помечаем текущую вершину, как пройденную
    for (adj_list_node node : adj[v]) //повторяем для всех смежных с этой вершиной вершин
    {
        if (!visited[node.get_v()])
            pre_longest_way(node.get_v(), visited, s);
    }
    s.push(v); //перемещаем текущую вершину в стек с топологической сортировкой
}

void graph::longest_way(int a)
{
    int* dist = new int[v];
    for (int i = 0; i < v; i++)
        dist[i] = INT_MAX;
    dist[a] = 0;
    stack<int> s;
    vector<bool> visited(v, false);
    for (int i = 0; i < v; i++)
        if (visited[i] == false)
            pre_longest_way(i, visited, s);
    while (s.empty() == false)
    {
        int u = s.top();
        s.pop();
        if (dist[u] != INT_MAX)
        {
            for (adj_list_node v : adj[u])
            {
                if (dist[v.get_v()] > dist[u] + v.get_weight() * -1)
                    dist[v.get_v()] = dist[u] + v.get_weight() * -1;
            }
        }
    }

    for (int i = 0; i < v; i++) //вывод пути 
    {
        if (dist[i] == INT_MAX)
            cout << "INT_MIN ";
        else
            cout << (dist[i] * -1) << " ";
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    graph g(3);
    g.add_edge(0, 1, 4);
    g.add_edge(1, 2, 5);
    g.add_edge(2, 0, 7);

    int s = 1; 
    g.longest_way(s); 
}