
#include <stdio.h>
#include <math.h>

#define ALPHA       1.0             // 反射点线段比例 α
#define GAMMA       1.0             // 扩展点线段比例 γ
#define BETA        0.5             // 压缩点线段比例 β
#define SCALE       0.5             // 初始点到各个单纯形顶点的步长
#define MATSIZ      50              // 函数变量个数
#define MAXIT       6000            // 最大迭代次数
#define VERR        1.0e-8          // 计算允许误差


typedef struct _PT {                // 定义单纯形顶点数据类型结构
    float f;                        // 顶点函数值
    float x[MATSIZ];                // 顶点坐标
} PT;

typedef float (*PFN) (float*);      // 函数指针类型定义

PT v[MATSIZ + 1], vm, vr, ve, vc;   // 单纯形顶点，中点，反射点，扩展点和收缩点

int vs;                             // 最小值顶点索引
int vg;                             // 最大值顶点索引
int vh;                             // 第 2 个最大值顶点索引

/** 计算单纯形顶点的函数值 */
void calc_vertexf(PFN fn, int n, PT * pt)
{
    int j;
    float vtmp[MATSIZ];
    
    for (j = 0; j < n; j++) {
        vtmp[j] = pt->x[j];
    }
    pt->f = (*fn)(vtmp);
}
/** 初始单纯形顶点坐标 */
void init(PFN fn, int n, float * start, PT * pts)	/** start 是函数极值点的初始估计值 */
{
    float pn, qn;
    int i, j;
    /** 初始化单纯形的顶点，其中 start 为函数变量的估计值 */
    pn = SCALE * (sqrt(n + 1) - 1 + n) / (n * sqrt(2.));
    qn = SCALE * (sqrt(n + 1) - 1) / (n * sqrt(2.));
    for (j = 0; j < n; j++) {
        pts[0].x[j] = start[j];
    }
    for (i = 1; i < n + 1; i++) {
        for (j = 0; j < n; j++) {
            if (i - 1 == j)
                pts[i].x[j] = pn + start[j];
            else
                pts[i].x[j] = qn + start[j];
        }
    }
    /** 计算所有顶点的函数值 */
    for (i = 0; i < n + 1; i++) {
        calc_vertexf(fn, n, &pts[i]);
    }
}
/** 查找 SHG 顶点的索引 */
void find_vertex_indexes(int n)
{
    int i, j;
    /** 寻找最小值和最大值索引 */
    vs = 0;
    vg = 0;
    for (i = 0; i < n + 1; i++) {
        if (v[i].f < v[vs].f)
            vs = i;
        if (v[i].f > v[vg].f)
            vg = i;
    }
    /** 查找第 2 个最大值索引 */
    vh = vg;
    for (i = 0; i < n + 1; i++) {
        if (v[i].f > v[vh].f && v[i].f < v[vg].f)
            vh = i;
    }
}
/** 特殊点计算 - 中点 */
void calc_center_pt(int n)
{
    int i, j;
    float cent;
    
    for (j = 0; j < n; j++) {
        cent = 0.0;
        for (i = 0; i < n + 1; i++) {
            if (i != vg) {
                cent = cent + v[i].x[j];
            }
        }
        vm.x[j] = cent / n;
    }
}
/** 特殊点计算 - 反射点 */
void calc_reflect_pt(PFN fn, int n)
{
    int j;
    
    for (j = 0; j < n; j++) {
        vr.x[j] = (1 + ALPHA) * vm.x[j] - ALPHA * v[vg].x[j];
    }
    calc_vertexf(fn, n, &vr);
}
/** 特殊点计算 - 扩展点 */
void calc_extend_pt(PFN fn, int n)
{
    int j;
    
    for (j = 0; j < n; j++) {
        ve.x[j] = (1 + GAMMA) * vr.x[j] - GAMMA * vm.x[j];
    }
    calc_vertexf(fn, n, &ve);
}
/** 特殊点计算 - 压缩点 */
void calc_contract_pt(PFN fn, int n)
{
    int j;
    
    for (j = 0; j < n; j++) {
        vc.x[j] = BETA * v[vg].x[j] + (1 - BETA) * vm.x[j];
    }
    calc_vertexf(fn, n, &vc);
}
/** 收缩计算 */
void shrink(PFN fn, int n)
{
    int i, j;
    
    for (i = 0; i < n + 1; i++) {
        if (i != vs) {
            for (j = 0; j < n; j++) {
                v[i].x[j] = v[vs].x[j] + (v[i].x[j] - v[vs].x[j]) / 2.0;
            }
            calc_vertexf(fn, n, &v[i]);
        }
    }
}
/** 迭代终止判断 */
int checkout(int n)
{
    int i;
    float fsum, favg, s;
    
    fsum = 0.0;
    for (i = 0; i < n + 1; i++) {
        fsum = fsum + v[i].f;
    }
    favg = fsum / (n + 1.);
    s = 0.0;
    for (i = 0; i < n + 1; i++) {
        s = s + (v[i].f - favg) * (v[i].f - favg) / n;
    } 
    s = sqrt(s);
    if (s < VERR) {
        return 1;
    }
    
    return 0;
}
/** NM 算法主程序 */
void simplex(PFN fn, float * start, float * fmin, int n)
{
    int i, j , m;
    
    init(fn, n, start, v);
    for (m = 0; m < MAXIT; m++) {
        find_vertex_indexes(n);
        calc_center_pt(n);
        calc_reflect_pt(fn, n);
        if (vr.f > v[vs].f && vr.f <= v[vh].f) {
            v[vg] = vr;     // 用 R 点替换 G 点
        }
        if (vr.f <= v[vs].f) {
            calc_extend_pt(fn, n);
            if (ve.f < vr.f)
                v[vg] = ve; // 用 E 点替换 G 点
            else
                v[vg] = vr; // 用 R 点替换 G 点
        }
        if (vr.f > v[vh].f) {
            calc_contract_pt(fn, n);
            if (vc.f < v[vg].f)
                v[vg] = vc; // 用 C 点替换 G 点
            else
                shrink(fn, n);  // 收缩，产生新单纯形
        }
        if (checkout(n)) {
            break;
        }
    }
    /** 查找最小值顶点 */
    vs = 0;
    for (i = 0; i < n + 1; i++) {
        if (v[i].f < v[vs].f)
            vs = i;
    }
    for (j = 0; j < n; j++) {
        start[j] = v[vs].x[j];
    }
    /** 获得最小函数值顶点坐标并取得函数值，即得到当函数为最小值时的变量值 */
    *fmin = (*fn)(start);
}


/** 测试函数 */
float myfunc(float * x)
{
    float fx;
    
    fx = (x[0] * x[0] - 13) * (x[0] * x[0] - 13);

    return fx;
}

int main()
{
    float fmin;
    float start[1];
    
    start[0] = 70;
    simplex(myfunc, start, &fmin, 1);
    
    printf("%f %f\n", start[0], fmin);
    
    return 0;
}