#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

void print_last_k_lines(string fname, int k) {
  if (k == 0)
    return;

  string lines[k];

  int line_idx = 0;

  string line;
  ifstream fs(fname.c_str());
  
  int str_idx;

  if(fs.is_open()) {
    while(getline(fs, line)) {
      str_idx = line_idx++ % k;
      //cout << line_idx << "," << str_idx << " - " << line << "\n";
      lines[str_idx] = line;
    }
    fs.close();
  }
  
  int start_idx = 0;
  if (line_idx >= k) {
    start_idx = line_idx % k;
  }
  
  //printf("k:%d li:%d si:%d\n", k, line_idx, start_idx);
  
  /*for (int i = 0; i < k; i ++) {
    cout << i << ": ";
    cout << lines[i] << "\n";
  }*/

  for (int i = start_idx; i < start_idx + k; i++) {
    cout << lines[i % k] + "\n";
  }
}

int main(int argc, char* argv[]) {
  print_last_k_lines(argv[1], atoi(argv[2]));
}
