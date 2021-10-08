#include <iostream>
#include <vector>
#include <algorithm>

//Алгоритм поиска компонент связности в графе

void DFS(std::vector<std::vector<int>> &graph, std::vector<bool> &used, std::vector<int> &comp, int v) {
    if(used[v]) return;
    used[v] = true;
    comp.push_back(v);
    for(size_t i = 0; i < graph[v].size(); ++i) {
        int to = graph[v][i];
        if(!used[to]) DFS(graph, used, comp, to);
    }
}

std::vector<std::vector<int>> FindComps(std::vector<std::vector<int>> &graph, std::vector<bool> &used) {
    std::vector<std::vector<int>> complist;
    int n = graph.size();
    for(int i = 0; i < n; ++i) {
        used[i] = false;
    }
    for(int i = 0; i < n; ++i) {
        if(!used[i]) {
            std::vector<int> comp;
            DFS(graph, used, comp, i);
            std::sort(comp.begin(), comp.end());
            complist.push_back(comp);
        }
    }
    return complist;
}

void DisplayVectorComps(std::vector<std::vector<int>> &components) {
    for(int i = 0; i < components.size(); ++i) {
        for(int j = 0; j < components[i].size(); ++j) {
            std::cout << (components[i][j] + 1) << " ";
        }
        std::cout << std::endl;
    }
}

//m - ребра
//n - вершины
int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<bool> used(n);
    std::vector<std::vector<int>> graph(n);
    for(int i = 0; i < m; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x;//начинаем считать с нуля
        --y;
        graph[x].push_back(y); //добавляем очередную вершину в список вершин, соединенных с текущей
        graph[y].push_back(x);
    }
    std::vector<std::vector<int>> complist = FindComps(graph, used);
    std::sort(complist.begin(), complist.end(),
    [](const std::vector<int>& v1, const std::vector<int>& v2) 
    { return v1[0] < v2[0]; });
    DisplayVectorComps(complist);
}

/*
5 4
1 2
2 3
1 3
4 5


1 2 3
4 5

 */