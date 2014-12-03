#ifndef SMATRIX_H
#define SMATRIX_H
typedef struct elem
{
	int i;
	int j;
	int data;
}elem;
class SMatrix
{
private:
	elem earray[30];
	int top;
	int col;
	int row;
public:
	SMatrix();
	void PrintMatrix(bool)const;
	void TransposeMatrix();
	void CreatMatrix();
};
#endif