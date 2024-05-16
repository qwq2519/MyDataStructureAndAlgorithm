#include<iostream>

using std::cin;
using std::cout;
using std::endl;
#include<queue>
using std::queue;
#include<vector>
using std::vector;

const int N=1e5+7;
const int M=5e5+7;

int n,m,ring;
int inDegree[N],num[N];//入度 拓扑序列
bool vis[N];
vector<int> G[N];//图

void TopoSort(){
    int cnt=0;
    queue<int> q;
    for(int i=1;i<=n;++i){
        if(!inDegree[i]){
            q.push(i);
        }
    }

    while(q.size()){
        int x=q.front();
        num[++cnt]=x;
        q.pop();
        for(auto i{0};i<G[x].size();++i){
            int y=G[x][i];
            if(!(--inDegree[y])){
                q.push(y);
            }
        }
    }
    for(int i=1;i<=cnt;++i){
        cout<<num[i]<<' ';
    }
    cout<<endl;
}

void dfs(int now){//回溯枚举所有拓扑序列
    if(now==n+1){
        for(int i=1;i<=n;++i){
            cout<<num[i]<<' ';
        }
        cout<<endl;
        ring=1;
        return ;
    }

    for(int i=1;i<=n;++i){
        if(!inDegree[i]&&!vis[i]){
            num[now]=i;
            vis[i]=1;
            for(const auto &j:G[i]){
                --inDegree[j];
            }
            dfs(now+1);
            vis[i]=0;
            for(const auto &j:G[i]){
                ++inDegree[j];
            }
        }
    }
}



int main(){
    cin>>n>>m;
    int x,y;
    for(int i=1;i<=m;++i){
        cin>>x>>y;
        G[x].push_back(y);
        ++inDegree[y];
    }
    dfs(1);
    if(!ring) {
        cout<<"有环";
    }
    return 0;
}
/*
6 8
 1 3
1 5
1 6
2 5
2 6
3 4
3 5
5 6


*/