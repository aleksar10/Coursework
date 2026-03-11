import java.util.Scanner;

class TrainGroup {
    Train first;

    TrainGroup() {   
        first = null; 
    }
    public void addNewTrain(String tName, TrainCar tCar) { 
        Train newTrain = new Train(tName, tCar);
        Train first_copy;

        if (first == null) { 
            first = newTrain;
        }
        else { 

            Train currTrain = first; 
            while (currTrain != null) { 

                if(currTrain.nameTrain.equals(tName)){ 
                    System.out.println("Train " + tName + " already exists");
                    return;
                }
                currTrain = currTrain.nextTrain;
            }
            first_copy = first; 
            first = newTrain; 
            first.nextTrain = first_copy;
        }
    }
    public Train[] LocateTrain(String tName) { 
        Train currTrain = first;
        Train prevTrain = null;

        
        while ((currTrain != null) && (!currTrain.nameTrain.equals(tName))) {
            prevTrain = currTrain;
            currTrain = currTrain.nextTrain;
        }
        
        if (currTrain != null) { 
            return new Train[]{currTrain, prevTrain}; 
        } else {
            return null; 
        }
    }
    public void DisplayTrains() { 

        Train currTrain = first;

        System.out.print("Trains:");
        while (currTrain != null) { 
            System.out.print(" " + currTrain.nameTrain); 
            currTrain = currTrain.nextTrain;
        }
        System.out.print("\n");
    }
    public void DeleteTrain(Train[] toDelete) { 
        if (toDelete[1] == null) { 
            first = toDelete[0].nextTrain; 
        }
        else {
            toDelete[1].nextTrain = toDelete[0].nextTrain; 
        }
    }
}

class Train {
    String nameTrain;
    Train nextTrain;
    TrainCar firstCar;
    TrainCar lastCar;
    private boolean bCarReversed;

    Train() {
        firstCar = new TrainCar();
        lastCar = firstCar;
        nameTrain = "";
        nextTrain = null;
    }
    Train(String newTrainName, TrainCar newTrainCar) {
        nameTrain = newTrainName;
        firstCar = new TrainCar();
        lastCar = newTrainCar;
        nextTrain = null;
        firstCar.next = newTrainCar;
        firstCar.prev = newTrainCar;
        newTrainCar.prev = firstCar;
        newTrainCar.next = firstCar;
    }
    public TrainCar getNextCar(TrainCar currCar) {
        if (bCarReversed) {
            if (currCar.prev.prev == currCar) {
                bCarReversed = !bCarReversed;
            }
            return currCar.prev;
        }
        else {
            if (currCar.next.next == currCar) {
                bCarReversed = !bCarReversed;
            } 
            return currCar.next;
        }
    }
    public void DisplayFull() {
        TrainCar currCar;
     
        System.out.print(this.nameTrain + ": ");

        if (firstCar.next == lastCar)
            currCar = firstCar.prev;
        else
            currCar = firstCar.next;

        if (currCar.next == firstCar)
            bCarReversed = true;
        else
            bCarReversed = false;

        while (currCar != firstCar) {
            System.out.print(currCar.name);
            currCar = getNextCar(currCar);
            if (currCar == firstCar) {
                System.out.print("\n");
            }
            else {
                System.out.print(" ");
            }
        }
    }
    public void InsertTrainCar(TrainCar newCar, boolean bFirst) {
        if (bFirst) {
            if ((firstCar.next == lastCar) && (firstCar.prev != lastCar)) {

                if (firstCar.prev.prev == firstCar) {
                    firstCar.prev.prev = newCar;
                    newCar.prev = firstCar;
                    newCar.next = firstCar.prev;
                }
                else { 
                    firstCar.prev.next = newCar;
                    newCar.next = firstCar;
                    newCar.prev = firstCar.prev;
                }
                firstCar.prev = newCar;                    
            }
            else {

                if (firstCar.next.next == firstCar) {
                    firstCar.next.next = newCar;
                }
                else { 
                    firstCar.next.prev = newCar;
                }
                newCar.next = firstCar.next;
                firstCar.next = newCar;
                newCar.prev = firstCar;
            }
        }
        else { 
            if ((firstCar.next == lastCar) && (firstCar.prev != lastCar)) {
                if (firstCar.next.next == firstCar) {
                    firstCar.next.next = newCar;
                    newCar.next = firstCar;
                    newCar.prev = firstCar.next;
                }
                else {
                    firstCar.next.prev = newCar;
                    newCar.next = firstCar.next;
                    newCar.prev = firstCar;
                }
                firstCar.next = newCar;
                lastCar = newCar;
        }
            else {
                if (lastCar.next == firstCar) {
                    lastCar.next = newCar;
                    newCar.next = firstCar;
                    newCar.prev = lastCar;
                }
                else {
                    lastCar.prev = newCar;
                    newCar.prev = firstCar;
                    newCar.next = lastCar;
                }
                firstCar.prev = newCar;
                lastCar = newCar;                    
            }
        }
    }
    public void Reverse() {
        if (lastCar == firstCar.next)
            lastCar = firstCar.prev;
        else
            lastCar = firstCar.next;
    }
}

