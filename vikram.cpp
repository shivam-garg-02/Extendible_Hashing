#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const ll MOD=((1e9)+7);
const ll INF=1e18;

#define F first
#define S second

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i : x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

ll hhhh(ll x){
    return x;
}

ll gt;

ll sw;

bool insert(vector<ll*> &dir, ll val, ll& gd, ll bc){
    if (gd>20) return false;
    ll h=hhhh(val);
    ll ind=(h&((1ll<<gd)-1));
    ll* ptr=dir[ind];
    ll ld=ptr[bc+1];
    // debug(ptr[bc],bc);
    // debug(val);
    if (ptr[bc]<bc){
        // debug(true);
        // debug(val);
        ptr[ptr[bc]]=val;
        ptr[bc]++;
    }
    else{
        if (ld<gd){

            // debug(val);

            ll* nptr=new ll(bc+3);
            nptr[bc]=0;
            nptr[bc+1]=ld+1;
            nptr[bc+2]=gt;gt++;
            // debug(nptr[bc]);
            
            ll temp[bc+1];
            for (ll i=0; i<bc; i++) temp[i]=ptr[i];
            temp[bc]=val;
            
            // debug(nptr[bc]);
            // debug(ptr[bc]);
            ptr[bc]=0;
            ptr[bc+1]=ld+1;
            for (ll i=0; i<dir.size(); i++){
                if (dir[i]==ptr && i&(1ll<<ld)){
                    dir[i]=nptr;
                    // debug(dir[i][bc],nptr[bc],nptr[bc+1]);
                }
            }
            // debug(val);
            for (ll i=0; i<=bc; i++) {
                // debug(u);
                insert(dir,temp[i],gd,bc);
            }
            // debug(val);
        }
        else if (ld==gd){
            debug(ld,gd);
            vector<ll*> dir2;
            dir2=dir;
            for (auto u: dir2) {
                debug(u[bc]);
                dir.push_back(u);
            }
            gd++;
            insert(dir,val,gd,bc);
        }
    }
    return true;
}

bool del(vector<ll*>& dir, ll val, ll& gd, ll bc){
    ll h=hhhh(val);
    ll ind=(h&((1ll<<gd)-1));
    ll* ptr=dir[ind];
    ll ld=ptr[bc+1];
    vector<ll> temp;
    ll fl=0;
    for (ll i=0; i<ptr[bc]; i++){
        if (ptr[i]==val && fl==0) fl=1;
        else temp.push_back(ptr[i]);
    }
    for (ll i=0; i<temp.size(); i++){
        ptr[i]=temp[i];
    }
    ptr[bc]=temp.size();
    if (fl) {
        // if (sw==1 && temp.size()==0){
        //     ll x=0;
        //     for (ll i=0; i<dir.size(); i++){
        //         if (dir[i]==ptr){
        //             x=i^(1ll<<(ld-1));
        //             break;
        //         }
        //     }
        //     ll* optr=dir[x];
        //     for (ll i=0; i<dir.size(); i++){
        //         if ((i&((1ll<<ld)-1))==x){
        //             dir[i]=optr;
        //         }
        //     }
        // }
        return true;
    }
    return false;
}

bool search(vector<ll*>& dir, ll val, ll& gd, ll bc){
    ll h=hhhh(val);
    ll ind=(h&((1ll<<gd)-1));
    ll* ptr=dir[ind];
    for (ll i=0; i<ptr[bc]; i++){
        if (ptr[i]==val) return true;
    }
    return false;
}

void stat(vector<ll*>& dir, ll& gd, ll bc){
    cout<<gd<<endl;
    vector<pair<ll,pair<ll,ll>>> bucks;
    set<ll*> s;
    for (auto u: dir){
        s.insert(u);
    }
    for (auto u: s){
        bucks.push_back({u[bc+2],{u[bc],u[bc+1]}});
    }
    sort(bucks.begin(),bucks.end());
    cout<<bucks.size()<<endl;
    for (auto u: bucks){
        cout<<u.S.F<<" "<<u.S.S<<endl;
    }
}

int main() {
    // #ifndef ONLINE_JUDGE
    // freopen("input.txt", "r", stdin);
    // for getting input frm input.txt
    // freopen("output.txt", "w", stdout);
    // for getting output frm output.txt
    // #else
    // #endif
    ll gd, bc;
    cin>>gd>>bc;
    ll a;
    gt=1;
    sw=0;
    vector<ll*> dir((1ll<<gd));
    ll *b1=new ll(bc+3);
    b1[bc]=0;b1[bc+1]=0;b1[bc+2]=gt;
    gt++;
    for (ll i=0; i<(1ll<<gd); i++){
        dir[i]=b1;
    }
    // vector<pair<bool,vector<ll>>> bu((1ll<<gd),{false,{}});
    //n -> no. if el
    //n+1 -> ld
    //m+2 -> time
    while (cin>>a){
        // debug(a);
        if (a==6) break;
        else if (a==2 || a==3 || a==4){
            ll val;
            cin>>val;
            if (a==2) insert(dir,val,gd,bc);
            else if (a==4) del(dir,val,gd,bc);
            else search(dir,val,gd,bc);
        }
        else stat(dir,gd,bc);
    }
    return 0;
}