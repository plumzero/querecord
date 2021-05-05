
#define MAXSIZE 200

typedef struct 		/** 三元组类型定义 */
{
	int i, j;
	DataType e;
} Triple;

typedef struct		/** 矩阵类型的定义 */
{
	Triple data[MAXSIZE];
	int m, n, len;		/** 矩阵的行数，列数和非零元素的个数 */
} TriSeqMatrix;

