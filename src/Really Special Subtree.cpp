#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'kruskals' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts WEIGHTED_INTEGER_GRAPH g as parameter.
 */

/*
 * For the weighted graph, <name>:
 *
 * 1. The number of nodes is <name>_nodes.
 * 2. The number of edges is <name>_edges.
 * 3. An edge exists between <name>_from[i] and <name>_to[i]. The weight of the edge is <name>_weight[i].
 *
 */

class Wedge{
    public:
    int from;
    int to;
    int weight;
};

bool operator< (const Wedge& c1, const Wedge& c2)
{
    if (c1.weight == c2.weight) {
        return (c1.weight + c1.from + c1.to) > (c2.weight + c2.from + c2.to);
    }
    return c1.weight > c2.weight;
}

int kruskals(int g_nodes, vector<int> g_from, vector<int> g_to, vector<int> g_weight) {

    vector<vector<int>> adjacencyMatrix(g_nodes, vector<int>(g_nodes, -1));
    for(int idx = 0; idx < g_from.size(); ++idx) {
        adjacencyMatrix[g_from[idx] - 1][g_to[idx] - 1] = g_weight[idx];
        adjacencyMatrix[g_to[idx] - 1][g_from[idx] - 1] = g_weight[idx];
    }

    vector<int> visited(g_nodes, false);
    visited[0] = true;
    priority_queue<Wedge> queue;
    for (int idx = 0; idx < g_nodes; ++idx) {
        if (adjacencyMatrix[0][idx] >=0 )
            queue.push(Wedge{0, idx, adjacencyMatrix[0][idx]});
    }
    int result = 0;

    while (!queue.empty()) {
        Wedge w = queue.top();
        queue.pop();
        if (!visited[w.to]) {
            result += w.weight;
            visited[w.to] = true;
            for (int idx = 0; idx < g_nodes; ++idx) {
                if (adjacencyMatrix[w.to][idx] >=0 && visited[idx] == false )
                    queue.push(Wedge{w.to, idx, adjacencyMatrix[w.to][idx]});
            }
        }
    }


    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string g_nodes_edges_temp;
    getline(cin, g_nodes_edges_temp);

    vector<string> g_nodes_edges = split(rtrim(g_nodes_edges_temp));

    int g_nodes = stoi(g_nodes_edges[0]);
    int g_edges = stoi(g_nodes_edges[1]);

    vector<int> g_from(g_edges);
    vector<int> g_to(g_edges);
    vector<int> g_weight(g_edges);

    for (int i = 0; i < g_edges; i++) {
        string g_from_to_weight_temp;
        getline(cin, g_from_to_weight_temp);

        vector<string> g_from_to_weight = split(rtrim(g_from_to_weight_temp));

        int g_from_temp = stoi(g_from_to_weight[0]);
        int g_to_temp = stoi(g_from_to_weight[1]);
        int g_weight_temp = stoi(g_from_to_weight[2]);

        g_from[i] = g_from_temp;
        g_to[i] = g_to_temp;
        g_weight[i] = g_weight_temp;
    }

    int res = kruskals(g_nodes, g_from, g_to, g_weight);

    // Write your code here.
    fout << res << endl;

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
