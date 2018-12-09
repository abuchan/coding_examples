#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

typedef struct node_t {
  int value[26];
  struct node_t* child[26];
} node_t ;

node_t build_tree(vector<string> genes, vector<int> healths, int first, int last) {
  node_t* tree = (node_t*)calloc(1, sizeof(node_t));
  return tree;
}

int sequence_health(vector<string> genes, vector<int> healths, int first, int last, string seq) {
    int health = 0;
    for (int si = 0; si < seq.length(); si++) {
        for (int gi = first; gi <= last; gi++) {
            string gene = genes[gi];
            int gl = gene.length();
            cout << "looking for " << gene << " in " << seq << " at " << si << "\n";
            if (((seq.length() - si) >= gl) && (seq.compare(si, gl, gene) == 0)) {
                health += healths[gi];
            }
        }
    }
    return health;
}

int main()
{
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string genes_temp_temp;
    getline(cin, genes_temp_temp);

    vector<string> genes_temp = split_string(genes_temp_temp);

    vector<string> genes(n);

    for (int i = 0; i < n; i++) {
        string genes_item = genes_temp[i];

        genes[i] = genes_item;
    }

    string health_temp_temp;
    getline(cin, health_temp_temp);

    vector<string> health_temp = split_string(health_temp_temp);

    vector<int> health(n);

    for (int i = 0; i < n; i++) {
        int health_item = stoi(health_temp[i]);

        health[i] = health_item;
    }

    int s;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int min_health = -1;
    int max_health = -1;

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string firstLastd_temp;
        getline(cin, firstLastd_temp);

        vector<string> firstLastd = split_string(firstLastd_temp);

        int first = stoi(firstLastd[0]);

        int last = stoi(firstLastd[1]);

        string d = firstLastd[2];

        int seq_health = sequence_health(genes, health, first, last, d);

        if ((min_health == -1) || (seq_health < min_health)) {
            min_health = seq_health;
        }

        if (seq_health > max_health) {
            max_health = seq_health;
        }
    }

    cout << min_health << " " << max_health;

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
