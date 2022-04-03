#include <bits/stdc++.h>
using namespace std;

#ifndef BUCKET_H
#define BUCKET_H

class bucket
{
public:
    bucket(int, int);
    ~bucket();
    bool insert_element(int);
    bool delete_element(int);
    bool inc_local_depth();
    int return_local_depth();
    int return_bucket_occupancy();
    bool print_bucket();
    bool search_element(int);
    bool empty_bucket();
    vector<int> return_elements();

private:
    int bucket_capacity;
    int local_depth;
    vector<int> elements;
};

#endif

bucket::bucket(int bc, int ld)
{
    bucket_capacity = bc;
    local_depth = ld;
}

bool bucket::inc_local_depth()
{
    local_depth++;
    return true;
}

bool bucket::insert_element(int element)
{
    elements.push_back(element);
    return true;
}

bool bucket::delete_element(int element)
{
    vector<int>::iterator ptr;
    for(ptr = elements.begin(); ptr != elements.end(); ptr++){
        if (*ptr == element){
            break;
        }
    }
    if (ptr == elements.end()){
        return false;
    }
    else{
        elements.erase(ptr);
        return true; 
    }
}

int bucket::return_local_depth()
{
    return local_depth;
}

int bucket::return_bucket_occupancy()
{
    return elements.size();
}

bool bucket::print_bucket()
{
    for(auto element: elements){
        cout << element << " ";
    }
    cout << endl;
    return true;
}

bool bucket::search_element(int element)
{
    vector<int>::iterator ptr;
    for(ptr = elements.begin(); ptr != elements.end(); ptr++){
        if (*ptr == element){
            break;
        }
    }
    if (ptr == elements.end()){
        return false;
    }
    else{
        return true; 
    }
}

bool bucket::empty_bucket()
{
    elements.clear();
    return true;
}

vector<int> bucket::return_elements()
{
    return elements;
}

bucket::~bucket()
{

}

#ifndef HASHTABLE_H
#define HASHTABLE_H

class hashTable
{
public:
    hashTable(int, int);
    ~hashTable();
    bucket* generate_bucket(int, int);\
    bool double_directory();
    bool insert_element(int);
    bool doctor(int);
    bool print_hash_table();
    int return_global_depth(); 
    bool delete_element(int);
    bool search_element(int);
    int return_no_buckets();
    bool print_ans();

private:
    int global_depth;
    int bucket_capacity;
    int no_buckets;
    vector<bucket *> directory;
    vector<bucket *> order_of_buckets;

};

#endif

hashTable::hashTable(int gd, int bc)
{
    global_depth = gd;
    bucket_capacity = bc;
    no_buckets = 0;
    for (int i = 0; i < (1 << gd); i++)
    {
        directory.push_back(generate_bucket(bc, gd));
    }
}

bucket *hashTable::generate_bucket(int bc, int ld)
{
    bucket *b;
    b = new bucket(bc, ld);
    no_buckets++;
    order_of_buckets.push_back(b);
    return b;
}

bool hashTable::double_directory()
{
    for (int i = 0; i < (1 << global_depth); i++)
    {
        bucket *mirror_pointer = directory[i];
        directory.push_back(mirror_pointer);
    }
    global_depth++;
    return true;
}

bool hashTable::insert_element(int element)
{
    int index = (element % (1 << global_depth));
    directory[index]->insert_element(element);
    if (directory[index]->return_bucket_occupancy() <= bucket_capacity)
        return true;
    doctor(index);
    return true;
}

bool hashTable::doctor(int ind)
{
    vector<int> elements = directory[ind]->return_elements();
    int local_depth = directory[ind]->return_local_depth();
    if (local_depth == global_depth)
    {
        double_directory();
        doctor(ind);
    }
    else
    {
        int mirror = (ind ^ (1 << local_depth));

        directory[ind]->inc_local_depth();
        local_depth++;

        directory[ind]->empty_bucket();

        if ((mirror & (1<<(local_depth-1))) == 0){
            int temp = mirror;
            mirror = ind;
            ind = mirror;
        }

        directory[mirror] = generate_bucket(bucket_capacity, local_depth);

        for (int i = 0; i < (1 << global_depth); i++)
            if ((i % (1 << local_depth)) == mirror % (1 << local_depth))
                directory[i] = directory[mirror];

        for (auto x : elements)
        {
            directory[x % (1<<global_depth)]->insert_element(x);
        }

        if (directory[ind]->return_bucket_occupancy() > bucket_capacity)
            doctor(ind);
        else if (directory[mirror]->return_bucket_occupancy() > bucket_capacity)
            doctor(mirror);
    }
    return true;
}

bool hashTable::search_element(int element)
{
    int x = 0;
    for (int i = 0; i < global_depth; i++)
    {
        x += (element & (1 << i));
    }
    return directory[x]->search_element(element);
}

bool hashTable::delete_element(int element)
{
    int x = 0;
    for (int i = 0; i < global_depth; i++)
    {
        x += (element & (1 << i));
    }
    return directory[x]->delete_element(element);
}

bool hashTable::print_hash_table()
{
    int i = 0;
    for (auto u : directory)
    {
        cout << i << " -> " << u->return_local_depth() << " -> ";
        bucket *y = u;
        y->print_bucket();
        i++;
    }
    return true;
}

int hashTable::return_global_depth()
{
    return global_depth;
}

int hashTable::return_no_buckets()
{
    return no_buckets;
}

bool hashTable::print_ans()
{
    cout << global_depth << endl;
    cout << no_buckets << endl;
    for (int i = 0; i < order_of_buckets.size(); i++)
    {
        cout << order_of_buckets[i]->return_bucket_occupancy() << " " << order_of_buckets[i]->return_local_depth() << endl;
    }
    return true;
}

hashTable::~hashTable()
{
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int global_depth;
    int bucket_capacity;
    cin >> global_depth;
    cin >> bucket_capacity;

    hashTable h(global_depth, bucket_capacity);
    int code;
    while(cin >> code){
        if (code == 2){
            int element;
            cin >> element;
            h.insert_element(element);
        }
        else if (code == 3){
            int element;
            cin >> element;
            h.search_element(element);
        }
        else if (code == 4){
            int element;
            cin >> element;
            h.delete_element(element);
        }
        else if (code == 5){
            h.print_ans();
            h.print_hash_table();
        }
        else if (code == 6){
            break;
        }
    }

    return (0);
}