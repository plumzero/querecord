
#include "mgraph.h"

int main()
{
    MGraph G;
    
    printf("创建一个图:\n");
    CreateGraph(&G);
    
    printf("输入图的信息:\n");
    VertexType va = { .name = "A" };
    VertexType vb = { .name = "B" };
    VertexType vc = { .name = "C" };
    VertexType vd = { .name = "D" };
    
    // 创建顶点信息
    InsertVertex(&G, va);
    InsertVertex(&G, vb);
    InsertVertex(&G, vc);
    InsertVertex(&G, vd);
    
    // 创建弧或边信息
    InsertArc(&G, "A", "B");
    InsertArc(&G, "A", "C");
    InsertArc(&G, "A", "D");
    InsertArc(&G, "C", "A");
    InsertArc(&G, "C", "B");
    InsertArc(&G, "D", "A");
    
    printf("输出图的顶点和弧:\n");
    DisplayGraph(G);
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
    return 0;
}