

// Created by aviel on 10/07/2023.
//
#include "includes.h"
#include "BuildCycles.h"
#include "primefactors.h"
#include "algorithm"
bool multPol(int pol,int word,int degreePol){
    //find the next bit value using the poly
    int mult=pol&word;
    int sum=0;
    for(int i=0;i<degreePol;i++){
        sum+=(mult%2);
        sum%=2;
        mult/=2;
    }
    return sum;
}
vb buildFirstMatrix(int startBits,int degreePol,int polynomial,vb& bits){
    //calc the first block (we don"t know its size)
    vb series;
    int currentBit=startBits;
    for(int i=0;i<degreePol;i++){
        series.push_back(currentBit%2);
        currentBit/=2;
    }
    int msb=pow(2,degreePol-1);
    currentBit=startBits;
    bool newBit;
    while(!bits[currentBit]){
        bits[currentBit]= true;
        newBit= multPol(polynomial,currentBit,degreePol);
        currentBit/=2;
        currentBit+=msb*newBit;
        series.push_back(newBit);
    }
    for(int i=0;i<degreePol;i++){
        series.pop_back();
    }

    return series;
}
vb buildMatrix(int startBits,int degreePol,int polynomial,int blockSize,vb& bits){
    //calc the next blocks (not the first). we know the block size now
    vb series;
    int currentBit=startBits;
    int freeSpace=blockSize;
    for(int i=0;i<degreePol;i++){
        series.push_back(currentBit%2);
        currentBit/=2;
        freeSpace--;
    }
    int msb=pow(2,degreePol-1);
    currentBit=startBits;
    bool newBit;
    while(freeSpace>0){
        bits[currentBit]= true;
        newBit= multPol(polynomial,currentBit,degreePol);
        currentBit/=2;
        currentBit+=msb*newBit;
        series.push_back(newBit);
        freeSpace--;
    }
    for(int i=0;i<degreePol;i++){
        bits[currentBit]= true;
        newBit=startBits%2;
        startBits/=2;
        currentBit/=2;
        currentBit+=msb*newBit;
    }
    return series;
}
void fillBlock(vvb& block,vb& series){
    //fill the block using the diaganal method
    int a=block.size();
    int b=block[0].size();
    int x=0,y=0;
    int val;
    for(int i=0;i<a*b;i++){
        block[x][y]=series[i];
        x=(x+1)%a;
        y=(y+1)%b;
        val=series[i];
    }
}

void printSeria(vvb& series)
{
    std::cout << "The values in the series are:" << std::endl;
    for (const std::vector<bool>& innerVector : series) {
        for (bool value : innerVector) {
            std::cout << (value ? 1 : 0);
        }
        std::cout << std::endl;
        std::cout << std::endl;

    }
}

