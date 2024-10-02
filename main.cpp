#include "greadyCycles.h"
#include "enum.h"
#include "BuildCycles.h"
#include "Extractdecimal.h"
#include <dirent.h>
#include "includes.h"
void createDeBroyn(int n,vvib& graph){
    int max=pow(2,n);
    assert(graph.size()==max-1);
    int value,push1,push2;
    for(int i=0;i<max-1;i++){
        value=i+1;
        push1=(value*2)%max-1;
        push2=(value*2+1)%max-1;
        if(push1!=-1 &&push2!=max-1) graph[i].first.push_back(push1); //we don't want that 01...1->1......1 edge will exist in the graph
        if(push2!=-1) graph[i].first.push_back(push2);
        graph[i].second= false;
    }
}
unsigned int firstPart(int n,int cycSize,int ratio){
    vvib graph(pow(2,n)-1);
    vvi constCycles;
    vvi cycles;
    int maxCyc=graph.size()/cycSize;
    int bound=int(maxCyc*ratio);
    createDeBroyn(n,graph);
    greedyCycles(graph,n,cycSize,constCycles,bound);
    if(ratio==1) return 0;
    vvi cycGraph=circuitEnum(graph,n,cycSize,cycles);
    int size = 0;
    double number_of_all=pow(2,n)-1;
    double number_of_cyc=number_of_all/cycSize;
    double remaining_circles=number_of_cyc-number_of_cyc*ratio;
    /*for(int i=0;i<cycGraph.size();i++){
        vi cyc=cycGraph[i];
        cout<<"vertx "<<i<<endl;
        for(auto j:cyc){
            cout<<j<<" ";
        }
        cout<<endl;
    }*/


    set<int> independentSet;

    independentSet=find_Maximal_Independent_Set(cycGraph);
    cout << "Maximal Independent Set: ";
    cout <<independentSet.size()<<endl;
    for(int it :independentSet){
        for(int i=0;i<cycles[it].size();i++){
            cout<<(cycles[it][i]+1)%2;
            if((cycSize/3)%i==0) cout<<" ";
        }
    }
    return independentSet.size();
}
std::string current_working_directory()
{
    char* cwd = _getcwd( nullptr, 0 ) ; // **** microsoft specific ****
    std::string working_directory(cwd) ;
    std::free(cwd) ;
    return working_directory ;
}
void partTwo(){
    int polDeg;
    cout<<"enter the polynomial degree: ";
    cin>>polDeg;
    string cur=current_working_directory();
    size_t lastSlashPos = cur.rfind('\\');
    cur= cur.substr(0, lastSlashPos);
    std::string filePath = cur+ "\\Degree" + to_string(polDeg) + ".txt";
    vi decimalNumbers = extractDecimalNumbers(filePath);
    for(int i=0;i<decimalNumbers.size();i++){
        bitset<13> binary(decimalNumbers[i]);
        cout<<i+1<<". "<<binary<<endl;
    }
    cout<<"choose polynomial index: ";
    int index;
    cin>>index;
    bitset<13> binary(decimalNumbers[index]);
    cout<<"the polyinom is: ";
    cout<<index<<". "<<binary<<endl;
    calcAndRun(decimalNumbers[index- 1], polDeg);

}
int main() {
    partTwo();
}
