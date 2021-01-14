#include <stdio.h>
#include <stdlib.h>
#include "sort_collection.h"
#include <time.h>

int GetRandom(int min, int max) {
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

int main(int argc, char *argv[]) {
  if (argc != 1) {
    int numdata = atoi(argv[1]);  // set numdata with cmd. argument
    int *array_insert = (int*)malloc(sizeof(int) * numdata);
    int *array_heap = (int*)malloc(sizeof(int) * numdata);
    int *array_quick = (int*)malloc(sizeof(int) * numdata);

    int i;
    printf("Enter %d integers\n", numdata);
    for (i = 0; i < numdata; i++) {
      int number;
      scanf("%d", &number);
      array_insert[i]=number;
      array_heap[i]=number;
      array_quick[i]=number;
    }

    insertion_sort(array_insert, numdata);
    printf("insert_sort result\n");
    display(array_insert, numdata);
    printf("# of comparisons: %lu\n", compare_count);
    cmp_cnt_rest();
    printf("\n");

    heap_sort(array_heap, numdata);
    printf("heap_sort result\n");
    display(array_heap, numdata);
    printf("# of comparisons: %lu\n", compare_count);
    cmp_cnt_rest();
    printf("\n");

    q_sort(array_quick, numdata);
    printf("q_sort result\n");
    display(array_quick, numdata);
    printf("# of comparisons: %lu\n", compare_count);
    cmp_cnt_rest();
    printf("\n");

    free(array_quick);
    free(array_heap);
    free(array_insert);
    int n = 10;
    int k = 3;
    int *array_radix = (int*)malloc(sizeof(int) * n);
    array_radix[0] = 967; 
    array_radix[1] = 365;
    array_radix[2] = 234;
    array_radix[3] = 100;
    array_radix[4] = 588;
    array_radix[5] = 152;
    array_radix[6] = 374;
    array_radix[7] = 207;
    array_radix[8] = 985;
    array_radix[9] = 597;

    radix_sort(array_radix, n, k);
    printf("radix_sort result\n");
    display(array_radix,n);


} else {
    int numdata;
    for (numdata = 1000; numdata <= 10000; numdata += 1000) {  // numdata is 1000, 2000, ..., 10,000
      int *array_heap = (int*)malloc(sizeof(int) * numdata);
      int *array_quick = (int*)malloc(sizeof(int) * numdata);
      int i, number;
      for (i = 0; i < numdata; i++) {
        number = GetRandom(0, (numdata * 10 -1));
        array_heap[i] = number;  // random number from 0 to numdata * 10 - 1
        array_quick[i] = number;
      }
    heap_sort(array_heap, numdata);
    printf("heap_sort:\n");
    printf("%d %lu\n", numdata, compare_count);
    cmp_cnt_rest();
    q_sort(array_quick, numdata);
    printf("quick_sort: \n");
    printf("%d %lu\n", numdata, compare_count);
    cmp_cnt_rest();

    free(array_heap);
    free(array_quick);
    }

    double start_time, end_time;
    for (numdata=1000000; numdata<=10000000; numdata=numdata+1000000){
      int *array_heap = (int*)malloc(sizeof(int) * numdata);
      int *array_quick = (int*)malloc(sizeof(int) * numdata);
      int i,number;
      for (i = 0; i < numdata; i++) {
              number = GetRandom(0, (numdata * 10 -1));
              array_heap[i] = number;  // random number from 0 to numdata * 10 - 1
              array_quick[i] = number;
            }
      start_time = get_realtime();
      heap_sort(array_heap, numdata);
      end_time = get_realtime();
      printf("numdata = %d\n",numdata);
      printf("実行時間_heap_sort: %g s\n",end_time-start_time);

      start_time = get_realtime();
      q_sort(array_quick, numdata);
      end_time = get_realtime();
      printf("実行時間_quick_sort: %g s\n",end_time-start_time);
      free(array_heap);
      free(array_quick);
    }
  printf("基本課題2.3:\n");
    for (numdata=10000; numdata<=100000; numdata=numdata+10000){
        int *array_quick = (int*)malloc(sizeof(int) * numdata);
        int i,number;
        for (i = 0; i < numdata; i++) {
                number =  (numdata-i)*100;
                array_quick[i] = number;
              }
        printf("numdata = %d\n",numdata);
        start_time = get_realtime();
        q_sort(array_quick, numdata);
        end_time = get_realtime();
        printf("実行時間_quick_sort: %g s\n",end_time-start_time);
        free(array_quick);
      }
    
    
    
    
    
    
  }
 
  return EXIT_SUCCESS;
}