
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue> 
#include <string>

using namespace std;
///dictionary, implement it in trie with vector of links
///maybe upgrade to map or set later 


struct trieInfo{
    bool endNode;
    int fin;
    trieInfo(bool endNode = false):
        endNode(endNode), fin(0){}
        ///wut?
};
struct trieNode{
    trieInfo info;
    char curChar;
    trieNode* parent;
    vector <trieNode*> linkList;
    trieNode(trieNode* parent = NULL) :
        info(), parent(parent) {
        }
    ///ret a number in [0,linkList.size()] represent expect position
    int findLink(char nextCh) {
        int L = 0, R = int(linkList.size()) - 1;
        while (L <= R){
            int mid = (L + R) >> 1;
            if (linkList[mid]->curChar < nextCh) L = mid + 1;
            else R = mid - 1;
        }
        return L;
    }
   
    int insertChar(const char& nextCh) {
        int pos = findLink(nextCh);
        ///can reuse?
        if (pos == linkList.size() || linkList[pos]->curChar != nextCh){
            trieNode* addNode = new trieNode(this);
            addNode->curChar = nextCh;
            ///push element to vector
            linkList.push_back(NULL);
            for(int i = pos + 1; i < linkList.size(); i++) linkList[i] = linkList[i - 1];
            linkList[pos] = addNode;
        }
        return pos;
    }
};


struct trie{
    trieNode* root;
    trie(){
        root = new trieNode();
    }

    void insert(const string& s){
        trieNode *curNode = root;
        for(auto &ch : s) {
            int pos = curNode->insertChar(ch);
            curNode = curNode->linkList[pos];
        }
        ///end node processing
        curNode->info = trieInfo(true);
    }
    trieNode* traverse(const string& s){
        ///ret end node if s is in the tree, else NULL
        trieNode *curNode = root;
        for(auto &ch : s) {
            int pos = curNode->findLink(ch);
            if (pos == curNode->linkList.size()) 
                return NULL;
            if (curNode->linkList[pos]->curChar != ch) 
                return NULL;
            curNode = curNode->linkList[pos];
        }
        return curNode;
    }
    bool markFinish(const string& s) {
        trieNode* endNode = traverse(s);
        if (endNode == NULL) return 0;
        //cerr << endNode << " " << root << " " << root->info.endNode << '\n';
        endNode->info.fin = 1;
        //cerr << endNode << " " << root << " " << root->info.endNode << '\n';
        return 1;
    }
    
    void trieBFS(vector<trieNode*> &dump, bool finish) {
        queue<trieNode*> nodeQueue;
        nodeQueue.push(root);
        //cerr << root << " " << root->info.endNode << '\n';
        while (!nodeQueue.empty()) {
            trieNode* cur = nodeQueue.front();
            nodeQueue.pop();
            if (cur->info.endNode) {
                if (!finish || cur->info.fin == 0) {
                    dump.push_back(cur);
                }
            }
            for(auto i : cur->linkList)
                nodeQueue.push(i);
        }
    }
    /*legacy
    void trie_DFS(vector <string> &dump,string& s,trieNode *cur){
            if (cur->info.endNode)
                    dump.push_back(s);
            for(auto i:cur->linkList){
                    s.push_back(i->curChar);
                    trie_DFS(dump,s,i);
                    s.pop_back();
            }
    }*/
    vector<trieNode*> getFreeEnd(bool finish){
        vector<trieNode*> ans;
        trieBFS(ans, finish);
        return ans;
    }
    string retrieveName(trieNode* curNode) {
        assert(curNode->info.endNode);
        string answer;
        while (curNode != root) {
            answer.push_back(curNode->curChar);
            curNode = curNode->parent;
        }
        reverse(answer.begin(), answer.end());
        return answer;
    }
};
