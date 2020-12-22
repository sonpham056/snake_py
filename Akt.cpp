#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int const length = 3;	
int const Max = 1000;
int I, J, cost; // toa do cua 0
int matrix[length][length] = {{1, 5, 7},//1 2 3 4 0 8 7 5 6
							  {4, 0, 8},
							  {3, 2, 6}};
							  
							/*  {{1, 5, 7},//1 2 3 4 0 8 7 5 6
							  {4, 0, 8},
							  {3, 2, 6}};*/

int result1[length][length] = {{1, 2, 3},
							  {8, 0, 4},
							  {7, 6, 5}};

int result2[length][length] = {{1, 2, 3},
							  {4, 5, 6},
							  {7, 8, 0}};
							  
int result[length][length];


struct Dinh{
	int taci[length][length];
	int h, f, g;
	char path[10];
	char way[100][6];
	int waySize;
};

//stack or queue
bool isEmpty(Dinh o[Max], int n){
	if (n == 0)
		return true;
	return false;
}

void push_Back(Dinh o[Max], int &n, Dinh d){
	n++;
	o[n - 1] = d;
}

void pop(Dinh o[Max], int &n){
	if (isEmpty(o, n))
		printf("mang rong");
	else{
		n--;
	}
		
}

void matrixCopy(int a[][length], int b[][length]){
	for (int i = 0; i < length; i++){
		for (int j = 0; j < length; j++){
			a[i][j] = b[i][j];
		}
	}
}



void findZero(Dinh d){
	for (int i = 0; i < length; i++){
		for (int j = 0; j < length; j++){
			if (d.taci[i][j] == 0){
				I = i;
				J = j;
			}
		}
	}
}

bool checkUp(Dinh d){
	findZero(d);
	if (I > 0 && strcmp(d.path, "xuong") != 0)
		return true;
	return false;
		
}

bool checkLeft(Dinh d){
	findZero(d);
	if (J > 0 && strcmp(d.path, "phai") != 0)
		return true;
	return false;
}

bool checkDown(Dinh d){
	findZero(d);
	if (I < 2 && strcmp(d.path, "len") != 0)
		return true;
	return false;
}

bool checkRight(Dinh d){
	findZero(d);
	if (J < 2 && strcmp(d.path, "trai") != 0)
		return true;
	return false;
}

void swap(int &x, int &y){
	int temp = x;
	x = y;
	y = temp;
}

int calH(Dinh d){
	int dem = 0;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++){
			if (i == 2 && j == 2)
				continue;
			if (d.taci[i][j] != result[i][j])
				dem++;
		}
	return dem;
}

/*int calH2(Dinh d){
	int dem = 0;
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++){
			if (i == 2 && j == 2)
				continue;
			if (d.taci[i][j] != result[i][j])
				dem++;
		}
	return dem;
}*/

void showMatrix(Dinh d){
	for (int i = 0; i < length; i++){
		for (int j = 0; j < length; j++){
			printf("%d ", d.taci[i][j]);
		}
		printf("\n");
	}
	printf("h: %d g: %d f: %d\n", d.h, d.g, d.f);
}

void showMatrix(int a[length][length]){
	for (int i = 0; i < length; i++){
		for (int j = 0; j < length; j++){
			printf("%d ", a[i][j]);
		}
		printf("\n");
	}
}

