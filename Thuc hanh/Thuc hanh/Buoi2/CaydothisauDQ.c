/*
Cho một đồ thị vô hướng đơn. Hãy dựng (các) cây DUYỆT ĐỒ THỊ khi duyệt đồ thị theo chiều sâu (dùng ĐỆ QUY) bắt đầu từ đỉnh 1.

Nếu đồ thị không liên thông, sau khi duyệt xong lần 1, tìm đỉnh có chỉ số nhỏ nhất chưa duyệt mà duyệt nó, và cứ tiếp tục như thế cho đến khi tất cả các đỉnh đều được duyệt.

Quy ước:

Các đỉnh kề của 1 đỉnh được liệt kê theo thứ tự tăng dần.


Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v nói rằng mô tả cung (u, v).

Đầu ra (Output):

In ra cây duyệt đồ thị theo định dạng:

1 <đỉnh cha của 1>
2 <đỉnh cha của 2>
....
i <đỉnh cha của i>
...
n <đỉnh cha của n>

Quy ước: Nếu 1 đỉnh không có đỉnh cha (nó là đỉnh gốc của cây) thì đỉnh cha của nó là 0.

Xem thêm các ví dụ bên dưới.



Gợi ý:

Sử dụng mảng parent[u] để lưu đỉnh cha của đỉnh u.
Trong quá trình duyệt, thay vì in các đỉnh ra màn hình, ghi nhận lại đỉnh cha của các đỉnh.
Thêm 1 tham số p (đỉnh cha của đỉnh u) cho hàm visit(). Khi gọi đệ quy duyệt v ta truyền u như là đỉnh cha của v.
void visit(Graph* G, int u, int p) {
    ...
    for (các đỉnh kề v của u)
        visit(G, v, u);
}
Khi duyệt xong lần lượt in ra u và parent[u] (u chạy từ 1 đến n).


Hướng dẫn đọc dữ liệu và chạy thử chương trình
Để chạy thử chương trình, bạn nên tạo một tập tin dt.txt chứa đồ thị cần kiểm tra.
Thêm dòng freopen("dt.txt", "r", stdin); vào ngay sau hàm main(). Khi nộp bài, nhớ gỡ bỏ dòng này ra.
Có thể sử dụng đoạn chương trình đọc dữ liệu mẫu sau đây:
	freopen("dt.txt", "r", stdin); //Khi nộp bài nhớ bỏ dòng này.
	Graph G;
	int n, m, u, v, w, e;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	
	for (e = 0; e < m; e++) {
		scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

*/
#include<stdio.h>
/* Khai bao Stack*/
#define MAX_ELEMENTS 100
#define MAX_VERTICES 100
#define MAX_VERTEXES 100
typedef struct {
	int data[MAX_ELEMENTS];
	int size;
} Stack;

typedef int ElementType;
typedef struct {
	ElementType data[MAX_ELEMENTS];
	int size;
} List;

typedef struct {
	int n; 
	int A[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph* G, int n) {
	int i, j;
	G->n = n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			G->A[i][j] = 0;
}

void add_edge(Graph* G, int x, int y) {
	G->A[x][y] += 1; 
	G->A[y][x] += 1; 
}

void make_null(List* L) {
	L->size = 0;
}


void push_back(List* L, ElementType x) {
	L->data[L->size] = x;
	L->size++;
}


ElementType element_at(List* L, int i) {
	return L->data[i-1];
}


int count_list(List* L) {
	return L->size;
}

int adjacent(Graph* G, int x, int y){
	return (G->A[x][y] != 0);
}

List neighbors(Graph *G, int x) {
	int i;
	List list;
	make_null(&list);
	for (i = 1; i <= G->n; i++)
		if (adjacent(G, x, i))
			push_back(&list, i);
	return list;
}

void make_null_stack(Stack* S) {
	S->size = 0;
}

void push(Stack* S, int x) {
	S->data[S->size] = x;
	S->size++;
}

int top(Stack* S) {
	return S->data[S->size - 1];
}

void pop(Stack* S) {
	S->size--;
}

int empty(Stack* S) {
	return S->size == 0;
}

int mark[MAX_VERTEXES];
int parent[MAX_VERTEXES];
void traversal(Graph* G, int x, int p) {
	if (mark[x] == 1)
		return;
	//printf("Duyet %d\n", x);
	parent[x] = p;
	mark[x] = 1;
	List list = neighbors(G, x);
	int j;
	for (j = 1; j <= list.size; j++) {
		int v = element_at(&list, j);
		traversal(G, v, x);
	}
}

int main() {
	Graph G;
	int n, m, e, u, v, i;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (e = 1; e <= m; e++) {
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	for(i = 1; i <= n; i++) {
		mark[i] = 0;
		parent[i]= -1;
	}
	for(i = 1; i <= n; i++) {
		if(mark[i] == 0)
		traversal(&G, i, 0);

	}

	for(i = 1; i <= n; i++) {
		printf("%d %d\n", i, parent[i]);
	}
}
