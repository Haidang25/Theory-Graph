//code
#include <stdio.h>
#include <stdbool.h>
#define maxv 50
#define idx 100
#define oo 9999999
typedef int Vertices;

typedef struct{
    int matrix[maxv][maxv];
    Vertices n;
}Graph;

typedef struct{
    int data[idx];
    int size;
}List;




void makenullList(List *l){
    l->size=0;
}

bool emptyList(List *l){
    return (l->size==0);
}


void pushList(List *l, int element){
    l->data[l->size] = element;
    l->size++;
}


int getList(List *l, int index){
    return l->data[index-1];
}


void initGraph(Graph *g, int n){
    g->n=n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            g->matrix[i][j]=0;
}


void addEdge(Graph *g, int x, int y){
    g->matrix[x][y]=1;
}


bool adjacent(Graph *g, int x, int y){
    return g->matrix[x][y]==1;
}


int degreeInput(Graph *g, int x){
    int count=0;
    for(int i=1;i<=g->n;i++){
        if(adjacent(g,i,x)){
            count++;
        }
    }
    return count;
}


int degreeOutput(Graph *g, int x){
    int count=0;
    for(int i=1;i<=g->n;i++){
        if(adjacent(g,x,i)){
            count++;
        }
    }
    return count;
}


List neighbors(Graph *g, int x){
    List L;
    makenullList(&L);
    for(int i=1;i<=g->n;i++){
        if(adjacent(g,x,i)){
            pushList(&L,i);
        }
    }
    return L;
}


void copyList(List *l1, List *l2){
    makenullList(l1);
    for(int i=1;i<=l2->size;i++){
        int value = getList(l2,i);
        pushList(l1,value);
    }
}

//Các biến toàn cục để phục vụ cho giải thuật xếp hạng đồ thị
int rank[maxv]; //Mảng rank[] để lưu hạng của tất cả các đỉnh trong đồ thị
int d[maxv]; //Mảng d-Degree  để lưu số bậc vào của tất cả các đỉnh trong đồ thị
List L1,L2; //Danh sách L1 lưu những đỉnh có bậc vào bằng 0(gốc cũ), danh sách L2 lưu những đỉnh kề v của u có bậc vào bằng 0(gốc mới)
int k=0; //Bước lặp của giải thuật, hạng của đỉnh sẽ được gán cho bước lặp sau khi xếp hạng 1 đỉnh trong đồ thị xong

//Dựa trên giải thuật ranking để tìm thứ tự topo
List topoSort(Graph *g){
    List toposort;
    makenullList(&toposort);
    int u,n=g->n;
    for(u=1;u<=n;u++) d[u]=0; //Khởi tạo các đỉnh có bậc vào điều bằng 0
    for(u=1;u<=n;u++) d[u] = degreeInput(g,u); //Tính bậc vào cho các đỉnh rồi lưu vào mảng d[]
    makenullList(&L1); //Khởi tạo danh sách L1 lưu những đỉnh gốc(đỉnh có bậc vào bằng 0)
    for(u=1;u<=n;u++) if(d[u]==0) pushList(&L1,u); //Những đỉnh nào là đỉnh gốc sẽ được cho vào danh sách L1(Gốc cũ)
    while(!emptyList(&L1)){ //Duyệt trong khi L1 chưa rỗng
        makenullList(&L2); //Khởi tạo danh sách L2 để chứa các đỉnh kề v của u có bậc vào bằng 0(Gốc mới)
        for(int i=1;i<=L1.size;i++){ //Duyệt các đỉnh gốc vừa được thêm trong danh sách L1
            int u = getList(&L1,i); //Lấy đỉnh gốc ra
            rank[u] = k; //Xếp hạng cho đỉnh gốc bằng bước lặp k
            pushList(&toposort,u); //Đưa đỉnh đó vào danh sách topo sau khi đã xếp hạng xong
            List L = neighbors(g,u); //Tìm đỉnh kề của đỉnh vừa được xếp hạng
            for(int j=1;j<=L.size;j++){ //Duyệt các đỉnh kề
                int v = getList(&L,j); //Lấy đỉnh kề
                d[v]--; //Giảm bậc đỉnh kề đi 1 tương đương với việc xóa đỉnh gốc u(gốc mới) ra khỏi đồ thị
                if(d[v]==0){ //Nếu đỉnh kề v là đỉnh gốc(gốc mới)
                    pushList(&L2,v); //Đưa đỉnh gốc mới vào danh sách L2
                }
            }
        }
        copyList(&L1,&L2);//Sao chép các đỉnh gốc mới trong L2 sang L1
        k++;//Tăng bước lặp lên để xếp hạng cho các đỉnh tiếp theo trong danh sách L1
        //Khi nào danh sách L2 rỗng tức đỉnh gốc cũ không có đỉnh kề thì hiển nhiên -> Giải thuật kết thúc -> vì lúc này L1 đã rỗng
    }
    return toposort;
}

