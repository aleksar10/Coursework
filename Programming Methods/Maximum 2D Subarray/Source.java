import java.util.Scanner;

class Source {

    public static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int data_am; 
        int rows, columns, set_num;
        char chr;

        data_am = scanner.nextInt();

        while(data_am > 0)
        {
            set_num = scanner.nextInt();
            chr = scanner.next().charAt(0);
            rows = scanner.nextInt();
            columns = scanner.nextInt();

            int[][] tab = new int[rows][columns];
            int[] arr_tmp = new int[columns];

            int MAX = -1;
            int i, j, k;
            int row_beg = 0, col_beg = 0, row_end = 0, col_end = 0;
            boolean all_neg = true;
            boolean change;
            int beg, beg2, end, max_loc, sum;

            for(i = 0; i < rows; i++)
            {
                for(j = 0; j < columns; j++)
                    tab[i][j] = scanner.nextInt();
            }

            for(i = 0; i < rows; i++)
            {
                for(j = i; j < rows; j++)
                {
                    for(k = 0; k < columns; k++)                         
                    {                            
                        if(j == i) 
                        {
                            if(tab[j][k] >= 0)
                            {
                                arr_tmp[k] = 3*tab[j][k];
                                all_neg = false;
                            }
                            else
                                arr_tmp[k] = 2*tab[j][k];
                        }
                        else
                        {
                            if(tab[j][k] >= 0)
                                arr_tmp[k] += 3*tab[j][k];
                            else
                                arr_tmp[k] += 2*tab[j][k];
                        }
                    }

                    beg = beg2 = end = sum = 0;
                    max_loc = -1;
                    change = false;
 
                    for(k = 0; k < columns; k++)
                    {
                        sum += arr_tmp[k];
                        if (sum > max_loc)
                        {
                            if ((sum > 0) && (max_loc == 0)) 
                                beg2 = k;                    

                            max_loc = sum;
                            beg = beg2;
                            end = k;
                        }
                        if (sum < 0)
                        {
                            sum = 0;
                            beg2 = k + 1;
                        }
                    } 

                    if(max_loc > MAX)
                        change = true;
                    else if (max_loc == MAX)
                    {
                        if(((j - i + 1)*(end - beg + 1)) < ((row_end - row_beg + 1)*(col_end - col_beg + 1)))  
                            change = true;
                    }

                    if(change == true) 
                    {
                        MAX = max_loc;
                        row_beg = i;
                        row_end = j;
                        col_beg = beg;
                        col_end = end;
                    }
                }
            }

            if(all_neg == true)
                System.out.print(set_num + ": ms_tab is empty\n");
            else
                System.out.print(set_num + ": ms_tab = a[" + row_beg + ".." + row_end + "][" + col_beg + ".." + col_end + "], msum=" + MAX +"\n");
            
            data_am--;
        }
    }
} 
