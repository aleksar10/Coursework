import java.util.Scanner;

class Person { 
    public int priority;
    public String name;
    public String surname;
}

class Node { 
    public Person info; 
    public Node left;
    public Node right;
    Node(Person p) {
        info = p;
        left = right = null;
    }
}

public class Source {
    public static Scanner sc = new Scanner(System.in);
    private static Node priQueue = null; 
    private static int createIndex; 

    private static void handleCreate() {
        String order = sc.next();
        int n = sc.nextInt();
        Person[] insertionArray = new Person[n];

        for (int i = 0; i < n; i++) { 
            Person person = new Person();
            person.priority = sc.nextInt();
            person.name = sc.next();
            person.surname = sc.next();
            insertionArray[i] = person;
        }
        if (order.equals("POSTORDER")) { 
            createIndex = n - 1; 
            priQueue = createTreePost(insertionArray, Integer.MIN_VALUE, Integer.MAX_VALUE); 
        }
        else if (order.equals("PREORDER")) { 
            createIndex = 0; 
            priQueue = createTreePre(insertionArray, Integer.MIN_VALUE, Integer.MAX_VALUE);
        }
    }
    private static Node createTreePost(Person[] array, int min, int max) { 
        if (createIndex < 0) 
            return null;
        Node currentRoot = null;

        if ((array[createIndex].priority > min) && (array[createIndex].priority < max)) {
            currentRoot = new Node(array[createIndex]);
            createIndex--;

            if (createIndex >= 0) { 
                currentRoot.right = createTreePost(array, array[createIndex + 1].priority, max); 
                currentRoot.left = createTreePost(array, min, array[createIndex + 1].priority);
            }
        }
        return currentRoot;
    }
    private static Node createTreePre(Person[] array, int min, int max) {
        if (createIndex >= array.length)
            return null;
        Node currentRoot = null;

        if ((array[createIndex].priority > min) && (array[createIndex].priority < max)) {
            currentRoot = new Node(array[createIndex]);
            createIndex++;

            if (createIndex < array.length)
                currentRoot.left = createTreePre(array, min, array[createIndex - 1].priority);
            if (createIndex < array.length)
                currentRoot.right = createTreePre(array, array[createIndex - 1].priority, max);
        }
        return currentRoot;
    }
    private static void handleDelete() {
        int delPriority = sc.nextInt();
        Node[] result = searchTree(delPriority);

        if (result[0] == null) {
            System.out.println("DELETE " + delPriority + ": BRAK");
            return;
        }
        else 
            deleteNode(result);
    }