class TrainCar {
    String name;
    TrainCar next;
    TrainCar prev;

    TrainCar() {
        name = "";
    }
    TrainCar(String newCarName) {
        name = newCarName;
    }
    TrainCar(TrainCar tCarPattern) {
        name = tCarPattern.name;
    }
}

public class Source {
    public static Scanner scanner = new Scanner(System.in);

    public static void handleNew(TrainGroup tGroup, Scanner scanner) { 
        String trainName, trainCarName;
        TrainCar trainCar;

        trainName = scanner.next();
        trainCarName = scanner.next();

        trainCar = new TrainCar(trainCarName); 
        tGroup.addNewTrain(trainName, trainCar); 
    }
    public static void handleInsertFirst(TrainGroup tGroup, Scanner scanner) { 
        String trainName, trainCarName;
        Train[] tResult;
        TrainCar newTrainCar;

        trainName = scanner.next();
        tResult = tGroup.LocateTrain(trainName);
        if (tResult == null) { 
            printTrainErrorMessage(trainName, true);
            return;
        }
        trainCarName = scanner.next();
        newTrainCar = new TrainCar(trainCarName);
        tResult[0].InsertTrainCar(newTrainCar, true); 
    }
    public static void handleInsertLast(TrainGroup tGroup, Scanner scanner) { 
        String trainName, trainCarName;
        Train[] tResult;
        TrainCar newTrainCar;

        trainName = scanner.next();
        tResult = tGroup.LocateTrain(trainName);
        if (tResult == null) { 
            printTrainErrorMessage(trainName, true);
            return;
        }
        trainCarName = scanner.next();
        newTrainCar = new TrainCar(trainCarName);
        tResult[0].InsertTrainCar(newTrainCar, false); 
    }
    public static void handleDisplay(TrainGroup tGroup, Scanner scanner) { 
        String trainName;
        Train[] tResult;

        trainName = scanner.next();
        tResult = tGroup.LocateTrain(trainName);
        if (tResult == null) { 
            printTrainErrorMessage(trainName, true);
        }
        else {
            tResult[0].DisplayFull(); 
        }
    }
    public static void handleTrains(TrainGroup tGroup, Scanner scanner) { 
        tGroup.DisplayTrains();
    }
    public static void handleReverse(TrainGroup tGroup, Scanner scanner) { 
        String trainName;
        Train[] tResult;

        trainName = scanner.next();
        tResult = tGroup.LocateTrain(trainName);
        if (tResult == null) { 
            printTrainErrorMessage(trainName, true);
            return;
        }
        tResult[0].Reverse();
    }
    public static void handleUnion(TrainGroup tGroup, Scanner scanner) { 
        String train1Name, train2Name;
        Train[] train1, train2;
        TrainCar firstCarSecondTrain;

        train1Name = scanner.next();
        train2Name = scanner.next();
        train1 = tGroup.LocateTrain(train1Name);

        if (train1 == null) { 
            printTrainErrorMessage(train1Name, true);
            return;
        }
        train2 = tGroup.LocateTrain(train2Name);
        if (train2 == null) { 
            printTrainErrorMessage(train2Name, true);
            return;
        }

        if (train2[0].firstCar.next == train2[0].lastCar) {
            firstCarSecondTrain = train2[0].firstCar.prev;
        }
        else {
            firstCarSecondTrain = train2[0].firstCar.next;
        }
        
        if(train1[0].lastCar.next == train1[0].firstCar){
            train1[0].lastCar.next = firstCarSecondTrain; 
        }
        else{
            train1[0].lastCar.prev = firstCarSecondTrain; 
        }

        if(firstCarSecondTrain.next == train2[0].firstCar){
            firstCarSecondTrain.next = train1[0].lastCar;
        }
        else{
            firstCarSecondTrain.prev = train1[0].lastCar;
        }

        if(train1[0].firstCar.next == train1[0].lastCar){
            train1[0].firstCar.next = train2[0].lastCar;
        }
        else{
            train1[0].firstCar.prev = train2[0].lastCar;
        }

        if(train2[0].lastCar.next == train2[0].firstCar){
            train2[0].lastCar.next = train1[0].firstCar;
        }
        else{
            train2[0].lastCar.prev = train1[0].firstCar;
        }

        train1[0].lastCar = train2[0].lastCar;

        tGroup.DeleteTrain(train2);
    }
    public static void handleDel(TrainGroup tGroup, Scanner scanner, boolean bFirst) { 
        String train1Name, train2Name;
        Train[] train1, train2;
        TrainCar tCarMoved, tCarNextToMoved;
        Boolean create_2nd = true;
        train1Name = scanner.next();
        train2Name = scanner.next();

        train1 = tGroup.LocateTrain(train1Name);
        if (train1 == null) { 
            printTrainErrorMessage(train1Name, true);
            return;
        }

        train2 = tGroup.LocateTrain(train2Name);
        if (train2 != null) { 
            printTrainErrorMessage(train2Name, false);
            create_2nd = false;
        }
        if (bFirst) {
            if (train1[0].firstCar.next == train1[0].lastCar) {
                tCarMoved = train1[0].firstCar.prev;
            }
            else {
                tCarMoved = train1[0].firstCar.next;
            }
            if (tCarMoved.next == train1[0].firstCar)
                tCarNextToMoved = tCarMoved.prev;
            else
                tCarNextToMoved = tCarMoved.next;

            if (tCarNextToMoved.next == tCarMoved)
                tCarNextToMoved.next = train1[0].firstCar;
            else
                tCarNextToMoved.prev = train1[0].firstCar;

            if (train1[0].firstCar.next == tCarMoved)
                train1[0].firstCar.next = tCarNextToMoved;
            else
                train1[0].firstCar.prev = tCarNextToMoved;            
        }
        else { 
            tCarMoved = train1[0].lastCar;

            if (tCarMoved.next == train1[0].firstCar)
                tCarNextToMoved = tCarMoved.prev;
            else
                tCarNextToMoved = tCarMoved.next;

            if (tCarNextToMoved.next == tCarMoved)
                tCarNextToMoved.next = train1[0].firstCar;
            else
                tCarNextToMoved.prev = train1[0].firstCar;

            if (train1[0].firstCar.next == tCarMoved)
                train1[0].firstCar.next = tCarNextToMoved;
            else
                train1[0].firstCar.prev = tCarNextToMoved;
            train1[0].lastCar = tCarNextToMoved;
        }
        if((train1[0].firstCar.next == train1[0].firstCar) || (train1[0].firstCar.prev == train1[0].firstCar))
            tGroup.DeleteTrain(train1);

        if(create_2nd == true){
            tGroup.addNewTrain(train2Name, tCarMoved);
        }
    }

