
#include "adjgraph.h"

int main()
{
    AdjGraph G;
        
    printf("创建一个图:\n");
    CreateGraph(&G, UG);
    
    printf("输入图的信息:\n");    
    VNode va("A");
    VNode vb("B");
    VNode vc("C");
    VNode vd("D");
    VNode ve("E");
    VNode vf("F");
    VNode vg("G");
    VNode vh("H");
    VNode vi("I");
    
    // 创建顶点信息
    InsertVertex(&G, va);
    InsertVertex(&G, vb);
    InsertVertex(&G, vc);
    InsertVertex(&G, vd);
    InsertVertex(&G, ve);
    InsertVertex(&G, vf);
    InsertVertex(&G, vg);
    InsertVertex(&G, vh);
    InsertVertex(&G, vi);
    
    // 创建弧或边信息
    InsertArc(&G, "A", "B");
    InsertArc(&G, "A", "C");
    InsertArc(&G, "A", "D");
    InsertArc(&G, "B", "E");
    InsertArc(&G, "C", "F");
    InsertArc(&G, "D", "G");
    InsertArc(&G, "D", "H");
    InsertArc(&G, "E", "F");
    InsertArc(&G, "G", "H");
    InsertArc(&G, "G", "I");
    
    printf("输出图的顶点和弧(边):\n");
    DisplayGraph(G);
    
    printf("深度优先遍历输出:\n");
    DFSTraverseGraph(G);
    printf("\n");
    
    printf("图的广度优先遍历:\n");
    BFSTraverseGraph(G);
    printf("\n");
    
    printf("销毁图:\n");
    DestroyGraph(&G);
    
    return 0;
}