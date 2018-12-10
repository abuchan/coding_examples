#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

typedef struct node_t {
  int health[26];
  struct node_t* child[26];
} node_t ;

vector<int> str_to_int_vec(string str) {
  vector<int> v = vector<int>(str.length());
  for (int i = 0; i < str.length(); i++) {
    v[i] = str[i] - 'a';
  }
  return v;
}

void add_gene_to_tree(node_t* tree, string gene, int health) {
  node_t* node = tree;
  vector<int> gene_vec = str_to_int_vec(gene);
  
  //cout << "Adding " << gene << "-" << health << "\n";

  for (int i = 0; i < gene.length(); i++) {
    int chr_idx = gene_vec[i];

    if (i == gene.length() - 1) {
      node->health[chr_idx] += health;
    } else if (node->child[chr_idx] == NULL) {
      node->child[chr_idx] = (node_t*)calloc(1, sizeof(node_t));
    }
    
    node = node->child[chr_idx];
  }
}

node_t* build_tree(vector<string> genes, vector<int> healths, int first, int last) {
  node_t* tree = (node_t*)calloc(1, sizeof(node_t));
  for (int i = first; i <= last; i++) {
    add_gene_to_tree(tree, genes[i], healths[i]);
  }
  return tree;
}

void print_node(node_t* node) {
  printf("Node 0x%08X\n", (uint64_t)node);
  for (int i = 0; i < 26; i++) {
    if ((node->health[i] != 0) || (node->child[i] != NULL)) {
      printf("  %c (%d) : 0x%08X\n", 'a' + i, node->health[i], (uint64_t)node->child[i]);
    }
  }
}

void print_tree(node_t* tree) {
  print_node(tree);
  for (int i = 0; i < 26; i++) {
    if (tree->child[i] != NULL) {
      print_tree(tree->child[i]);
    }
  }
}

long sequence_health(vector<string> genes, vector<int> healths, int first, int last, string seq) {
    long health = 0;
    
    for (int si = 0; si < seq.length(); si++) {
        for (int gi = first; gi <= last; gi++) {
            string gene = genes[gi];
            int gl = gene.length();
            //cout << "looking for " << gene << " in " << seq << " at " << si << "\n";
            if (((seq.length() - si) >= gl) && (seq.compare(si, gl, gene) == 0)) {
                health += healths[gi];
            }
        }
    }
    
    return health;
}

long sequence_health(node_t* tree, vector<int> seq_vec, int start);

long sequence_health(node_t* tree, string seq) {
  long health = 0;
  vector<int> seq_vec = str_to_int_vec(seq);
  
  //cout << "Checking " << seq << "\n";
  //print_tree(tree);
  
  for (int i = 0; i < seq.length(); i++) {
    long sub_health = sequence_health(tree, seq_vec, i);
    //cout << " " << i << ":" << sub_health << "\n";
    health += sub_health;
  }
  
  //cout << "Total " << health << "\n\n";
  return health;
}

long sequence_health(node_t* tree, vector<int> seq_vec, int start) {
  int chr_idx = seq_vec[start];
  long health = tree->health[chr_idx];
  
  //cout << "Node health:" << seq_vec[start] << ":" << health << "\n";
  if (start < seq_vec.size() - 1) {
    if (tree->child[chr_idx] != NULL) {
      health += sequence_health(tree->child[chr_idx], seq_vec, start + 1);
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

    long min_health = -1;
    long max_health = -1;
    
    double total_tree_time = 0.0;
    double total_naive_time = 0.0;

    for (int s_itr = 0; s_itr < s; s_itr++) {
        string firstLastd_temp;
        getline(cin, firstLastd_temp);

        vector<string> firstLastd = split_string(firstLastd_temp);

        int first = stoi(firstLastd[0]);

        int last = stoi(firstLastd[1]);

        string d = firstLastd[2];
        
        clock_t start_clk = clock();

        //cout << "Tree " << first << "," << last << "\n";
        node_t* tree = build_tree(genes, health, first, last);
        //print_tree(tree);

        long seq_health = sequence_health(tree, d);
        //long seq_health = 0;//sequence_health(tree, d);
        
        clock_t tree_clk = clock();

        long test_health = sequence_health(genes, health, first, last, d);
        
        clock_t naive_clk = clock();

        total_tree_time += ((double)(tree_clk - start_clk))/CLOCKS_PER_SEC;
        total_naive_time += ((double)(naive_clk - tree_clk))/CLOCKS_PER_SEC;
        
        if (s_itr % 10 == 0) {
          cout << total_tree_time / s_itr << " " << total_naive_time / s_itr << "\n";
        }

        if ((min_health == -1) || (seq_health < min_health)) {
            min_health = seq_health;
        }

        if (seq_health > max_health) {
            max_health = seq_health;
        }
        
        //cout << s_itr << " of " << s << ":" << seq_health << "\n";
        //cout << min_health << " " << max_health << "\n";
    }

    cout << min_health << " " << max_health << "\n";

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
