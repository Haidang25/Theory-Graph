/*
Peter rất thích chơi đá. Anh ta thường dùng đá để trang trí sân nhà của mình. Hiện tại Peter có n hòn đá. Dĩ nhiên mỗi hòn đá có một khối lượng nào đó. Peter muốn đặt các hòn đá này dọc theo lối đi từ cổng vào nhà của mình. Peter lại muốn sắp xếp như thế này: hòn đá nặng nhất sẽ đặt ở cạnh cổng rào, kế tiếp là hòn đá nặng thứ 2, ... hòn đá nhẹ nhất sẽ được đặt cạnh nhà. Như vậy nếu đi từ trong nhà ra cổng, ta sẽ gặp các hòn đá có khối lượng tăng dần.

Tuy nhiên, điều khó khăn đối với Peter là anh chỉ có một cây cân đĩa mà không có quả cân nào. Nói cách khác, mỗi lần cân Peter chỉ có thể biết được hòn đá nào nhẹ hơn hòn đá nào chứ không biết nó nặng bao nhiêu kg.

Sau m lần cân, Peter biết được sự khác nhau về cân nặng của m cặp. Với các thông tin này, hãy giúp Peter sắp xếp các viên đá theo thứ tự anh mong muốn.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số hòn đó và số lần cân

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng hòn đá u nhẹ hơn hòn đá v.

Đầu ra (Output):

In ra màn hình thứ tự của các hòn đá theo khối lượng tăng dần. In các số thứ tự trên cùng một dòng, mỗi số cách nhau một khoảng trắng.

Bạn có thể yên tâm là dữ liệu đầu được giả sử rằng chỉ có một kết quả quả duy nhất.

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên ta có: hòn đá 1 nhẹ nhất, kế đến là hòn đá 3 và sau cùng là hòn đá 2.
*/
#include<stdio.h>
#define MAX_VERTICES 100
#define MAX_ELEMENTS 100
typedef int ElementType;

int rank[MAX_VERTICES];
typedef struct {
    int data[MAX_ELEMENTS];
    int front, rear;
} Queue;
void make_null_queue(Queue* Q) {
	Q->front = 0;
	Q->rear = -1;
}

void push(Queue* Q, int x) {
	Q->rear++;
	Q->data[Q->rear] = x;
}

int top(Queue* Q) {
	return Q->data[Q->front];
}

void pop(Queue* Q) {
	Q->front++;
}

int empty(Queue* Q) {
	return Q->front > Q->rear;
}
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
int adjacent(Graph* G, int x, int y){
	return (G->A[x][y] != 0);
}
List neighbors(Graph *G, int x) {
	int i;
	List list;
	make_null_list(&list);
	for (i = 1; i <= G->n; i++)
		if (adjacent(G, x, i))
			push_back(&list, i);
	return list;
}
int emptyList(List *l){
    if(l->size == 0)
        return 1;
    return 0;
}
int deg(Graph* G, int x) {
	int y, degree = 0;
	for (y = 1; y <= G->n; y++)
		if (G->A[x][y] > 0)
			degree++;
	return degree;
}

List topo_sort(Graph *G){
    int d[MAX_VERTICES];
    int x, u;
    Queue Q;
    make_null_queue(&Q);
    List L;
    for (u = 1; u <= G->n; u++)
        d[u] = 0;
     for (x = 1; x <= G->n; x++)
        for (u = 1; u <= G->n; u++)
            if (G->A[x][u] != 0)
                d[u]++;
    for (u = 1; u <= G->n; u++)
        if (d[u] == 0)
            push(&Q, u);
    make_null_list(&L);
    int k = 0, i;
    for(i = 1; !empty(&Q); i++) {
        int u = top(&Q);
        pop(&Q);
        rank[u] = k;
        push_back(&L, u);
        int v;
        for (v = 1; v <= G->n; v++)
            if (G->A[u][v] != 0) {
                d[v]--;
                if (d[v] == 0)
                    push(&Q, v);
            }
    }
    return L;    
    
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
	List L = topo_sort(&G);
	for(u = 1; u <= L.size; u++) {
	    printf("%d ", element_at(&L, u));
	}
    return 0;

}