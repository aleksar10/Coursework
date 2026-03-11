import java.util.Scanner;

public class Source {
    private static Scanner sc = new Scanner(System.in);
    private static long[] array;

    private static short FindMedianIndex(short left, short right) {
        short mid = (short)(left + ((right - left) / 2));

        if ((array[left] <= array[mid] && array[mid] <= array[right]) ||
            (array[right] <= array[mid] && array[mid] <= array[left])) {
            return mid;
        } else if ((array[mid] <= array[left] && array[left] <= array[right]) ||
                   (array[right] <= array[left] && array[left] <= array[mid])) {
            return left;
        } else {
            return right;
        }
    }

    private static void swap(short i, short j) {
        long tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    private static short Partition(short left, short right) {
        short i = (short)(left - 1), j = right;
        short pivot_idx = FindMedianIndex(left, right);
        swap(pivot_idx, right);

        while(true) {
            while (array[++i] < array[right]);
            while (j > left && array[--j] > array[right]);
            if (i >= j)
                break;
            else
                swap(i, j);
        }
        swap(i, right);

        return i;
    }

    private static short FindBiggest(short left, short right) { 
        short biggest_idx = 0;

        for (short i = left; i <= right; i++) {
            if (array[i] > array[biggest_idx])
                biggest_idx = i;
        }
        return biggest_idx;
    }

    private static void InsertionSort(short left, short right) {
        long tmp;
        short i, j;

        for (i = (short)(left + 1); i <= right; i++) {
            tmp = array[i];
            j = (short)(i - 1);

            while ((j >= 0) && (tmp < array[j])) {
                array[j + 1] = array[j];
                j--;
            }
            array[j+1] = tmp;
        }
    }

    private static void EffectiveQSort() {
        long tmp;
        short pivot_idx = -1, left, right, biggestLeft_idx; 
        right = -2; 
        do {
            left = (short)(right + 2); 
            pivot_idx = (short)(left - 1); 
            right = left;
            
            if (pivot_idx == -1) 
                right = (short)(array.length - 1);
            else {
                while (array[right] >= array[pivot_idx - 1])
                    right++;
    
                tmp = array[right];
                array[right] = array[pivot_idx];
                array[pivot_idx] = array[pivot_idx - 1];
                array[pivot_idx - 1] = tmp;
            }

            while ((right - left) >= 20) { 
                pivot_idx = Partition(left, right); 
                biggestLeft_idx = FindBiggest(left, (short)(pivot_idx - 1)); 
                                                         
                tmp = array[biggestLeft_idx];
                array[biggestLeft_idx] = array[pivot_idx - 1];
                array[pivot_idx - 1] = array[pivot_idx];
                array[pivot_idx] = array[right];
                array[right] = tmp;
                right = (short)(pivot_idx - 1);  
            }
            InsertionSort(left, right);
        } while (right < (array.length - 1));
    }

    public static void main(String[] args) {
        int j;
        int z = sc.nextInt();
        sc.nextLine();

        for (int i = 0; i < z; i++)  {
            short n = sc.nextShort();
            sc.nextLine();
            array = new long[n];
            for (j = 0; j < n; j++) {
                array[j] = sc.nextLong();
            }
            EffectiveQSort();
            for (j = 0; j < n; j++) {
                System.out.print(array[j] + " ");
            }
            System.out.print("\n");
        }
    }
}