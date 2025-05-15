#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#define m 2000
#define p 31
using namespace std;

struct Company {
    string name;
    string profit_tax;
    string address;
};
struct HashTable {
    vector<Company> table[m];
};

vector<Company> readCompanyList(string file_name){
    vector<Company> company_list;
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Error opening file: " << file_name << endl;
        return company_list;
    }
    string line;        
    getline(file, line); // bỏ qua "Ten cong ty|MST|Dia chi"
    while (getline(file, line)) {
        Company company;
        size_t pos = 0;

        // Read name
        pos = line.find('|');
        company.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Read profit tax
        pos = line.find('|');
        company.profit_tax = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Read address
        company.address = line;

        company_list.push_back(company);
    }
    file.close();
    return company_list;
}
long long hashString(string company_name){
    long long hash = 0;
    long long p_pow = 1;
    string s = (company_name.size() <= 20) ? company_name : company_name.substr(company_name.size() - 20);

    for (char c : s) {
        hash = (hash + (int)c * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return hash;
}
HashTable* createHashTable(vector<Company> list_company){
    HashTable* ht = new HashTable();

    for ( Company& c : list_company ){
        long long index = hashString(c.name);
        ht->table[index].push_back(c);
    }
    return ht;
}
void insert(HashTable* hash_table, Company company){
    long long index = hashString(company.name);
    hash_table->table[index].push_back(company);
}
Company* search(HashTable* hash_table, string company_name){
    long long index = hashString(company_name);
    for (Company& c : hash_table->table[index]){
        if (c.name == company_name){
            return &c;
        }
    }
    return nullptr;
}
int main(int argc, char* argv[]){
    if (argc != 4) {
        cerr << "Syntax: " << argv[0] << " <file data> <file input> <file output>" << endl;
        return 1;
    }
    string MST = argv[1];
    string input = argv[2];
    string output = argv[3];

    vector<Company> company_list = readCompanyList(MST);
    HashTable* hash_table = createHashTable(company_list);

    ifstream name_file(input);
    ofstream out_file(output);

    if (!out_file.is_open()) {
        cerr << "Error opening file: " << output << endl;
        return 1;
    }
    if (!name_file.is_open()) {
        cout << "Error opening file: " << input << endl;
        return 1;
    }

    string line;
    while (getline(name_file,line)){
        Company* found = search(hash_table,line);
        if (found != nullptr){
            out_file << found->name << "|" << found->profit_tax << "|" << found->address << endl;
        }
    }
    out_file.close();
    return 0;
}