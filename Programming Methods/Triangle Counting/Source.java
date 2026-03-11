 import java.util.Scanner;

 class Source {
 
     public static Scanner scanner = new Scanner(System.in);
 
     public static void main(String[] args) {
 
         int data_am;
         int set_num = 0;
         int n;
         data_am = scanner.nextInt();
 
        while (data_am > 0)
        {
             set_num++;
             n = scanner.nextInt();
             Table T = new Table(n);
 
             for (int i = 0; i < n; i++)
                 T.tab[i] = scanner.nextInt();
 
             scanner.nextLine();
 
             T.sort();
             System.out.print(set_num + ": n= " + n);

             for(int i = 0; i < n; i++)
             {
                 if((i % 25) == 0)
                     System.out.print("\n");
 
                 System.out.print(T.tab[i] + " ");
             }
                 
             System.out.print("\n");

             
             int triangles = 0;
             int count = 0;
             int idx;
             int i, j, m;
 
             for (i = 0; i < n - 2; i++) 
             {
                for(j = i + 1; j < n - 1; j++)
                {
                    T.low = i + 2;
                    T.upp = n - 1;

                    idx = T.SearchBinFirst(T.tab[i] + T.tab[j]);
                    
                    triangles += idx - j - 1;

                    for(m = j + 1; (m < idx) && (count < 10); m++)
                    {
                        System.out.print("(" + i + "," + j + "," + m + ") ");
                        count++;
                    }
                } 
            }

            if(triangles != 0)
                System.out.print("\n");

            System.out.print("Total number of triangles is: " + triangles + "\n");
            
            data_am--;  
        }     
    }
} 
 
 class Table {
 
     public int[] tab;
     public int length;

     public int low;
     public int upp;
 
     public Table(int l){
         tab = new int[l];
         length = l;
     }

     
     public int SearchBinFirst(int x)
     {
        int curr;

        while (low <= upp)
        {
            curr = (low + upp)/2;
                        
            if(tab[curr] < x)
                low = curr + 1;
            else if(tab[curr] >= x)
                upp = curr - 1;
        }

        return low;
     }


     public void sort() {
 
         int i, j, tmp, idx_min;
 
         for(i = 0; i < length - 1; i++)
         {
             idx_min = i;
 
             for(j = i + 1; j < length; j++)
             {
                 if(tab[j] < tab[idx_min])
                     idx_min = j;
             }
 
             tmp = tab[i];
             tab[i] = tab[idx_min];
             tab[idx_min] = tmp;
         }
     }
 }
   
