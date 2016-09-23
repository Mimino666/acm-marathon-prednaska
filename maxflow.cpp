int N;
struct Edge { int from, to, residue; };
vector<Edge> edges;
vector<int> graph[N]; // graph[node] = indexes of outgoing edges

void add_edge(int from, int to, int capacity) {
    graph[from].push_back(edges.size());
    edges.push_back(Edge{from, to, capacity});

    graph[to].push_back(edges.size());
    edges.push_back(Edge{to, from, 0});
}

int back[N];
bool bfs(int source, int sink) {
    memset(back, -1, sizeof(back));
    back[source] = -2;

    queue<int> q;
    q.push(source);
    while (!q.empty() && back[sink] == -1) {
        int node = q.front();
        q.pop();

        for (int i = 0; i < graph[node].size(); ++i) {
            Edge & edge = edges[graph[node][i]];
            if (edge.residue && back[edge.to] == -1) {
                back[edge.to] = graph[node][i];
                q.push(edge.to);
            }
        }
    }
    return back[sink] != -1;
}

int maxflow(int source, int sink) {
    int total_flow = 0;

    while (bfs(source, sink)) {
        // find size of the flow
        int flow = 1<<30, node = sink;
        while (back[node] != -2) {
            Edge & edge = edges[back[node]];
            flow = min(flow, edge.residue);
            node = edge.from;
        }

        // push the flow
        node = sink;
        while (back[node] != -2) {
            Edge & edge = edges[back[node]],
                 & edge2 = edges[back[node]^1];
            edge.residue -= flow;
            edge2.residue += flow;
            node = edge.from;
        }

        total_flow += flow;
    }
    return total_flow;
}
