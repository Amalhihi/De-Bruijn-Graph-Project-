//
// Created by aviel on 27/06/2023.
//

#include "enum.h"
//some side functions
bool moveOnGraph(vvib& graph,int start,int target,int pathLen,vi& result,int minVertex){
    //runs over the line between 2 given points, and checks that the line is legal part of the cycle
    int current=start;
    int max=graph.size()+1;
    int mod=pow(2,pathLen);
    for(int deep=pathLen;deep>0;deep--){
        if(current<minVertex ||graph[current].second) return false;
        result.push_back(current);
        graph[current].second= true;
        int digit=((target+1) % mod)/(mod/2);
        assert(digit==0||digit==1);
        current=((current+1)*2+digit)%max-1;
        mod/=2;
    }
    assert(current==target);
    return true;
}

int zeroSequence(int word,int n){
    //finds the maximum zero sequence in the binary word
    word++;
    int max=0;
    int current=0;
    for(int digit=0;digit<n;digit++){
        if(word%2==0){
            current++;
        }
        else{
            if(current>max) max=current;
            current=0;
        }
        word/=2;
    }
    assert(word==0);
    return max;


}
void allSonsOf(int start,int deep,vvib graph){
    //prints all the sons of given deep and given vertex, debug function
    if(deep==0){
        cout<<start<<" ";
        return;
    }
    for(int i=0;i<graph[start].first.size();i++){
        allSonsOf(graph[start].first[i],deep-1,graph);
    }
}

//long case functions, 2n<l<=3n
bool checkLongCyc(int start,int p1,int p2,vi&  result,vvib& graph,int n,int l){
    //gets the start point and 2 more points that we chose, and checks if the cycle that they are making is legal
    // remember that the real value is higher in 1
    return moveOnGraph(graph,p1,p2,n,result,start) && moveOnGraph(graph,p2,start,n,result,start);

}
int checkLongStart(int start,int p1,vvib& graph,int n,int l,long long foundCyc,vector<pair<long long,long long>>& edges,vvi& cycles,vvi& finalCyc,vi& result,int maxDigit){
    //gets the start point of the cycle and the chosen p1 point, and counts how many legal cycles there is by choosing the p2 point.
    int startVal=start+1;
    //remember that the real value is higher in 1
    if(!moveOnGraph(graph,start,p1,l-2*n,result,start)) return 0;
    long long cycCount=foundCyc;
    int v=start+1;
    if((v+1)%2==0) v++;
    for(;v<graph.size();v+=2){
        if((v+1)%2==0||zeroSequence(v,n)>=maxDigit ) continue;
        if(checkLongCyc(start,p1,v,result,graph,n,l)){
            finalCyc.push_back(result);
            for(int &vertex : result){
                for(int & cycle:cycles[vertex]){
                    edges.emplace_back(cycCount,cycle);
                }
                cycles[vertex].push_back(cycCount);
            }
            cycCount++;

        }
        for(int i=l-2*n;i<result.size() ;i++){
            graph[result[i]].second=false;
        }
        result.resize(l-2*n);

    }
    return cycCount-foundCyc;


}
long long makeStarts(int start,vvib& graph,int n,int l,long long foundCyc,vector<pair<long long,long long>>& edges,vvi& cycles,vvi& finaCyc){
    //gets the start point of the cycles, and counts how many legal cycles there is.
    int startVal=start+1;
    assert(l<=3*n && l>2*n);
    int maxMod=graph.size()+1; // pow(2,n)
    int maxDigit=0;
    while(maxMod>startVal){
        maxDigit++;
        maxMod/=2;
    }
    if(maxDigit==1) return false;
    if(zeroSequence(start,n)>=maxDigit ) return false;
    int mod=graph.size()+1;
    int offset=pow(2,l-2*n);
    int base=int(startVal*offset) % mod-1;
    long long cycCount=foundCyc;
    int minValue=max(start,base);
    vi result;
    for(int p1=minValue;p1<base+offset;p1+=1){
        if(zeroSequence(p1,n)>=maxDigit ) continue;
        cycCount+=checkLongStart(start,p1,graph,n,l,cycCount,edges,cycles,finaCyc,result,maxDigit);
        for(int & it : result){
            graph[it].second=false;
        }
        result.clear();
    }
    return cycCount-foundCyc;

}

//short case functions, n<l<=2n
bool checkCyc(int start,int via,vi&  result,vvib& graph,int n,int l){
    //gets the start point the second point and checks if the cycle is legal.
    assert(l>n);
    return moveOnGraph(graph,start,via,l-n,result,start) && moveOnGraph(graph,via,start,n,result,start);
}
int checkStart(int start,vvib& graph,int n,int l,long long foundCyc,vector<pair<long long,long long>>& edges,vvi& cycles,vvi& finaCyc){
    //gets the start point and counts how many legal cycles there is by choosing the second point and checking the cycle.
    int startVal=start+1;
    //remember that the real value is higher in 1
    assert(l<=2*n);
    int maxMod=graph.size()+1; // pow(2,n)
    int maxDigit=0;
    while(maxMod>startVal){
        maxDigit++;
        maxMod/=2;
    }
    if(maxDigit==1) return false;
    if(zeroSequence(start,n)>=maxDigit ) return false;
    //zeroSequence(via,n)>=maxDigit
    int mod=graph.size()+1;
    int offset=pow(2,l-n);
    int base=int(startVal*offset) % mod-1;
    long long cycCount=foundCyc;
    int minValue=max(start,base);
    if((minValue+1)%2==0) minValue++;
    vi result;
    for(int v=minValue;v<base+offset;v+=2){
        if((v+1)%2==0||zeroSequence(v,n)>=maxDigit ) continue;
        if(checkCyc(start,v,result,graph,n,l)){
            finaCyc.push_back(result);
            for(int &vertex : result){
                for(int & cycle:cycles[vertex]){
                    edges.emplace_back(cycCount,cycle);
                }
                cycles[vertex].push_back(cycCount);
            }
            cycCount++;

        }
        for(int & it : result){
            graph[it].second=false;
        }
        result.clear();

    }
    return cycCount-foundCyc;


}
vvi circuitEnum(vvib& graph,int n,int cycSize,vvi& cyclesValue){
    vvi cycles(graph.size());
    vector<pair<long long,long long>> edges;
    assert(graph.size()==pow(2,n)-1);
    assert(cycSize>n);
    assert(cycSize<=3*n);
    assert(graph.size()%cycSize==0);
    long long totalCyc=0;
    if(cycSize>n && cycSize<=2*n){
        for(int start=0;start+1<(graph.size()+1)/2;start++){
            totalCyc+=checkStart(start,graph,n,cycSize,totalCyc,edges,cycles,cyclesValue);
        }
    }
    else {
        for(int start=0;start+1<(graph.size()+1)/2;start++){
            totalCyc+=makeStarts(start,graph,n,cycSize,totalCyc,edges,cycles,cyclesValue);
        }
    }
    cout<<"in total: "<<totalCyc<<endl;
    vvb newGraphMat(totalCyc,vb(totalCyc,false));
    for(auto edge:edges){
        newGraphMat[edge.first][edge.second]=newGraphMat[edge.second][edge.first]=true;
    }
    vvi newGraph(totalCyc);
    for(int j=0;j<newGraphMat.size();j++){
        vb cyc=newGraphMat[j];
        for(int i=0;i<cyc.size();i++){
            if(cyc[i]) newGraph[j].push_back(i);
        }
    }
    return newGraph;
}