#ifndef INCLUDE_GUARD_SORT_COLLECTION_H
#define INCLUDE_GUARD_SORT_COLLECTION_H

extern unsigned long compare_count;

void cmp_cnt_rest(void);
void display(int a[], int n);
void insertion_sort(int a[], int n);
void heap_sort(int a[], int n);
void q_sort(int a[], int n);
double get_realtime(void);
void RadixSort(int x[ ], int n, int r);
int compare(int ldata, int rdata) ;
void swap(int a[], int lidx, int ridx) ;
void sift_down(int a[], int i, int n) ;
void build_heap (int a[], int n) ;
int partition(int a[], int pivot, int left, int right, int n) ;
void quick_sort(int a[], int left, int right, int n) ;
typedef struct queue {
  int *buffer;
  int length;
  int front;
  int rear;
  int count;
} Queue;
#endif  // INCLUDE_GUARD_SORT_COLLECTION_H