// Function to check if the matrix contains a zero block of size x*y
pair<int, int> findZeroBlock(vvb& matrix,unsigned int a,unsigned  int b,unsigned  int x,unsigned  int y) {
    // Iterate through the rows and columns to find the zero block
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            // Check if the current block is a zero block
            bool isZeroBlock = true;
            for (int k = 0; k < x; k++) {
                for (int l = 0; l < y; l++) {
                    if (matrix[(i + k) % a][(j + l) % b] != 0) {
                        isZeroBlock = false;
                        break;
                    }
                }
                if (!isZeroBlock) break;
            }

            // If we found a zero block, return its left-top corner indices
            if (isZeroBlock) return std::make_pair(i, j);
        }
    }

    // If no zero block of size x*y is found, return (-1, -1)
    return std::make_pair(-1, -1);
}
vvb makeBlocks(int polynomial,int degreePol){
    //surround func for calc all the blocks
    vb bm(pow(2,degreePol), false); //bitMap
    vb firstSeries=buildFirstMatrix(1,degreePol,polynomial,bm);
    vvb blocks(bm.size()/firstSeries.size(),vb(firstSeries.size()));
    blocks[0]=firstSeries;
    int startBit=1;
    for(int indexBlock=1;indexBlock<blocks.size();indexBlock++){
        while(bm[startBit]) startBit++;
        vb nextBlock= buildMatrix(startBit,degreePol,polynomial,firstSeries.size(),bm);
        blocks[indexBlock]=nextBlock;
    }
    return blocks;
}
ii checkBlock(vvb& matrix,int x,int y){
    //surround func for findZeroBlock params
    unsigned int a=matrix.size();
    unsigned int b=matrix[0].size();
    ii res=findZeroBlock(matrix,a,b,x,y);
    if(res!=ii(-1,-1)){
        return res;
    }
    return ii(-1,-1);
}
void extendedGCD(int a, int b, int &s, int &r) {
    int s1 = 0, s2 = 1, r1 = 1, r2 = 0;

    while (b != 0) {
        int q = a / b;
        int temp = b;
        b = a % b;
        a = temp;

        int new_s = s1 - q * s2;
        s1 = s2;
        s2 = new_s;

        int new_r = r1 - q * r2;
        r1 = r2;
        r2 = new_r;
    }

    s = s1;
    r = r1;
}
int chineseRemainderTheorem(ii res, int m1, int m2) {
    int a1=res.first;
    int a2=res.second;
    int M = m1 * m2;
    int x, y;
    extendedGCD(m1, m2, x, y);
    // Assuming that moduli m1 and m2 are coprime, as there's no gcd calculation

    int result = (a1 * x * m2 + a2 * y * m1) % M;
    return (result + M) % M; // Ensure the result is non-negative
}
void printOneSeries(vb& series){
    for(auto i:series){
        cout<<i;
    }
    cout<<endl;
}
bool inRange(int start,int end,int len,int index){
    assert(0<=start && start<len && 0<=end && end<len && 0<=index && index<len);
    if(start<end){
        if(index>=start && index<end){
            return true;
        }

    }
    else{
        if(index>=start || index<end){
            return true;
        }
    }
    return false;
}
void specPrintBlock(vvb& block,ii corner,ii windowSize){
    //print block in block format
    unsigned int a=block.size();
    unsigned int b=block[0].size();
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            if(inRange(corner.first,(corner.first+windowSize.first)%a,a,i)&&inRange(corner.second,(corner.second+windowSize.second)%b,b,j)) cout<<"* ";
            else cout<<block[i][j]<<" ";
        }
        cout<<endl;
    }
}void printBlock(vvb& block){
    //print block in block format
    unsigned int a=block.size();
    unsigned int b=block[0].size();
    for(auto i:block){
        for(auto j:i){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}

void runOverBlocks(vvb& seriesMatrix, int degree) {
    vi degreeFactors = decomposeIntoPrimeFactors(degree);
    int sizeSeria=seriesMatrix[0].size();
    cout<<"series total size: "<<seriesMatrix[0].size()<<endl;

    vi blockFactors = decomposeIntoPrimeFactors(seriesMatrix[0].size());
    cout<<"prime factors: ";
    for(auto i:blockFactors) cout<<i<<" ";
    cout<<endl;
    cout<<"window total size (polynomial degree): "<<degree<<endl;
    cout<<"total size factors: ";
    for(auto i:degreeFactors) cout<<i<<" ";
    cout<<endl;
    int numBlocks = seriesMatrix.size();
    cout<<"enter block sizes and window sizes: ";
    int a,b;
    cin>>a>>b;
    int x,y;
    cin>>x>>y;
    while(a*b!=seriesMatrix[0].size() || x*y!=degree ||__gcd(a,b)!=1||x>=a||y>=b){
        cout<<"there is a problem with the given values. enter again: ";
        cin>>a>>b>>x>>y;
    }
    vvb block(a,vb(b));

    for(int blockIdx=0;blockIdx<numBlocks;blockIdx++){
        fillBlock(block,seriesMatrix[blockIdx]);
        ii res=checkBlock(block,x,y);
        if(res!=ii(-1,-1)){
            cout<<"there is zero window of size "<<x<<","<<y<<" in block Number "<<blockIdx<<" and his left-top corner is "<<res.first<<","<<res.second<<endl;
            cout<<"the place of the corner in the original series is "<<chineseRemainderTheorem(res,block.size(),block[0].size())<<endl;
            cout<<"there is the block:"<<endl;
            printOneSeries(seriesMatrix[blockIdx]);
            specPrintBlock(block,res,ii(x,y));
            return;
        }
    }
    cout<<"there is no zero window of the given size"<<endl;
    printSeria(seriesMatrix);
    for(int blockIdx=0;blockIdx<numBlocks;blockIdx++){
        cout<<endl;
        fillBlock(block,seriesMatrix[blockIdx]);
        printBlock(block);
    }

}
void calcAndRun(int polynomial,int degreePol){
    polynomial-=pow(2,degreePol);
    vvb seriaMatrix=makeBlocks(polynomial,degreePol);
    runOverBlocks(seriaMatrix,degreePol);
}




