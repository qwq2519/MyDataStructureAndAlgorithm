#ifndef MYDATASTRUCTUREANDALGORITHM_MYDINIC_H
#define MYDATASTRUCTUREANDALGORITHM_MYDINIC_H

#include<climits>
#include<vector>
#include<queue>
#include<cstring>
#include<iostream>
namespace MyDinic {
    const int VERTEX = 1e4 + 7;
    const int EDGE = 1e6 + 7;

    struct edge {//存终点即可，
        int ed;//边的目标节点
        long long capacity;//边的容量
        int id;//反向边的编号，便于找反向边
        //如果不存id，那么要遍历e[ed]，寻找反向边，时间复杂度为线性
    };//表示有向边

    std::vector<edge> e[VERTEX];//图的存储

    int n;//点数
    int m;//边数
    int S;//源点
    int T;//汇点

    int depth[VERTEX];
    int cur[VERTEX];

    bool Bfs() {
        memset(depth, 0xff, sizeof depth);//将depth数组清为-1
        std::queue<int> q;
        q.push(S);
        depth[S] = 1;
        while (!q.empty()) {
            auto t = q.front();
            q.pop();
            auto Size = e[t].size();
            for (size_t i{0}; i < Size; ++i) {

                int ed = e[t][i].ed;
                if (depth[ed] == -1 && e[t][i].capacity) {//还有容量而且该点还为确定深度
                    depth[ed] = depth[t] + 1;
                    q.push(ed);
                }
            }
        }
        return (depth[T] != -1);//没走到，说明s到t没有路了，流不通了，不存在增广路
    }

    long long Dfs(int now, long long limit) {
        if (now == T||(!limit) ) return limit;//到达节点了或没有流量了
        for (int &i{cur[now]}; i < e[now].size(); ++i) {
            /*
             当前弧优化:DFS走到第i条边了,那么前i-1弧到汇点的流一定已经被流满了而没有可行路线了，所以可以去掉
             记录了当前节点st遍历了多少边了，跳过已经遍历过的边
             cur[st] = i; 注意上面有引用
            */
            int ed = e[now][i].ed;
            if (depth[ed] == depth[now] + 1 && e[now][i].capacity) {
                long long t = Dfs(ed, std::min(e[now][i].capacity, limit));
                if (t) {//回溯的时候减去流量
                    e[now][i].capacity -= t;
                    e[ed][e[now][i].id].capacity+=t;
                    return t;//还有路，往回去传递
                }else{
                    depth[ed]=-1;//不可达的点,相当于剪枝，破坏了层次图，去掉不可增广的点
                }
            }
        }
        return 0;//没有增广路了
    }

    long long Dinic(){
        std::cin>>n>>m>>S>>T;
        while(m--){
            int x,y;long long z;
            std::cin>>x>>y>>z;
            int sti=e[x].size();//即将加入新边的编号
            int edi=e[y].size();//即将加入的新边的反向边的编号
            e[x].push_back({y,z,edi});
            e[y].push_back({x,0,sti});//反向边

            /* 无向图的话加上下面这些
             std::swap(x,y);
            sti=e[x].size();
            edi=e[y].size();
            e[x].push_back({y,z,edi});
            e[y].push_back({x,0,sti});*/
        }

        long long ans{0},flow{0};
        while(Bfs()){
            memset(cur, 0, sizeof cur);
            while(flow= Dfs(S,LONG_LONG_MAX)){
                ans+=flow;
            }
        }
        return ans;
    }

}


#endif //MYDATASTRUCTUREANDALGORITHM_MYDINIC_H
