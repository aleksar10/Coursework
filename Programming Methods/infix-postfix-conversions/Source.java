import java.util.Scanner;

class Source {

    public static Scanner scanner = new Scanner(System.in);

    public static int Priorities(char x)
    {
         if((x == '!') || (x == '~'))
            return 8;
        else if(x == '^')
            return 7;
        else if((x == '*') || (x == '/') || (x == '%'))
            return 6;
        else if((x == '+') || (x == '-'))
            return 5;
        else if((x == '>') || (x == '<'))
            return 4;
        else if(x == '&')
            return 3;
        else if(x == '|')
            return 2;
        else if(x == '=')
            return 1;

        return 0;
    }

    public static Boolean is_complex(String expr){

        int operands = 0; 
        for(int i = 0; i < expr.length(); i++){

            if((((int)expr.charAt(i) >= 97) && ((int)expr.charAt(i) <= 122))){
                operands++;
            }

            if(operands > 1)
                return true;
        }
        return false;
    }

    public static void main(String[] args) {

        int data_am;
        data_am = scanner.nextInt();
        String given_line;
        scanner.nextLine();

        while(data_am > 0)
        {
            given_line = scanner.nextLine();

            if(given_line.charAt(0) == 'I')
            {
                char[] expression = new char[257];
                int exp_idx = 0;
                char[] result = new char[257];
                int result_idx = 0;

                for(int i = 5; i < given_line.length() ; i++)
                {
                    if((((int)given_line.charAt(i) >= 97) && ((int)given_line.charAt(i) <= 122)) || (given_line.charAt(i) == '~') || (given_line.charAt(i) == '!') 
                    || (given_line.charAt(i) == '(') || (given_line.charAt(i) == '^') || (given_line.charAt(i) == '*') || (given_line.charAt(i) == '/') || (given_line.charAt(i) == '%') ||
                    (given_line.charAt(i) == '+') || (given_line.charAt(i) == '-') || (given_line.charAt(i) == '<') || (given_line.charAt(i) == '>') ||
                    (given_line.charAt(i) == '=') || (given_line.charAt(i) == '&') || (given_line.charAt(i) == '|') || (given_line.charAt(i) == ')'))
                    {
                        expression[exp_idx] = given_line.charAt(i);
                        exp_idx++;
                    }
                }

                int q0 = 1, q1 = 0, q2 = 0;
    
                Boolean is_error = false;
                int bracket = 0;
                Stack_char new_stack = new Stack_char();
                int oper_check = 0;

                
                for(int i = 0; i < exp_idx; i++)
                {
                    if(q0 == 1)
                    {
                        if(((int)expression[i] >= 97) && ((int)expression[i] <= 122))
                        {
                            q0 = 0;
                            q1 = 1;
                            oper_check++;
                        }
                        else if((expression[i] == '~') || (expression[i] == '!'))
                        {
                            q0 = 0;
                            q2 = 1;
                        }
                        else if((expression[i] == '('))
                        {
                            q0 = 1;
                            bracket++;
                        }
                        else
                            is_error = true;
                    }
                    else if(q1 == 1)
                    {
                        if((expression[i] == '^') || (expression[i] == '*') || (expression[i] == '/') || (expression[i] == '%') || 
                        (expression[i] == '+') || (expression[i] == '-') || (expression[i] == '<') || (expression[i] == '>') || 
                        (expression[i] == '=') || (expression[i] == '&') || (expression[i] == '|'))
                        {
                            q1 = 0;
                            q0 = 1;
                            oper_check--;
                        }
                        else if((expression[i] == ')'))
                        {
                            q2 = 1;
                            bracket--;
                        }
                        else
                            is_error = true;
                    }
                    else if(q2 == 1)
                    {
                        if((expression[i] == '~') || (expression[i] == '!'))
                        {
                            q2 = 1;
                        }
                        else if((expression[i] == '('))
                        {
                            q2 = 0;
                            q0 = 1;
                            bracket++;
                        }
                        else if(((int)expression[i] >= 97) && ((int)expression[i] <= 122))
                        {
                            q2 = 0;
                            q1 = 1;
                            oper_check++;
                        }
                        else
                            is_error = true;
                    }
    
                    if((is_error == true) || (bracket < 0) || (oper_check < 0))
                        break;
                    
                    if(((int)expression[i] >= 97) && ((int)expression[i] <= 122))
                    {
                        result[result_idx] = expression[i];
                        result_idx++;
                    }
                    else if(expression[i] == '(')
                    {
                        new_stack.push(('('));
                    }
                    else if(expression[i] == ')')
                    {
                        while(new_stack.isEmpty() == false) {
    
                            if(new_stack.peek()  != '(') {
                                result[result_idx] = new_stack.peek();
                                result_idx++;
                                new_stack.pop();
                            }
                            else {
                                new_stack.pop();
                                break;
                            }
                        }
                    }
                    else
                    {
                        if((expression[i] == '!') || (expression[i] == '~') || (expression[i] == '^') || (expression[i] == '='))
                        {
                            while((new_stack.isEmpty() == false))
                            {
                                if(Priorities(expression[i]) < Priorities(new_stack.peek()))
                                {
                                    result[result_idx] = new_stack.peek();
                                    result_idx++;
                                    new_stack.pop();
                                }
                                else
                                    break;
                            }
                        }
                        else
                        {
                            while((new_stack.isEmpty() == false))
                            {
                                if(Priorities(expression[i]) <= Priorities(new_stack.peek()))
                                {
                                    result[result_idx] = new_stack.peek();
                                    result_idx++;
                                    new_stack.pop();
                                }
                                else
                                    break;
                            }
                        }
                        new_stack.push(expression[i]);
                    }
                }
    
                while((new_stack.isEmpty() == false))
                {
                    result[result_idx] = new_stack.peek();
                    result_idx++;
                    new_stack.pop();
                }

                if((q1 != 1) || (bracket != 0) || (is_error == true) || (oper_check != 1)){
                    System.out.print("ONP: error\n");
                }
                else{
                    System.out.print("ONP: ");
                    for(int i = 0; i < result_idx; i++)
                        System.out.print(result[i] + " ");
                    System.out.print("\n");
                }

            }
            else
            {
                String[] expression = new String[257];
                int exp_idx = 0;
                char a;
                int oper_check = 0;

                for(int i = 5; i < given_line.length() ; i++)
                {
                    if((((int)given_line.charAt(i) >= 97) && ((int)given_line.charAt(i) <= 122)) || (given_line.charAt(i) == '~') || (given_line.charAt(i) == '!') 
                    || (given_line.charAt(i) == '^') || (given_line.charAt(i) == '*') || (given_line.charAt(i) == '/') || (given_line.charAt(i) == '%') ||
                    (given_line.charAt(i) == '+') || (given_line.charAt(i) == '-') || (given_line.charAt(i) == '<') || (given_line.charAt(i) == '>') ||
                    (given_line.charAt(i) == '=') || (given_line.charAt(i) == '&') || (given_line.charAt(i) == '|'))
                    {
                        a = given_line.charAt(i);
                        expression[exp_idx] = Character.toString(a);
                        exp_idx++;
                    }
                }

                Stack_string new_stack = new Stack_string();
                Stack_string brackets_stack = new Stack_string();
                String stack_elem_1, stack_elem_2;
                String operator_1, operator_2; 
                
                for(int i = 0; i < exp_idx; i++){
                
                    if ((!expression[i].equals("~")) && (!expression[i].equals("!")) && (!expression[i].equals("^")) && 
                    (!expression[i].equals("*")) && (!expression[i].equals("/")) && (!expression[i].equals("%")) && (!expression[i].equals("+")) && 
                    (!expression[i].equals("-")) && (!expression[i].equals("<")) && (!expression[i].equals(">")) && (!expression[i].equals("=")) && 
                    (!expression[i].equals("&")) && (!expression[i].equals("|"))) { 
                        oper_check++;
                        new_stack.push(expression[i]);
                    }
                    else{

                        if((expression[i].equals("~")) || (expression[i].equals("!"))){
                            
                            if((is_complex(new_stack.peek()) == true) && (new_stack.peek().charAt(0) != '~') && (new_stack.peek().charAt(0) != '!')){
                                new_stack.push(expression[i] + "(" + new_stack.pop() + ")");
                                brackets_stack.pop();
                                brackets_stack.push(expression[i]);
                            }
                            else
                                new_stack.push(expression[i] + new_stack.pop());
                        }
                        else{
                            oper_check--;

                            stack_elem_1 = new_stack.pop();
                            stack_elem_2 = new_stack.pop();

                            if(stack_elem_2 == "0")
                            {
                                oper_check = 0;
                                break;
                            }

                            if((is_complex(stack_elem_1) == false) && (is_complex(stack_elem_2) == false)){

                                new_stack.push(stack_elem_2 + expression[i] + stack_elem_1);
                            }
                            else if((is_complex(stack_elem_1) == false) && (is_complex(stack_elem_2) == true)){

                                operator_1 = brackets_stack.pop();
                                
                                if((Priorities(operator_1.charAt(0)) == 7) || (Priorities(operator_1.charAt(0)) == 1)){
                                    
                                    if((Priorities(operator_1.charAt(0)) < Priorities(expression[i].charAt(0)))){
                                        new_stack.push("(" + stack_elem_2 + ")" + expression[i] + stack_elem_1);
                                    }
                                    else if((Priorities(operator_1.charAt(0)) >= Priorities(expression[i].charAt(0)))){
                                            new_stack.push(stack_elem_2 +  expression[i]  + stack_elem_1);
                                    }  
                                }
                                else
                                {
                                    if((Priorities(operator_1.charAt(0)) < Priorities(expression[i].charAt(0)))){
                                        new_stack.push("(" + stack_elem_2 + ")" + expression[i] + stack_elem_1);
                                    }
                                    else if((Priorities(operator_1.charAt(0)) >= Priorities(expression[i].charAt(0)))){
                                            new_stack.push(stack_elem_2 +  expression[i] + stack_elem_1);
                                    }  
                                }
                            }
                            else if((is_complex(stack_elem_1) == true) && (is_complex(stack_elem_2) == false)){
                                operator_1 = brackets_stack.pop();

                                if((Priorities(operator_1.charAt(0)) == 7) || (Priorities(operator_1.charAt(0)) == 1)){
                                    
                                    if((Priorities(operator_1.charAt(0)) < Priorities(expression[i].charAt(0)))){
                                        new_stack.push(stack_elem_2 + expression[i] + "(" + stack_elem_1 + ")");
                                    }
                                    else if((Priorities(operator_1.charAt(0)) >= Priorities(expression[i].charAt(0)))){
                                            new_stack.push(stack_elem_2 +  expression[i]  + stack_elem_1);
                                    }  
                                }
                                else
                                {
                                    if((Priorities(operator_1.charAt(0)) <= Priorities(expression[i].charAt(0)))){
                                        new_stack.push(stack_elem_2 + expression[i] + "(" + stack_elem_1 + ")");
                                    }
                                    else if((Priorities(operator_1.charAt(0)) > Priorities(expression[i].charAt(0)))){
                                            new_stack.push(stack_elem_2 +  expression[i] + stack_elem_1);
                                    }  
                                }
                            }
                            else{
                                operator_1 = brackets_stack.pop();
                                operator_2 = brackets_stack.pop();
                                
                                String build_res = new String();
                                build_res = "";

                                if((Priorities(operator_2.charAt(0)) == 7) || (Priorities(operator_2.charAt(0)) == 1)){
                                    
                                    if((Priorities(operator_2.charAt(0)) < Priorities(expression[i].charAt(0)))){
                                        build_res += "(" + stack_elem_2 + ")" + expression[i];
                                    }
                                    else if((Priorities(operator_2.charAt(0)) >= Priorities(expression[i].charAt(0)))){
                                        build_res += stack_elem_2 +  expression[i];
                                    }  
                                }
                                else
                                {
                                    if((Priorities(operator_2.charAt(0)) < Priorities(expression[i].charAt(0)))){
                                        build_res += "(" + stack_elem_2 + ")" + expression[i];
                                    }
                                    else if((Priorities(operator_2.charAt(0)) >= Priorities(expression[i].charAt(0)))){
                                        build_res += stack_elem_2 +  expression[i];
                                    }  
                                }

                                if((Priorities(operator_1.charAt(0)) == 7) || (Priorities(operator_1.charAt(0)) == 1)){
                            
                                    if((Priorities(operator_1.charAt(0)) < Priorities(expression[i].charAt(0)))){
                                        build_res += "(" + stack_elem_1 + ")";
                                    }
                                    else if((Priorities(operator_1.charAt(0)) >= Priorities(expression[i].charAt(0)))){
                                        build_res += stack_elem_1;
                                    }  
                                }
                                else
                                {
                                    if((Priorities(operator_1.charAt(0)) <= Priorities(expression[i].charAt(0)))){
                                        build_res += "(" + stack_elem_1 + ")";
                                    }
                                    else if((Priorities(operator_1.charAt(0)) > Priorities(expression[i].charAt(0)))){
                                        build_res += stack_elem_1;
                                    }  
                                } 
                                new_stack.push(build_res);
                            }
                            brackets_stack.push(expression[i]);
                        }
                    }      
                    
                    if(oper_check < 0)
                        break;
                }

                if(oper_check != 1)
                    System.out.print("INF: error\n");
                else {
                    String result = new_stack.peek();

                    System.out.print("INF: ");
                    for(int j = 0; j < result.length(); j++)
                        System.out.print(result.charAt(j) + " ");
                    System.out.print("\n");
                }
            }
            
            data_am--;
        }
    }
}

class Stack_char{
    
    private char[] stack;
    public int top;

    public Stack_char()
    {
        stack = new char[257];
        top = -1;
    }

    public void push(char x)
    { 
        top++;
       stack[top] = x; 
    } 

    public char pop()
    { 
        if(top < 0)
            return '0';
        else 
            return stack[top--]; 
    } 

    public char peek()
    { 
        if ( top < 0 )
            return '0';
        else
            return stack[top];
    } 

    public Boolean isEmpty()
    {
        if(top == -1)
            return true;
        else
            return false;
    }
}

class Stack_string{
    
    private String[] stack; 
    public int top;

    public Stack_string()
    {
        stack = new String[257];
        top = -1;
    }

    public void push(String x)
    { 
        top++;
       stack[top] = x; 
    } 

    public String pop()
    { 
        if(top < 0)
            return "0";
        else 
            return stack[top--]; 
    } 

    public String peek()
    { 
        if ( top < 0 )
            return "0";
        else
            return stack[top];
    } 

    public Boolean isEmpty() {
        if(top == -1)
            return true;
        else
            return false;
    }
}
