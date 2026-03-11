import java.util.Scanner;

public class Source {
    public static Scanner sc = new Scanner(System.in);
    private static boolean recFound;

    static Stack_int recPackage(int capacity, int[] elements) {
        Stack_int result = new Stack_int(elements.length);
        Source.recFound = false;

        fillPackage(capacity, elements, 0, result);

        return result;
    }

    static private void fillPackage(int remCapacity, int[] items, int currItem, Stack_int currSelection) {

        if ((remCapacity == 0) || (currItem >= items.length) || (Source.recFound == true)) {
            if (remCapacity == 0) {
                Source.recFound = true;
            }
            return;
        }

        if (items[currItem] <= remCapacity) {
            currSelection.push(items[currItem]);

            fillPackage(remCapacity - items[currItem], items, currItem + 1, currSelection);
            if (Source.recFound == true)
                return;
            currSelection.pop();
        }

        fillPackage(remCapacity, items, currItem + 1, currSelection);
    }

    static Stack_int StackSimPackage(int capacity, int[] elements) {
        Stack_int currSelection = new Stack_int(elements.length);
        Stack_int stack_cap = new Stack_int(100);
        Stack_int stack_idx = new Stack_int(100);
        int remCapacity, currItem;

        stack_cap.push(capacity);
        stack_idx.push(0);

        while (!stack_cap.isEmpty()) {
            remCapacity = stack_cap.pop();
            currItem = stack_idx.pop();

            if (remCapacity == 0) {
                break;
            }
            if (currItem >= elements.length) {
                currSelection.pop();
                continue;
            }

            if (elements[currItem] <= remCapacity) {
                stack_cap.push(remCapacity);
                stack_idx.push(currItem + 1);
                currSelection.push(elements[currItem]);

                stack_cap.push(remCapacity - elements[currItem]);
                stack_idx.push(currItem + 1);
                continue;
            }
            else {
                stack_cap.push(remCapacity);
                stack_idx.push(currItem + 1);
                continue;
            }
        }
        return currSelection;
    }

    private static void printStack(Stack_int stack) {
        int element = stack.pop();

        if (element == -1)
            return;
        else {
            printStack(stack);
            System.out.print(" " + element);
        }
    }

    public static void main(String[] args) {
        Stack_int resultRec, resultSim;
        int z = sc.nextInt();

        sc.nextLine();
        for (int i = 0; i < z; i++)  {
            int n = sc.nextInt();
            sc.nextLine();
            int k = sc.nextInt();
            sc.nextLine();
            int[] elemArray = new int[k];
            for (int j = 0; j < k; j++) {
                elemArray[j] = sc.nextInt();
            }
            sc.nextLine();
            resultRec = recPackage(n, elemArray);

            if (resultRec.isEmpty())
                System.out.println("BRAK");
            else {
                resultSim = StackSimPackage(n, elemArray);
                System.out.print("REC:  " + n + " =");
                
                if (!resultRec.isEmpty()) {
                    printStack(resultRec);
                }
                System.out.print("\n");

                System.out.print("ITER: " + n + " =");
                while (!resultSim.isEmpty()) {
                    printStack(resultSim);
                }
                System.out.print("\n");
            }
        }
        sc.close();
    }
}

class Stack_int { 
    
    private int[] stack; 
    private int top;
    private int maxSize;

    public Stack_int(int n) {
        stack = new int[n];
        top = -1;
        maxSize = n;
    }
    public void push(int x) {
        if (++top >= maxSize) {
            int[] newStack = new int[maxSize * 2];
            System.arraycopy(stack, 0, newStack, 0, maxSize);
            maxSize *= 2;
            stack = newStack;
        }
        stack[top] = x;
    }
    public int pop() {
        if(top < 0)
            return -1;
        else
            return stack[top--];
    }
    public boolean isEmpty() {
        if(top == -1)
            return true;
        else
            return false;
    }
}