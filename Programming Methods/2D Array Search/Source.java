import java.util.Scanner;

public class Source {
    public static Scanner scanner = new Scanner(System.in);

    static void searchRow(int[][] arr, int row_idx, int beg, int end, 
                          boolean bFirst, int number, int[] result) { 
        if (beg > end)
            return;

        int mid = beg + (end - beg) / 2;        
        int val = arr[row_idx][mid];

        if (val == number) {
            result[0] = row_idx;
            result[1] = mid;
            if (bFirst)
                end = mid - 1;
            else 
                beg = mid + 1;
        } else if (val < number) {
            beg = mid + 1;
        }
        else {
            end = mid - 1;
        }
        searchRow(arr, row_idx, beg, end, bFirst, number, result);
    }

    static void recFirst(int[][] arr, int currRow, int number, int[] result) {
        if (currRow == arr.length)
            return;

        searchRow(arr, currRow, 0, arr[currRow].length - 1, true, number, result);

        if ((result[0] != -1) && (result[1]) != -1)
            return;

        recFirst(arr, currRow + 1, number, result);
    }

    static void recLast(int[][] arr, int currRow, int number, int[] result) {
        if (currRow < 0)
            return;

        searchRow(arr, currRow, 0, arr[currRow].length - 1, false, number, result);

        if ((result[0] != -1) && (result[1] != -1))
            return;

        recLast(arr, currRow - 1, number, result);
    }

    static void iterFirst(int[][] arr, int number) {
        int[] result = { -1, -1 };
        int rows = arr.length;
        int cols = arr[0].length;
        int beg, end, mid;

        for (int i = 0; i < rows; i++) {
            beg = 0;
            end = cols - 1;

            while (beg <= end) {
                mid = beg + (end - beg) / 2;             
                int val = arr[i][mid];
                if (val == number) {
                    result[0] = i;
                    result[1] = mid;
                    end = mid - 1;
                } else if (val < number) {
                    beg = mid + 1;
                }
                else {
                    end = mid - 1;
                }
            }
            if ((result[0] != -1) && (result[1] != -1))
                break;
        }
        System.out.print("iterFirst: " + number + " ");
        if ((result[0] == -1) || (result[1] == -1)) {
            System.out.println("missing in array");
        } else {
            System.out.println("= a[" + result[0] + "][" + result[1] + "]");
        }
    }

    static void iterLast(int[][] arr, int number) {
        int[] result = { -1, -1 };
        int rows = arr.length;
        int cols = arr[0].length;
        int beg, end, mid;

        for (int i = rows - 1; i >= 0; i--) {
            beg = 0; 
            end = cols - 1;
            while (beg <= end) {
                mid = beg + (end - beg) / 2;             
                int val = arr[i][mid];
                if (val == number) {
                    result[0] = i;
                    result[1] = mid;
                    beg = mid + 1;
                } else if (val < number) {
                    beg = mid + 1;
                }
                else {
                    end = mid - 1;
                }
            }
            if ((result[0] != -1) && (result[1] != -1))
                break;
        }
        System.out.print("iterLast: " + number + " ");
        if ((result[0] == -1) || (result[1] == -1)) {
            System.out.println("missing in array");
        } else {
            System.out.println("= a[" + result[0] + "][" + result[1] + "]");
        }
    }
    public static void main(String[] args) {
        int[] result = { -1, -1 };
        int z = scanner.nextInt();

        scanner.nextLine();
        for (int i = 0; i < z; i++)  {

            int n = scanner.nextInt();
            int m = scanner.nextInt();
            scanner.nextLine();

            if ((n < 0) || (m < 0)){
                continue;
            }
            int[][] myArray = new int[n][m];

            for (int j = 0; j < n; j++) {
                for (int k = 0; k < m; k++) {
                    myArray[j][k] = scanner.nextInt();
                }
                scanner.nextLine();
            }

            int number = scanner.nextInt();
            scanner.nextLine();

            result[0] = -1;
            result[1] = -1;

            recFirst(myArray, 0, number, result);

            System.out.print("recFirst: " + number + " ");
            if ((result[0] == -1) || (result[1] == -1)) {
                System.out.println("missing in array");
            } else {
                System.out.println("= a[" + result[0] + "][" + result[1] + "]");
            }

            result[0] = -1;
            result[1] = -1;

            recLast(myArray, n - 1, number, result);

            System.out.print("recLast: " + number + " ");
            if ((result[0] == -1) || (result[1] == -1)) {
                System.out.println("missing in array");
            } else {
                System.out.println("= a[" + result[0] + "][" + result[1] + "]");
            }

            iterFirst(myArray, number);
            iterLast(myArray, number);
            System.out.println("---");
        }
        scanner.close();
    }
}
