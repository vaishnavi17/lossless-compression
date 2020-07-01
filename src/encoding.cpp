#include "encoding.h"
#include <functional>
#include <queue>
#include <vector>
#include <fstream>

using namespace std;

unordered_map<unsigned char, int> buildFrequencyTable(istream &input)
{
    unordered_map<unsigned char, int> freqTable = unordered_map<unsigned char, int>();
    while (input.peek() != EOF)
    {
        unsigned char c;
        c = input.get();
        if (freqTable.find(c) != freqTable.end())
        {
            freqTable[c]++;
        }
        else
            freqTable[c] = 1;
    }
    freqTable[EOF] = 1;
    return freqTable;
}

HuffmanNode *buildEncodingTree(const unordered_map<unsigned char, int> &freqTable)
{
    auto compare = [](HuffmanNode* a, HuffmanNode* b) { return a->count > b->count; };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(compare)> pq(compare);
    for (auto node : freqTable) {
        HuffmanNode* temp = new HuffmanNode(node.first, node.second, NULL, NULL);
        pq.push(temp);
    }
    if (pq.empty()) return NULL;
    while (pq.size()>1) {
        HuffmanNode* t1 = pq.top();
        pq.pop();
        HuffmanNode* t2 = pq.top();
        pq.pop();
        HuffmanNode* n = new HuffmanNode(-1, t1->count + t2->count, t1, t2);
        pq.push(n);
    }
    return pq.top();
}

string tostr(vector<bool>& vec) {
    string ans = "";
    for (bool i : vec) {
        ans+= (i?"1":"0");
    }
    return ans;
}

vector<bool> convertInts(int size, int seq) {
    vector<bool> arr = vector<bool>(size, 0);
    for (int i = size-1; i >=0; i--) {
        arr[i]=(seq%2);
        seq/=2;
    }
    return arr;
}

void dfs(HuffmanNode *Tree, int size, int seq, unordered_map<unsigned char, vector<bool>> &encodingMap,
        unordered_map<unsigned char, unsigned char> &headerMap) {
    if (Tree->isLeaf()) {
        auto c = convertInts(size, seq);
        encodingMap[Tree->character] = c;
        int pos = 0;
        for (bool i : c) {
            pos = (pos<<1) + (i ? 2 : 1);
        }
        headerMap[pos] = Tree->character;
//        cout << c.size() << '\n';
    }
    else {
        dfs(Tree->one, size + 1, (seq<<1) + 1, encodingMap, headerMap);
        dfs(Tree->zero, size + 1, seq<<1, encodingMap, headerMap);
    }
}

unordered_map<unsigned char, vector<bool>> buildEncodingMap(HuffmanNode *encodingTree, unordered_map<unsigned char, unsigned char> &headerMap)
{
    unordered_map<unsigned char, vector<bool>> encodingMap;
    dfs(encodingTree, 0, 0, encodingMap, headerMap);
    return encodingMap;
}

void writeHeader(chunkwriter& out, unordered_map<unsigned char, unsigned char>& headerMap) {
    out.pushByte(headerMap.size());
    for (auto i : headerMap) {
        out.pushByte(i.first);
        out.pushByte(i.second);
    }
}

 void compress(string input_file, string output_file)
 {
     ifstream inp;
     inp.open(input_file, ios::in);
     HuffmanNode* tree = buildEncodingTree(buildFrequencyTable(inp));
     unordered_map<unsigned char, unsigned char> headerMap;
     auto encodingMap = buildEncodingMap(tree, headerMap);

//     for (auto i : encodingMap) {
//         cout << i.first << ' ' << tostr(i.second) << '\n';
//     }

     inp.close();

//     for (auto i : headerMap) {
//         cout << +i.first << ' ' << i.second << '\n';
//     }


     chunkwriter out = chunkwriter(output_file);
     writeHeader(out, headerMap);
     inp.open(input_file, ios::in);
     while (inp.peek() != EOF)
     {
         unsigned char c;
         c = inp.get();
         out.push(encodingMap.at(c));
     }
     out.push(encodingMap.at(EOF));
     inp.close();
     out.close();
     freeTree(tree);

 }

// void decodeData(ibitstream &input, HuffmanNode *encodingTree, ostream &output)
// {
//     // TODO: implement this function
// }


// void decompress(ibitstream &input, ostream &output)
// {
//     // TODO: implement this function
// }

void freeTree(HuffmanNode *node)
{
    if (node == NULL) return;
    freeTree(node->zero);
    freeTree(node->one);
    delete node;
}
