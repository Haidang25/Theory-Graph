/*Cho cấu trúc dữ liệu đồ thị được khai báo sử dụng ma trận đỉnh - đỉnh như sau:

typedef struct {
    int A[100][100];
    int n;
} Graph;
Giả sử đồ thị vô hướng, không chứa khuyên, không chứa đa cung

Viết hàm int deg(Graph* G, int x) để tính bậc của đỉnh x.

int deg(Graph* G, int x) {
}
*/
typedef struct {
    int A[100][500];
    int n, m;
} Graph;
int deg(Graph* G, int x) {
	int y, degree = 0;
	for (y = 1; y <= G->n; y++)
		if (G->A[x][y] > 0)
			degree++;
	return degree;
}