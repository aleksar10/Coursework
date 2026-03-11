import java.util.Scanner;

public class Source {
    public static Scanner sc = new Scanner(System.in);

    private static void InsertionSort(int[] array, int left, int right) {
        int tmp, i, j;

        for (i = left + 1; i <= right; i++) {
            tmp = array[i];
            j = i - 1;
            while ((j >= left) && (tmp < array[j])) {
                array[j + 1] = array[j];
                j--;
            }
            array[j+1] = tmp;
        }
    }

    private static int partition5(int[] array, int left, int right) {
        InsertionSort(array, left, right);
        return (left + right) / 2;
    }

    private static void swap(int[] array, int i, int j) {
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }

    private static int partition(int[] array, int left, int right, int pivotIndex) {
        int pivotValue = array[pivotIndex];
        swap(array, pivotIndex, right);

        int storeIndex = left;
        for (int i = left; i < right; i++) {
            if (array[i] < pivotValue) {
                swap(array, storeIndex, i);
                storeIndex++;
            }
        }
        swap(array, right, storeIndex);
        return storeIndex;
    }

    private static int getPivotIndex(int[] array, int left, int right) {
        for (int i = left; i <= right; i += 5) {
            int subRight = i + 4;
            if (subRight > right) {
                subRight = right;
            }
            int median5 = partition5(array, i, subRight);
            swap(array, median5, left + (i - left) / 5);
        }
        int mid = 1 + (right - left) / 10;
        return Select2(array, left, left + (right - left) / 5, mid);
    }

    private static int Select2(int[] array, int left, int right, int element) {

        if ((right - left + 1) < 40) {
            InsertionSort(array, left, right);
            return left + element - 1;
        }

        int pivotIndex = getPivotIndex(array, left, right);
        pivotIndex = partition(array, left, right, pivotIndex);

        if (element <= (pivotIndex - left))
            return Select2(array, left, pivotIndex - 1, element); 
        else if (element == (pivotIndex - left + 1))
            return pivotIndex;
        else
            return Select2(array, pivotIndex + 1, right, element - (pivotIndex - left + 1)); 
    }

    public static void main(String[] args) {
        int j;
        int z = sc.nextInt();

        for (int i = 0; i < z; i++)  {
            int n = sc.nextInt();
            int[] array = new int[n];
            for (j = 0; j < n; j++) {
                array[j] = sc.nextInt();
            }
            int m = sc.nextInt();
            int[] tofind = new int[m];
            for (j = 0; j < m; j++) {
                tofind[j] = sc.nextInt();
            }
            for (j = 0; j < m; j++) {
                System.out.print(tofind[j] + " ");
                if ((tofind[j] > array.length) || (tofind[j] < 1))
                    System.out.print("brak");
                else
                    System.out.print(array[Select2(array, 0, array.length - 1, tofind[j])]);
                System.out.print("\n");
            }
        }
    }
}