    private static void deleteNode(Node[] input) {
        Node currentNode = input[0];
        Node prevNode = input[1];

        if (currentNode == null)
            return;

        if ((currentNode.left == null) || (currentNode.right == null)) {
            Node newCurrent;
            if (currentNode.left == null)
                newCurrent = currentNode.right;
            else
                newCurrent = currentNode.left;
            if (prevNode == null) {
                priQueue = newCurrent; 
                return;
            }
            if (currentNode == prevNode.left)
                prevNode.left = newCurrent;
            else
                prevNode.right = newCurrent;
        }
        else {
            Node p = null;
            Node temp;

            temp = currentNode.right;
            while (temp.left != null) { 
                p = temp;
                temp = temp.left;
            }

            if (p != null) 
                p.left = temp.right;
            else 
                currentNode.right = temp.right;
            currentNode.info = temp.info;
        }
    }
    private static void handleEnque() { 
        Person newPerson = new Person();

        newPerson.priority = sc.nextInt();
        newPerson.name = sc.next();
        newPerson.surname = sc.next();
        insertPerson(newPerson);
    }
    private static void handlePreorder() { 
        MyStack stack = new MyStack(100);
        Node currentNode;
        StringBuilder sb = new StringBuilder();

        sb.append("PREORDER: ");
        if (priQueue == null) {
            sb.append("\n");
            System.out.print(sb.toString());
            return;
        }
        stack.push(priQueue);
        while (stack.isEmpty() != true) {
            currentNode = stack.pop();
            sb.append(currentNode.info.priority + " - " + currentNode.info.name + " " + currentNode.info.surname + ", ");
            if (currentNode.right != null) 
                stack.push(currentNode.right);  
            if (currentNode.left != null)
                stack.push(currentNode.left);
        }
        sb.delete(sb.length() - 2, sb.length());
        sb.append("\n");
        System.out.print(sb.toString());
    }
    private static void handleInorder() {
        MyStack stack = new MyStack(100);
        StringBuilder sb = new StringBuilder();

        sb.append("INORDER: ");
        if (priQueue == null) {
            sb.append("\n");
            System.out.print(sb.toString());
            return;
        }
        Node currentNode = priQueue;
        while (currentNode != null || stack.isEmpty() != true) {
            if (currentNode != null) {
                stack.push(currentNode);
                currentNode = currentNode.left; 
            }
            else {
                currentNode = stack.pop();
                sb.append(currentNode.info.priority + " - " + currentNode.info.name + " " + currentNode.info.surname + ", ");
                currentNode = currentNode.right;
            }
        }
        sb.delete(sb.length() - 2, sb.length());
        sb.append("\n");
        System.out.print(sb.toString());
    }
    private static void handlePostorder() {
        MyStack stack1 = new MyStack(50);
        MyStack stack2 = new MyStack(50); 
        Node currentNode;
        StringBuilder sb = new StringBuilder();

        sb.append("POSTORDER: ");
        if (priQueue == null) {
            sb.append("\n");
            System.out.print(sb.toString());
            return;
        }
        stack1.push(priQueue);
        while (stack1.isEmpty() != true) {
            currentNode = stack1.pop();
            stack2.push(currentNode);

            if (currentNode.left != null)
                stack1.push(currentNode.left);
            if (currentNode.right != null)
                stack1.push(currentNode.right);
        }
        while (stack2.isEmpty() != true) {
            currentNode = stack2.pop();
            sb.append(currentNode.info.priority + " - " + currentNode.info.name + " " + currentNode.info.surname + ", ");
        }
        sb.delete(sb.length() - 2, sb.length());
        sb.append("\n");
        System.out.print(sb.toString());
    }
    private static void insertPerson(Person person) {
        Node newNode = new Node(person);

        if (priQueue == null) {
            priQueue = newNode;
            return;
        }
        Node prevNode = null;
        Node currentNode = priQueue;
        while (currentNode != null) {
            if (currentNode.info.priority > person.priority) {
                prevNode = currentNode;
                currentNode = currentNode.left;
            }
            else if (currentNode.info.priority <= person.priority) {
                prevNode = currentNode;
                currentNode = currentNode.right;
            }
        }
        if (prevNode.info.priority > person.priority)
            prevNode.left = newNode;
        else
            prevNode.right = newNode;
    }
    private static Node[] searchTree(int priority) {
        Node currentNode = priQueue;
        Node prevNode = null;
        Node[] result = { null, null };

        while (currentNode != null) {
            if (priority > currentNode.info.priority) {
                prevNode = currentNode;
                currentNode = currentNode.right;
            }
            else if (priority < currentNode.info.priority) {
                currentNode = currentNode.left;
            }
            else {
                result[0] = currentNode;
                result[1] = prevNode;
                break;
            }
        }
        return result;
    }
    private static Node[] searchMinMax(boolean searchMin) {
        Node currentNode = priQueue;
        Node prevNode = null, nextNode = null;
        Node[] result = { null, null };

        while (currentNode != null) {
            if (searchMin == true)
                nextNode = currentNode.left;
            else
                nextNode = currentNode.right;
            if (nextNode != null) {
                prevNode = currentNode;
                currentNode = nextNode;
            }
            else
                break;
        }

        result[0] = currentNode;
        result[1] = prevNode;
        return result;
    }
    private static void handleDeque(boolean deQueueMin) {
        Node[] result = searchMinMax(deQueueMin);
        System.out.print("DEQUE" + ((deQueueMin == true) ? "MIN: " : "MAX: "));
        if (result[0] != null)
            System.out.print(result[0].info.priority + " - " + result[0].info.name + " " + result[0].info.surname + "\n");
        else
            System.out.print("BRAK");
        deleteNode(result);
    }
    private static void handleNext() {
        Node result = null;
        Node currentNode = priQueue;
        boolean bFound = false;
        int priority = sc.nextInt();

        System.out.print("NEXT " + priority + ": ");
        while (currentNode != null) {
            if (currentNode.info.priority == priority) {
                bFound = true;
                if (currentNode.right != null) {
                    result = currentNode.right;
                    while (result.left != null)
                        result = result.left;
                }
                break;
            }
            else if (currentNode.info.priority < priority) 
                currentNode = currentNode.right; 
            else { 
                result = currentNode;
                currentNode = currentNode.left;
            }
        }
        if ((result == null) || (bFound == false))
            System.out.print("BRAK\n");
        else
            System.out.print(result.info.priority + " - " + result.info.name + " " + result.info.surname + "\n");
    }
    private static void handlePrev() {
        Node result = null;
        Node currentNode = priQueue;
        boolean bFound = false;
        int priority = sc.nextInt();

        System.out.print("PREV " + priority + ": ");
        while (currentNode != null) {
            if (currentNode.info.priority == priority) { 
                bFound = true;
                if (currentNode.left != null) {
                    result = currentNode.left; 
                    while (result.right != null) 
                        result = result.right;
                }
                break;
            }
            else if (currentNode.info.priority < priority) {
                result = currentNode; 
                currentNode = currentNode.right;
            }
            else
                currentNode = currentNode.left; 
        }
        if ((result == null) || (bFound == false))
            System.out.print("BRAK\n");
        else
            System.out.print(result.info.priority + " - " + result.info.name + " " + result.info.surname + "\n");
    }
    private static int calculateHeight(Node treeNode) {
        if (treeNode == null)
            return -1;
        int heightLeft = calculateHeight(treeNode.left);
        int heightRight = calculateHeight(treeNode.right);

        return 1 + Math.max(heightLeft, heightRight);
    }
    private static void handleHeight() {
        System.out.println("HEIGHT: " + calculateHeight(priQueue));
    }
    public static void main(String[] args) {
        String command;
        int z = sc.nextInt();

        for (int i = 0; i < z; i++)  {
            priQueue = null;
            int k = sc.nextInt();
            System.out.println("ZESTAW " + (i + 1));
            for (int j = 0; j < k; j++) {
                command = sc.next();
                switch (command) {
                    case "CREATE":
                        handleCreate();
                        break;
                    case "DELETE":
                        handleDelete();
                        break;
                    case "ENQUE":
                        handleEnque();
                        break;
                    case "DEQUEMAX":
                        handleDeque(false);
                        break;
                    case "DEQUEMIN":
                        handleDeque(true);
                        break;
                    case "NEXT":
                        handleNext();
                        break;
                    case "PREV":
                        handlePrev();
                        break;
                    case "PREORDER":
                        handlePreorder();
                        break;
                    case "INORDER":
                        handleInorder();
                        break;
                    case "POSTORDER":
                        handlePostorder();
                        break;
                    case "HEIGHT":
                        handleHeight();
                        break;
                    default:
                        break;
                }
            }
        }
        sc.close();
    }
}

class MyStack {
    
    private Node[] stack;
    private int top;
    private int maxSize;

    public MyStack(int n) {
        stack = new Node[n];
        top = -1;
        maxSize = n;
    }
    public void push(Node x) {
        if (++top >= maxSize) {
            Node[] newStack = new Node[maxSize * 2];
            System.arraycopy(stack, 0, newStack, 0, maxSize);
            maxSize *= 2;
            stack = newStack;
        }
        stack[top] = x;
    }
    public Node pop() {
        if(top < 0)
            return null;
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