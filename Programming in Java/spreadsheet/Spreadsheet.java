public class Spreadsheet {
    public String[][] calculate(String[][] input) {

        int n = input.length, m = input[0].length;
        String[][] result = new String[n][m];
        String cell, formula, arguments;
        String[] args = new String[2];
        int row, column;
        Boolean completed = false;

        for (int i = 0; i < n; i++)
            System.arraycopy(input[i], 0, result[i], 0, m);

        while (!completed) {
            completed = true;

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    cell = result[i][j];

                    if (cell.charAt(0) == '$') {
                        column = cell.charAt(1) - 65;
                        row = Integer.parseInt(cell.substring(2)) - 1;
                        result[i][j] = result[row][column];
                        completed = false;
                    } 
                    else if (cell.charAt(0) == '=') {
                        formula = cell.substring(1, 4);
                        arguments = cell.substring(5, cell.length() - 1);
                        args = arguments.split(",");

                        String calc = calculateFormula(result, formula, args);
                        if (calc != "")
                            result[i][j] = calc;
                        completed = false;
                    } 
                    else
                        result[i][j] = cell;
                }
            }
        }
        return result;
    }

    public int[] toNumber(String[][] currInput, String arg) {

        if (arg.charAt(0) == '$') {
            int column = arg.charAt(1) - 65;
            int row = Integer.parseInt(arg.substring(2)) - 1;

            if (currInput[row][column].charAt(0) == '$' || currInput[row][column].charAt(0) == '=')
                return null;
            else
                return new int[] {Integer.parseInt(currInput[row][column])};
        }
        else 
            return new int[] {Integer.parseInt(arg)};
    }

    public String calculateFormula(String[][] currInput, String formula, String[] args) {

        int[] numArg1, numArg2; 
        int result = 0;

        numArg1 = toNumber(currInput, args[0]);
        numArg2 = toNumber(currInput, args[1]);

        if (numArg1 == null || numArg2 == null)
            return "";

        result = switch (formula) {
            case "ADD" -> numArg1[0] + numArg2[0];
            case "SUB" -> numArg1[0] - numArg2[0];
            case "MUL" -> numArg1[0] * numArg2[0];
            case "DIV" -> numArg1[0] / numArg2[0];
            case "MOD" -> numArg1[0] % numArg2[0];
            default -> 0;
        };

        return Integer.toString(result);
    }
}
