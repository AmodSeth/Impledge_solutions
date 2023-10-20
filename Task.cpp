#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

class TrieNode {
public:
  TrieNode() {}
  TrieNode(char c) { 

    val = c; }

  char val;
  map<char, TrieNode*> children;
  bool is_end;
};

class Trie {
public:
  Trie() { 

    root = new TrieNode(); 

  }

  void insert_trie(string word) {
    TrieNode* curr = root;
    for (char c : word) {
      if (!curr->children.count(c)) {
        curr->children[c] = new TrieNode(c);
      }
      curr = curr->children[c];
    }
    curr->is_end = true;
  }

  bool search_trie(string word) {
    TrieNode* curr = root;
    for (char c : word) {
      //if the ndoe is not found
      if (!curr->children.count(c)) {
        return false;
      }
      curr = curr->children[c];
    }
    return curr->is_end;
  }

vector<int> getindices_trie(string word) {
    vector<int> indices;
    TrieNode* curr = root;
    for (int i = 0; i < word.size(); i++) {
      char c = word[i];
      //if not found
      if (!curr->children.count(c)) {
        return indices;
      }
      curr = curr->children[c];

      if (curr->is_end) {
        indices.push_back(i + 1);
      }
    }
    return indices;
  }



public:
  TrieNode* root;
};


void solve(vector<string> words){

  Trie tree;
  queue<pair<string, string>> queue;
  set<string> compoundWords;

  vector<int> indexGroups;

  for(auto it:words){
    indexGroups = tree.getindices_trie(it);

    for(int i : indexGroups){
      if(i>=it.length()) break;

      queue.push({it,it.substr(i)});

    }



    tree.insert_trie(it);
  }


  int maxLength = 0;
  string longest = " ";
  string secondLongest = " ";

  while(!queue.empty()){
    pair<string,string> p = queue.front();

    string word = p.second;
    queue.pop();

    indexGroups= tree.getindices_trie(word);

    //if the vector is empty
    if(indexGroups.size() == 0) continue;

    // cout<<word<< " ";

    for(int i : indexGroups){
      if(i>word.length()) break;

      if(i == word.length()){

        if(p.first.length() > maxLength){
          secondLongest = longest;
          maxLength = p.first.length();
          longest  = p.first;
        }
        


      }
      else{
        queue.push({p.first,word.substr(i)});
      }


    }




  }
  cout<<longest<<endl;
  cout<<secondLongest<<endl;

  // (tree.search_trie("dogcatsdog"))?cout<<"found":cout<<"not found";

}


int main(){

  #ifndef ONLINE_JUDGE

    ifstream inputFile("input.txt");
    freopen("output.txt","w",stdout); 

    if (!inputFile.is_open()) {
        cerr << "Error opening the file." << endl;
        return 1;
    }

    #endif


    // int t = 1;
    // // cin>>t; 

    // while(t--) solve();

    //reading the file
    vector<string> words;
    string word;
    while (inputFile >> word) {
        words.push_back(word);
    }


    auto start = high_resolution_clock::now();
    //
    solve(words);
     auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);


   cout << "\nTime taken by function : "<< duration.count() << " microseconds";

    //close?
    inputFile.close();


  return 0; 

}
