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
    vector<int> x = elements;
    return x;
}

bucket::~bucket()
{

}

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

class hash_table
{
public:
    hash_table(int, int);
    ~hash_table();
    bool insert_element(int element);
    bool print_hash_table();
    int return_global_depth(); 
    bool delete_element(int element);
    bool search_element(int element);
    int return_no_buckets();
    bool print_ans();

private:
    int global_depth;
    int bucket_capacity;
    int no_buckets;
    vector<pair<int, bucket *>> directory;
    vector<bucket *> order_of_buckets;
};

#endif

hash_table::hash_table(int gd, int bc)
{
    global_depth = gd;
    bucket_capacity = bc;
    no_buckets = 0;
    bucket *b;
    for(int i = 0; i < (1 << gd); i++){
        b = new bucket(bc, gd);
        directory.push_back({i, b});
        no_buckets++;
        order_of_buckets.push_back(b);
    }
}

bool hash_table::insert_element(int element)
{
    int x = 0;
    for(int i = 0; i < global_depth; i++){
        x += (element & (1<<i));
    }
    bucket *y = directory[x].second;

    int occ = y->return_bucket_occupancy();

    if(occ == bucket_capacity)
    {
        if(y->return_local_depth() == global_depth)
        {
            if (global_depth == 20){
                return false;
            }
            
            for(auto u: directory){
                directory.push_back({(u.first | (1<<global_depth)), u.second});
            }

            int x2 = (x | (1<<global_depth));

            vector<int> elements = y->return_elements();
            y->empty_bucket();
            elements.push_back(element);

            global_depth++;
            y->inc_local_depth();

            bucket *y2 = new bucket(bucket_capacity, global_depth);
            no_buckets++;
            order_of_buckets.push_back(y2);
            directory[x2].second = y2;

            for(auto el: elements){
                insert_element(el);
            }
        }
        else if(y->return_local_depth() != global_depth)
        {
            int ld = y->return_local_depth();

            int real_x = 0;
            for(int i = 0; i < ld; i++){
                real_x += (element & (1<<i));
            }
            int real_x2 = (real_x | (1<<ld));

            vector<int> elements = y->return_elements();
            y->empty_bucket();
            elements.push_back(element);

            y->inc_local_depth();

            bucket *y2 = new bucket(bucket_capacity, (ld+1));
            no_buckets++;
            order_of_buckets.push_back(y2);
            directory[real_x2].second = y2;

            for(int j = 0; j < directory.size(); j++){
                int v = 0;
                for(int i = 0; i <= ld; i++){
                    v += (directory[j].first & (1<<i));
                }
                if (v == real_x){
                    directory[j].second = y;
                }
                else if (v == real_x2){
                    directory[j].second = y2;
                }
            }

            for(auto el: elements){
                insert_element(el);
            }
        }
    }
    else{
        y->insert_element(element);
    }
    return true;
}

bool hash_table::search_element(int element)
{
    int x = 0;
    for(int i = 0; i < global_depth; i++){
        x += (element & (1<<i));
    }
    return directory[x].second->search_element(element);
}   

bool hash_table::delete_element(int element)
{
    int x = 0;
    for(int i = 0; i < global_depth; i++){
        x += (element & (1<<i));
    }
    return directory[x].second->delete_element(element);
}

bool hash_table::print_hash_table()
{
    for(auto u: directory){
        cout << u.first << " -> " << u.second->return_local_depth() << " -> ";
        bucket *y = u.second;
        y->print_bucket();
    }
    return true;
}

int hash_table::return_global_depth()
{
    return global_depth;
}

int hash_table::return_no_buckets()
{
    return no_buckets;
}

bool hash_table::print_ans()
{
    cout << global_depth << endl;
    cout << no_buckets << endl;
    for(int i = 0; i < order_of_buckets.size(); i++){
        cout << order_of_buckets[i]->return_bucket_occupancy() << " " << order_of_buckets[i]->return_local_depth() << endl;
    }
    return true;
}

hash_table::~hash_table()
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

    hash_table h(global_depth, bucket_capacity);
    int code;
    while(1){
        cin>>code;
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
            // h.print_hash_table();
        }
        else if (code == 6){
            break;
        }
    }

    return (0);
}