void sort(Dinh a[Max], int nA){
	for (int i = 0; i < nA - 1; i++){
		for (int j = i + 1; j < nA; j++){
			if (a[i].f <= a[j].f){
				Dinh temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}
}

void wayCopy(Dinh &a, Dinh b, char c[6]){
	for (int i = 0; i < b.waySize; i++){
		strcpy(a.way[i], b.way[i]);
	}
	strcpy(a.way[a.waySize - 1], c);
}

void move(Dinh array[Max], int &nA, Dinh e){
	findZero(e);
	Dinh a, b, c, d;
	
	if (checkUp(e)){
		matrixCopy(a.taci, e.taci);
		swap(a.taci[I][J], a.taci[I - 1][J]);
		a.g = e.g + 1;
		a.h = calH(a);
		a.f = a.h + a.g;
		a.waySize = e.waySize + 1;
		char f[] = "len";
		wayCopy(a, e, f);
		strcpy(a.path, "len");
		push_Back(array, nA, a);
	}
	findZero(e);
	if (checkLeft(e)){
		matrixCopy(b.taci, e.taci);
		swap(b.taci[I][J], b.taci[I][J - 1]);
		b.g = e.g + 1;
		b.h = calH(b);
		b.f = b.h + b.g;
		b.waySize = e.waySize + 1;
		char f[] = "trai";
		wayCopy(b, e, f);
		strcpy(b.path, "trai");
		push_Back(array, nA, b);
	}
	findZero(e);
	if (checkDown(e)){
		matrixCopy(c.taci, e.taci);
		swap(c.taci[I][J], c.taci[I + 1][J]);
		c.g = e.g + 1;
		c.h = calH(c);
		c.f = c.h + c.g;
		c.waySize = e.waySize + 1;
		char f[] = "xuong";
		wayCopy(c, e, f);
		strcpy(c.path, "xuong");
		push_Back(array, nA, c);
	}
	findZero(e);
	if (checkRight(e)){
		matrixCopy(d.taci, e.taci);
		swap(d.taci[I][J], d.taci[I][J + 1]);
		d.g = e.g + 1;
		d.h = calH(d);
		d.f = d.h + d.g;
		d.waySize = e.waySize + 1;
		char f[] = "phai";
		wayCopy(d, e, f);
		strcpy(d.path, "phai");
		push_Back(array, nA, d);
	}
	sort(array, nA);
}

bool check(Dinh a[Max], int n){
	for (int i = 0; i < n; i++){
		if (a[i].h == 0)
			return true;
	}
	return false;
}

int compare(int a[][3], int x, int i, int j){
	long dem = 0;
	for (i;  i < length; i++){
		for (j; j < length; j++){
			if (x > a[i][j] && a[i][j] != 0)
				dem++;
		}
		j = 0;
	}
	return dem;
}

void check(){
	int dem = 0;
	for (int i = 0; i < length; i++){
		for (int j = 0; j < length; j++){
			dem += compare(matrix, matrix[i][j], i, j);
		}
	}
	if (dem % 2 == 0 ){
		matrixCopy(result, result2);
	}
	else
		matrixCopy(result, result1);
	printf("\ndem: %d\n", dem);
}

void deleteElement(Dinh a[], int &n, int pos){
    // Mang rong, khong the xoa.
    if(n <= 0){
        return;
    }
    // Neu pos <= 0 => Xoa dau
    if(pos < 0){
        pos = 0;
    }
    // Neu pos >= n => Xoa cuoi
    else if(pos >= n){
        pos = n-1;
    }
    // Dich chuyen mang
    for(int i = pos; i < n - 1; i++){
        a[i] = a[i+1];
    }
    // Giam so luong phan tu sau khi xoa.
    --n;
}

void nHandler(Dinh o[], int &n){
	for (int i = 0; i < n; i++){
			if (o[i].f > o[n - 1].f){
				deleteElement(o, n, i);
			}
		}
}

void run(){
	check();

	//open
	int countWhile = 0;
	Dinh o[Max];
	int n = 0;
	
	int matrixInit[length][length];//tao 1 mang matrix dau tien
	matrixCopy(matrixInit, matrix);//copy matrix do voi matrix game
	
	Dinh d;							//khoi tao dinh ban dau la trang thai bat dau cua tro choi
	matrixCopy(d.taci, matrix);
	d.g = 0;
	d.h = calH(d);
	d.f = d.h + d.g;
	d.waySize = 1;
	strcpy(d.way[d.waySize - 1], "begin");

	push_Back(o, n, d);
	
	
	while(check(o, n) == false){
		if (n == 0){
			printf("Failed");
			exit(0);
		}
		int nJar = 0;
		Dinh jar[Max];
		//dinh hien tai di den duoc cac dinh nao thi add vao
		move(jar, nJar, o[n - 1]);
	
		pop(o, n);

		if (n >= 1000)
			nHandler(o, n);
		
		for (int i = 0; i < nJar; i++){
			push_Back(o, n, jar[i]);
		}
		sort(o, n);

		
		countWhile++;
	}
	printf("\n=== Ma tran ban dau ===\n");
	showMatrix(matrix);
	printf("\n=== Ket qua ===\n");
	
	//in ket qua
	for (int i = 0; i < n; i++){
		if (o[i].h == 0){
			showMatrix(o[i]);
			printf("\nwhile: %d\n", countWhile);
			for (int j = 0; j < o[i].waySize; j++){
				printf("%s ", o[i].way[j]);
			}
		}
			
	}
}

//main
int main(){
	run();
	return 0;
}