    public static void printTrainErrorMessage(String tName, boolean doesNot) { 
        if (doesNot) {
            System.out.println("Train " + tName + " does not exist");
        }
        else {
            System.out.println("Train " + tName + " already exists");
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        TrainGroup myGroup = new TrainGroup();
        String command;
        int i, j;

        int sets = scanner.nextInt();
        scanner.nextLine();

        for (i = 0; i < sets; i++) 
        {
            int data_am = scanner.nextInt();
            
            for (j = 0; j < data_am; j++) 
            {
                command = scanner.next();
                switch (command) 
                {
                    case "New":
                    handleNew(myGroup, scanner);
                    break;
                    case "InsertFirst":
                    handleInsertFirst(myGroup, scanner);
                    break;
                    case "InsertLast":
                    handleInsertLast(myGroup, scanner);
                    break;
                    case "Display":
                    handleDisplay(myGroup, scanner);
                    break;
                    case "Trains":
                    handleTrains(myGroup, scanner);
                    break;
                    case "Reverse":
                    handleReverse(myGroup, scanner);
                    break;
                    case "Union":
                    handleUnion(myGroup, scanner);
                    break;
                    case "DelFirst":
                    handleDel(myGroup, scanner, true);
                    break;
                    case "DelLast":
                    handleDel(myGroup, scanner, false);
                    break;
                }
            }
        }
        scanner.close();
    }
}
