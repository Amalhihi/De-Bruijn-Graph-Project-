//
// Created by aviel on 27/06/2023.
//

#include "greadyCycles.h"
bool checkDeepRecursion(vvib& graph,vi& result,int deep,int current,int target,int n) {
    //the recursion. compares the finite destinations(on the L deep) to the start vertex.
    if(deep==0) {
        if(current==target) {
            graph[current].second= true;
            return true;
        }
        return false;
    }
    if(deep<=n){
        graph[current].second= true;
        int mod=pow(2,deep);
        int digit=((target+1) % mod)/(mod/2);
        assert(digit==0||digit==1);
        int max=graph.size()+1;
        int next=((current+1)*2+digit)%max-1;
        if(next==-1 ||graph[next].second) {
            graph[current].second= false;
            return false;
        }
        if(checkDeepRecursion(graph,result,deep-1,next,target,n)) {
            result.push_back(current);
            return true;
        }
        graph[current].second= false;
        return false;
    }

    graph[current].second= true;
    for(int i=0;i<graph[current].first.size();i++) {
        if(graph[graph[current].first[i]].second) continue;
        if(checkDeepRecursion(graph,result,deep-1,graph[current].first[i],target,n)) {
            result.push_back(current);
            return true;
        }
    }
    graph[current].second= false;
    return false;
}


bool startRecursion(vvib& graph,int start,vi& result,int L,int n) {
    //this func is important because we don't want that it marks the start vertex as true,so we can find it later
    for(int i : graph[start].first) {
        if(graph[i].second) continue;
        if(checkDeepRecursion(graph,result,L-1,i,start,n)) {
            result.push_back(start);
            return true;
        }
    }
    return false;
}
bool findCyc(vvib& graph,vi& cyc,int n,int cycSize,int vertex) {
    /*
     * checks if there are a cycle that contains the vertex.
     * always finds if there is one, and vise versa
     * takes the first cycle that it finds (the 0-edges checked first)*/
    assert(graph.size()==pow(2,n)-1);
    assert(cycSize>n);
    assert(graph.size()%cycSize==0);
    //remember start_value=start+1
    if(startRecursion(graph,vertex,cyc,cycSize,n)){
        reverse(cyc.begin(),cyc.end());
        cout<<"cycle: ";
        for(int i=0;i<cyc.size();i++) {
            cout<<(cyc[i]+1)%2;
            if((i+1)%7==0) cout<<" ";
        }
        cout<<endl;
        return true;
    }
    return false;

}
int greedyCycles(vvib& graph,int n,int cycSize,vvi& cyclesVal,int bound){
    //runs findCyc on all the vertex that isn't already in a cycle
    if(bound==0) return 0;
    assert(graph.size()==pow(2,n)-1);
    assert(cycSize>n);
    assert(graph.size()%cycSize==0);
    vi cyc;
    int cycles=0;
    int maxCyc=graph.size()/cycSize;
    int start=0;
    int tries=0;
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> distr(0, graph.size()-1);
    for(int i=0;i<graph.size();i++){
        start=distr(gen);
        //while(graph[start].second) start++;
        start=i;
        if(graph[start].second) continue;
        tries++;
        if(findCyc(graph,cyc,n,cycSize,start)){
            cyclesVal.push_back(cyc);
            cyc.clear();
            cycles++;
            if(cycles>=bound) {
                cout<<"===stats==="<<endl;
                cout<<"Cycles num: "<<cycles<<endl;
                cout<<"left vertexes:"<<graph.size()-cycles*cycSize<<endl;
                return cycles;
            }
        }
    }
    /*cout<<"not in any of them: ";
    int i=0;
    while(i<graph.size()){
        if(!graph[i].second) cout<<i+1<<" ";
        i++;
    }
    cout<<endl;*/
    cout<<"===stats==="<<endl;
    cout<<"Cycles num: "<<cycles<<endl;
    cout<<"left vertexes:"<<graph.size()-cycles*cycSize<<endl;
    return cycles;
}