 import java.util.Scanner;

 class HeapElement {
     int value;
     int xIndex;
     int yIndex;
 }
 
 public class Source {
     public static Scanner sc = new Scanner(System.in);
 
     private static void upHeap(HeapElement[] heap, int k) {
         int prev = (k - 1) / 2; 
         HeapElement tmp = heap[k];
         while ((k > 0) && (heap[prev].value > tmp.value)) {
             heap[k] = heap[prev]; 
             k = prev;
             prev = (prev - 1) / 2;
         }
         heap[k] = tmp;
     }
     private static void downHeap(HeapElement[] heap) {
         int j, k = 0;
         int n = heap.length;
         HeapElement tmp = heap[0];
         while (k < (n / 2)) {
             j = 2*k + 1;
             if ((j < (n - 1)) && (heap[j].value > heap[j + 1].value))
                 j++;
             if (tmp.value <= heap[j].value)
                 break;
             heap[k] = heap[j];
             k = j;
         }
         heap[k] = tmp;
     }
     private static int deleteMin(HeapElement[] heap, int[][] array2D, int[] seqLengths) {
         int result = heap[0].value;
         if ((heap[0].yIndex + 1) < seqLengths[heap[0].xIndex]) {
             heap[0].value = array2D[heap[0].xIndex][heap[0].yIndex + 1];
             heap[0].yIndex++;
         }
         else { 
             heap[0].value = Integer.MAX_VALUE;
             heap[0].xIndex = -1;
             heap[0].yIndex = -1;
         }
         downHeap(heap);
 
         return result;
     }
 
     public static void main(String[] args) {
         int i, j, k;
         int z = sc.nextInt();
 
         for (i = 0; i < z; i++)  {
             int maxLength = 0;
             int n = sc.nextInt(); 
             int[] seqLengths = new int[n];
             for (j = 0; j < n; j++) {
                 seqLengths[j] = sc.nextInt();
                 if (seqLengths[j] > maxLength) 
                 maxLength = seqLengths[j];
             }
             int[][] array2D = new int[n][maxLength];
             for (j = 0; j < n; j++) {
                 for (k = 0; k < seqLengths[j]; k++) {
                     array2D[j][k] = sc.nextInt();  
                 }
             }
             HeapElement[] heap = new HeapElement[n];
             for (j = 0; j < n; j++) {
                 HeapElement elem = new HeapElement();
                 elem.xIndex = j;
                 elem.yIndex = 0;
                 elem.value = array2D[j][0];
                 heap[j] = elem;
                 upHeap(heap, j);
             }
             while (heap[0].xIndex != -1)
                 System.out.print(deleteMin(heap, array2D, seqLengths) + " ");

             System.out.print("\n");
         }
         sc.close();
     }
 }