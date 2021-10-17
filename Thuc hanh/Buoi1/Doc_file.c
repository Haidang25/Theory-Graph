/*
Hãy viết chương trình đọc đồ thị từ tập tin và hiển thị ma trận kề của đồ thị này.

Giả sử đồ thị được cho là đồ thị vô hướng đơn.

Đầu vào (Input):

Dữ liệu đầu vào được nhập từ tập tin dt1.txt với định dạng:

- Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.

- m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả cung (u, v).

Đầu ra (Output):

In ra Ma trận kề (0/1) của đồ thị

Ví dụ:

Nếu đầu vào là:

4 4
1 2
1 3
2 3
3 4
Kết quả là:

0 1 1 0 
1 0 1 0 
1 1 0 1 
0 0 1 0
*/
#include<stdio.h>
#define max 50
typedef struct {
    int n;
    int A[max][max];
} Graph;
void add_edge(Graph *G, int x, int y){
    G->A[x][y] = 1;
    G->A[y][x] = 1;
}

int main(){
    Graph G;
	int n, m, u, v, e;
	FILE* file = fopen("dt1.txt", "r");
	fscanf(file, "%d%d", &n, &m);
	for (e = 1; e <= n; e++) {
		fscanf(file, "%d%d", &u, &v);
		add_edge(&G, u, v);
	}
	for(e = 1; e <= n; e++) {
	    for(v = 1; v <= n; v++){
	        printf("%d ", G.A[e][v]);
	    }
	    printf("\n");
	}
}