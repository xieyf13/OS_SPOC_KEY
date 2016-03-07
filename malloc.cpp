//最差匹配
//测试用例说明：文件名为“in”，每行为一个整数与一个字母，字母为‘c’时free
#include <cstdio>
#include <algorithm>

#define MAZ_SIZE 10000

//全局变量及结构
int num;
struct Mem{
    int start;
    int size;
    int next;
    int prev;
    bool free;
}mem[MAZ_SIZE];

//分割
void split(int index, int size){

    mem[index].free = 0;
    if (size == mem[index].size) return;
    mem[num].start = mem[index].start + size;
    mem[num].size = mem[index].size - size;
    mem[num].free = 1;
    mem[index].size = size;
     
    mem[num].next = mem[index].next;
    mem[index].next = num;
    num++;

}

//合并
void merge(int index){

    int cur = index;
    while(mem[cur].next && mem[mem[cur].next].free){
        cur = mem[cur].next;
        mem[index].size += mem[cur].size;
    }
    mem[index].next = mem[cur].next;

}

//malloc实现
int myMalloc(int size){

    int ans = -1;
    for(int k = 1; k; k = mem[k].next){
        if (mem[k].free) merge(k);
        if (mem[k].free && mem[k].size >= size && 
            (ans == -1 || mem[k].size >= mem[ans].size)){
            ans = k;
        }
    }
    split(ans, size);
    return mem[ans].start;

}

//free实现
void myFree(int start){

    for(int k = 1; k; k = mem[k].next){
        if (mem[k].start == start){
            mem[k].free = 1;
            break;
        }
    }

}

//初始化
void init(){

    num = 1;
    mem[num].start = 0;
    mem[num].free = 1;
    mem[num++].size = MAZ_SIZE;

}


/*测试用例说明：文件名为“in”，每行为一个整数与一个字母，字母为‘c’时free*/


//测试函数
void test(int n, char c){
    
    int a = myMalloc(n);
    printf("malloc %d : %d\n", n, a);
    if(c == 'c')
        myFree(a);

}

int main(){

    init();
    
    FILE *fp;
    fp = fopen("in", "r");
    if(fp == NULL)
    {
	printf("failed\n");
	return 1;
    }
    
    int n;
    char c;
    while(fscanf(fp, "%d%c", &n, &c) > 0)
    {
        test(n, c);
    }
    
    fclose(fp);

    return 0;
  
}