int min(int a, int b){
    return (a<b)?a:b;
}


int max(int a, int b){
    return (a>b)?a:b;
}
int main(){
    Graph g;
    int n, u, x;
    scanf("%d", &n);
    initGraph(&g, n+2); //Đồ thị lúc này sẽ được thêm 2 đỉnh nữa là đỉnh alpha và beta
    int time[100]; //Mảng time lưu thời gian để thực hiện công việc 
    time[n+1] = 0; // d[alpha] = 0
    for (u=1;u<=n;u++) {
        scanf("%d",&time[u]); //Nhập thời gian hoàn thành công việc thứ u (u=1,2,3,...)
        do{
            scanf("%d", &x); //Nhập danh sách công việc trước đó phải làm của công việc u
            if(x>0){ //Nếu không phải đỉnh alpha và beta
              addEdge(&g, x, u); //Thì thêm công việc trước đó của công việc u - thêm cung vào đồ thị  
            } 
        }while(x>0);//Nếu không có công việc trước đó hoặc nhập hết công việc trước đó thì dừng
    }
    
    //Thêm đỉnh alpha vào đồ thị
    for(int i=1;i<=n;i++){
        if(degreeInput(&g,i)==0){
            addEdge(&g,n+1,i);//Nối đỉnh alpha vào đỉnh bắt đầu
        }
    }
    
    //Thêm đỉnh beta vào đỉnh cuối
    for(int i=1;i<=n;i++){
        if(degreeOutput(&g,i)==0){
            addEdge(&g,i,n+2);//Nối đỉnh beta vào đỉnh cuối
        }
    }

    //Muốn tìm thời gian trễ nhất và sớm nhất để bắt đầu công việc thì phải dựa trên thứ tự topo
    List L = topoSort(&g);
    
    int t[100];//Mảng lưu thời gian sớm nhất để bắt đầu công việc
    int T[100];//Mảng lưu thời gian trễ nhất để bắt đầu công việc
    
    t[n+1] = 0; //Khởi tạo t[alpha] = 0
    for (int j=2;j<=L.size;j++){ //Bắt đầu từ đỉnh thứ 2 vì đỉnh thứ 1 đã là đỉnh alpha
        int u = getList(&L,j); //Lấy đỉnh trong danh sách topo ra
        t[u] = -1; //Gán t[u] bằng số nào đó > 0
        for (x=1;x<=g.n;x++){
            if (adjacent(&g,x,u)){ // Nếu u kề xx
                t[u] = max(t[u], t[x] + time[x]); //Tính thời gian sớm nhất hoàn thành công việc
            }
        }
    }
    
    //Tìm thời điểm trễ nhất 
    T[n+2] = t[n+2]; //Khởi tạo T[beta] = t[beta]
    for (int j=L.size-1;j>=1;j--) { //Bắt đầu bằng đỉnh trước đỉnh cuối vì đỉnh cuối đang là đỉnh beta
        int u = getList(&L, j); //Lấy đỉnh trong danh sách topo ra
        T[u] = oo; // Gán T[u] bằng vô cực
        for (int v = 1; v <= g.n; v++){
            if (adjacent(&g,u,v)){ //Nếu v kể u
                T[u] = min(T[u], T[v] - time[u]); //Tính thời gian trễ nhất hoàn thành công việc
            }
        }
    }
    
    //In tổng số tuần sớm nhất để hoàn thành công trình -> t[beta];
    printf("%d\n",t[n+2]);
    
    //In thời gian sớm nhất và trễ nhất để bắt đầu công việc
    for(u=1;u<=g.n;u++) printf("%d-%d\n",t[u],T[u]);
        
    return 0;
}
