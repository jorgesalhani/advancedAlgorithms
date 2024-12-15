#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

typedef unordered_map<char, void*> suffixTrie;
typedef vector<suffixTrie*> vst;
typedef vector<int> vi;
typedef vector<string> vs;

suffixTrie raiz;

vi obterLpsKMP(string padrao) {
  int m = padrao.size();
  vi lps(m, 0);
  
  int tamMaiorPrefSuf = 0;
  int i = 1;
  while (i < m) {
    if (padrao[i] == padrao[tamMaiorPrefSuf]) {
      tamMaiorPrefSuf++;
      lps[i] = tamMaiorPrefSuf;
      i++;
      // cout << tamMaiorPrefSuf << "; ";
    } else {
      if (tamMaiorPrefSuf != 0) {
        tamMaiorPrefSuf = lps[tamMaiorPrefSuf - 1];
      } else {
        lps[i] = 0;
        i++;
      }
      // cout << "p[i] = " << padrao[i] << " --- p[tamLPS] = " << padrao[tamMaiorPrefSuf] << endl;
    }
  }

  return lps;
}

vi KMPSearch(string texto, string padrao, vi &lps) {
  vi positions; 
  int n = texto.size();
  int m = padrao.size();
  
  int i = 0;
  int j = 0;

  while (i < n) {
    if (texto[i] == padrao[j]) {
      i++;
      j++;
    }
    if (j == m) {
      positions.push_back(i - j);
      j = lps[j - 1];
      // cout << j << " - ";
    } else 
    if (i < n && texto[i] != padrao[j]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }

  return positions;
}


void insertWord(string word) {
  int tamanho = (int) word.size();

  for (int i = 0; i < tamanho; ++i) {
    suffixTrie* current = &raiz;
    
    for (int j = i; j < tamanho; ++j) {
      if (current->find(word[j]) == current->end()) {
        (*current)[word[j]] = new suffixTrie();
      }
      
      current = (suffixTrie*) ((*current)[word[j]]);
    }
    
    (*current)['$'] = nullptr;
  }
}

void obterCaminho(suffixTrie* node, string currentPath, vs& paths) {
  if (!node) return;
  for (auto& cursor : *node) {
    if (cursor.first == '$') paths.push_back(currentPath);
    else obterCaminho((suffixTrie*) (cursor.second), currentPath + cursor.first, paths);
  }
}

int countWord(string prefix) {
    vs paths;
    obterCaminho(&raiz, "", paths);
    
    // cout << endl << endl;
    // for (auto &x: paths) cout << x << " ";
    // cout << endl << endl;

    vi lps = obterLpsKMP(prefix);
    int total = 0;

    for (string& path : paths) {
      vi matches = KMPSearch(path, prefix, lps);
      if (!matches.empty()) total++;
    }

    return total;
}

void printSufTrie(suffixTrie* raiz, string prefix) {
  for (auto& node : *raiz) {
    if (node.first == '$') {
      cout << prefix << endl;
    } else {
      // cout << prefix << entry.first << endl;
      printSufTrie((suffixTrie*) (node.second), prefix + node.first);
    }
  }
}

bool deleteWord(suffixTrie* node, string word, int depth) {
  if (!node) return false;

  if (depth == (int) word.size()) {
    if (node->find('$') != node->end()) node->erase('$');
    return node->empty();
  }

  char c = word[depth];
  auto it = node->find(c);
  if (it == node->end()) return false;

  suffixTrie* child = (suffixTrie*) (it->second);
  if (deleteWord(child, word, (int) depth + 1)) {
    delete child;
    node->erase(it);
  }

  return node->empty();
}

void processarQueries(int N) {
  int op;
  string word;

  for (int i = 0; i < N; i++) {
    cin >> op >> word;
    // cout << op << " - " << word << ": ";

    switch (op) {
      case 1:
        insertWord(word);
        // cout << "Insert" << endl;
        break;
      
      case 2:
        deleteWord(&raiz, word, 0);
        // cout << "Delete" << endl;
        break;

      case 3:
        cout << countWord(word) << endl;
        break;

      default:
        printSufTrie(&raiz, "");
        break;
    }
  }
}

int main() {
  int N;
  cin >> N;
  processarQueries(N);
  return 0;
}
