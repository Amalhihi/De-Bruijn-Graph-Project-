//
// Created by aviel on 10/07/2023.
//

#ifndef DEBROYNEXP_BUILDCYCLES_H
#define DEBROYNEXP_BUILDCYCLES_H
vb buildFirstMatrix(int startBits,int degreePol,int polynomial,vb& bits);
pair<int, int> findZeroBlock(const vvi& matrix, int a, int b, int x, int y);
vb buildMatrix(int startBits,int degreePol,int polynomial,int blockSize,vb& bits);
vvb makeBlocks(int polynomial,int degreePol);
void calcAndRun(int polynomial,int degreePol);
void printSeria(vvb& seria);

#endif //DEBROYNEXP_BUILDCYCLES_H
