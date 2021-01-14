#include <stdio.h>
#include <stdlib.h>
#include "sort_collection.h"
#include <time.h>

unsigned long compare_count = 0;

void cmp_cnt_rest(void) {
  compare_count = 0;
}

int compare(int ldata, int rdata) {
  compare_count++;
  if      (ldata  < rdata) return -1;
  else if (ldata == rdata) return  0;
  else                     return  1;
}


void swap(int a[], int lidx, int ridx) {
  if(lidx == ridx) return;
  int temp = a[lidx];
  a[lidx] = a[ridx];
  a[ridx] = temp;
}

void display(int a[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

// Insertion sort
/**************************************/
void insertion_sort(int a[], int n) { 
    int i, j;
    int target;
    for (i=1; i < n; i = i + 1){
        target = a[i];
        j = i - 1;
        while (j >= 0 && compare(target,a[j]) == -1){
            a[j+1] = a[j];
            j = j-1;
        }
        a[j+1] = target;
        printf("途中経過: ");
        display(a,n);
    }
}

// Functions for Heap sort
/**************************************/
void sift_down(int a[], int i, int n) {
    int snode, svalue;
    while( 2*i + 1 <= n-1){
        if (2*i + 1 == n-1){
            snode = 2*i + 1;
            svalue = a[2*i + 1];
        }
        else{
            if (compare(a[2*i+1], a[2*i+2]) != -1){
                snode = 2*i + 1;
                svalue = a[2*i + 1];
            }
            else{
                snode = 2*i + 2;
                svalue = a[2*i + 2];
            }
        }
        if (compare(a[i],svalue) == -1){
            a[snode] = a[i];
            a[i] = svalue;
            i = snode;
            
        }
        else return;
    }
    return;
}

void build_heap (int a[], int n) {
    int x;
    for (x = (n+2-1)/2 -1; x >= 0; x = x-1){
      sift_down(a,x,n);
    }
}

void heap_sort (int a[], int n) {
    build_heap(a,n);
    int m;
    for (m = n-1; m > 0; m = m-1){
        swap(a,0,m);
        sift_down(a,0,m);
    }
}

// Functions for Quick sort
/**************************************/
int partition(int a[], int pivot, int left, int right,int n) {
    swap(a,right,pivot);
    int l = left;
    int r = right - 1;
    while(1){
    while (compare(a[l],a[right]) == -1) l = l+1;
    while (l <= r && compare(a[r],a[right]) != -1) r = r-1;
    if (l < r) {
      swap(a,l,r);
     
    }
    else break;
    }
    swap(a,l,right);
    
    return l;
}

void quick_sort(int a[], int left, int right,int n) {
    if (left < right){
        int pivot = right; 
        int p = partition(a, pivot, left, right, n);
        display(a,n);
        printf("pの値: %d ",p);
        printf("a[p]の値: %d ",a[p]);
        quick_sort(a, left, p-1, n);
        quick_sort(a, p+1, right, n);
    }
}

void q_sort(int a[], int n) {
  quick_sort(a, 0, n-1, n);
}

double get_realtime(void){
    struct timespec time;
    clock_gettime(CLOCK_REALTIME, &time);
    return time.tv_sec + (double)time.tv_nsec*1e-9;
}

Queue *create_queue(int len){
    Queue *queue=(Queue*)malloc(sizeof(Queue));
    if(queue != NULL){
        queue -> buffer = malloc(sizeof(int)*len);
        queue -> front = 0;
        queue -> rear = 0;
        queue -> length = len;
        queue -> count = 0;
        if(queue -> buffer == NULL){
            free(queue);
            exit(EXIT_FAILURE);
        }
    }
    return queue;
}


void enqueue(Queue *queue,int d){
    if(queue -> count == queue -> length){
        printf("Queue Overflow !!\n");
        
    }
    else{
        queue -> buffer[queue -> rear] = d;
        if(queue -> rear == queue -> length-1){
            queue -> rear = 0;
        }
        else{
            queue -> rear += 1;
        }
        queue -> count += 1;
    }
}


int dequeue(Queue *queue){
    int number;
    if(queue -> count == 0){
        printf("Queue Underflow!!");
        return EXIT_FAILURE;
    }
    else{
        number = queue -> buffer[queue -> front];
        if(queue -> front == queue -> length -1){
            queue -> front = 0;
        }
        else{
            queue -> front += 1;
        }
        queue -> count -= 1;
        return number;
    }
}


void display_1(Queue *queue) {
    if (queue -> count == 0) {
        printf("Empty queue!");
    }
    else if (queue -> rear > queue -> front) {
        int temp = queue -> front;
        while (temp != queue-> rear) {
            printf("%d ", queue -> buffer[temp]);
            temp += 1;
        }
    }
    else {
        int temp = queue -> front;
        while (temp != queue -> length) {
            printf("%d ", queue -> buffer[temp]);
            temp += 1;
        }
        temp = 0;
        while (temp != queue -> rear) {
            printf("%d ", queue -> buffer[temp]);
            temp += 1;
        }
    }
    printf("\n");
}

void delete_queue(Queue *queue){
    free(queue->buffer);
    free(queue);
    printf("Queue deleted!\n");
}



void radix_sort(int a[],int n,int k){
  int i,j,x;
  int m=1;
  int B[n];
  
  Queue *queue=(Queue*)malloc(sizeof(Queue)*10);
  for(i=0;i<10;i=i+1){
    queue[i]=*(create_queue(n));
  }
  
  for(x=1;x<=k;x=x+1){
    for(i=0;i<n;i=i+1){
      B[i]=(a[i]/m)%10;
    }
    for(i=0;i<n;i=i+1){
      enqueue(&queue[B[i]],a[i]);
    }
    printf("%d桁目のバケット処理完了時:\n",x);
    for(i=0;i<n;i++){
      display_1(&queue[i]);
    }
    printf("\n");
    for(i=0,j=0; j<10; j=j+1){
      while(queue[j].count!=0){
        a[i]=dequeue(&queue[j]);
        i=i+1;
      }
    }
    printf("%d桁目終了時の配列：",x);
    for(i=0;i<n;i=i+1){
      printf("%d ",a[i]);
    }
    printf("\n");
    m=m*10;
  }
  delete_queue(queue);
}

