/* 
Viết chương trình xếp hạng cho đồ thị có hướng không chu trình.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).

Đầu ra (Output):

In ra màn hình hạng của các đỉnh theo thứ tự của đỉnh, mỗi đỉnh trên 1 dòng:

Hạng đỉnh 1

Hạng đỉnh 2

...

Hạng đỉnh n

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên ta có: hạng của 1 = 0, hạng của 2 = 2 và hạng của 3 = 1.

Chú ý:

Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d%d", &u, &v);
		add_edge(&G, u, v);
	}

*/
#include<stdio.h>
#define MAX_VERTICES 100
#define MAX_ELEMENTS 100
typedef int ElementType;

int rank[MAX_VERTICES];


typedef struct {
    
    int n;
    int A[MAX_VERTICES][MAX_VERTICES];
} Graph;


typedef struct
{
    ElementType data[MAX_ELEMENTS];
    int size;
} List;
/* Tao danh sach rong */
void make_null_list(List *L)
{
    L->size = 0;
}
/* Them mot phan tu vao cuoi danh sach */
void push_back(List *L, ElementType x)
{
    L->data[L->size] = x;
    L->size++;
}
/* Lay phan tu tai vi tri i, phan tu bat dau o vi tri 1 */
ElementType element_at(List *L, int i)
{
    return L->data[i - 1];
}
/* Tra ve so phan tu cua danh sach */
int count_list(List *L)
{
    return L->size;
}

void copy_list(List *s1, List *s2){
    int i, x;
    make_null_list(s1);
    for(i = 1; i <= s2->size; i++){
        x=element_at(s2,i);
        push_back(s1,x);
    }
}

void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			G->A[i][j] = 0;
}

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] += 1; 
}
void ranking(Graph* G) {
    int d[MAX_VERTICES];
    int x, u;
    for (u = 1; u <= G->n; u++)
        d[u] = 0;
    for (x = 1; x <= G->n; x++)
        for (u = 1; u <= G->n; u++)
            if (G->A[x][u] != 0)
                d[u]++;
    List S1, S2;
    make_null_list(&S1);
    for (u = 1; u <= G->n; u++)
        if (d[u] == 0)
            push_back(&S1, u);
    int k = 0, i;
    while (S1.size > 0) {
        make_null_list(&S2);
        for (i = 1; i <= S1.size; i++) {
            int u = element_at(&S1, i);
            rank[u] = k;
            int v;
            for (v = 1; v <= G->n; v++)
                if (G->A[u][v] != 0) {
                    d[v]--;
                    if (d[v] == 0)

                        push_back(&S2, v);
                }
        }
        copy_list(&S1, &S2);
        k++;
    }
}
int main(){
    //freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	ranking(&G);
	for(u = 1; u <= n; u++ ){
	    printf("%d\n", rank[u]);
	}
}