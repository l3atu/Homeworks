import java.util.InputMismatchException;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        
        Bus bus=new Bus("06 HUBM 06", 42);
        
        System.out.println("1-Book a seat\n"+
                "2-Cancel booking\n"+
                "3-Print all passengers\n"+
                "4-Print available seats\n"+
                "5-Print all seats\n"+
                "6-Search passenger\n"+
                "7-Exit\t");
        
        Scanner scanner=new Scanner(System.in);
        Scanner scanner2=new Scanner(System.in);
               
        while (true) {
            System.out.println("Enter your choose:");
            String choice=scanner.nextLine();
            if (choice.equals("1")) {
                System.out.println("Enter seat id:");
                Integer seatID = null;
                while (true) { 
                    try{
                        seatID=scanner2.nextInt();
                    if (seatID>bus.getSeatCount() || seatID<1) {
                        System.out.println("Invalid seat, seat id must be between 1 and "+bus.getSeatCount()+"!");
                        System.out.println("Enter seat id:");
                        seatID=scanner2.nextInt();
                    }
                    else{
                        break;
                    }
                    }
                    catch(InputMismatchException e){
                        System.out.println("Invalid seat, please enter a number!");
                        System.out.println("Enter seat id:");
                        scanner2.nextLine();
                    }
                }    
                System.out.println("Enter name:");
                String name=scanner.nextLine();
                System.out.println("Enter surname:");
                String surname=scanner.nextLine();
                System.out.println("Enter gender:");
                String gender=scanner.nextLine();
                while (true) {                    
                    if (gender.equals("E")||gender.equals("K")||gender.equals("e")||gender.equals("k")) {
                        break;
                    }
                    else{
                        System.out.println("Invalid gender!");
                        System.out.println("Enter gender:"); 
                        gender=scanner.nextLine();
                    }
                }
                System.out.println("Enter countrycode:");
                String countrycode=scanner.nextLine();
                System.out.println("Enter code:");
                String code=scanner.nextLine();
                System.out.println("Enter number:");
                String number=scanner.nextLine();
                while (true) {                    
                    if (number.length()!=7) {
                        System.out.println("Invalid number!");
                        System.out.println("Enter number:");
                        number=scanner.nextLine();
                    }
                    else{
                        break;
                    }
                }           
                System.out.println("Enter type:");
                String type=scanner.nextLine();
                if (countrycode.equals("")&& code.equals("+90")) {
                   bus.bookSeat(new Seat(seatID, true, name, surname, gender, number, code, type), seatID);
                }
                else{
                    bus.bookSeat(new Seat(seatID, true, name, surname, gender, countrycode, number, code, type), seatID); 
                }               
            }
            else if (choice.equals("2")) {
                System.out.println("Enter name:");
                String name=scanner.nextLine();
                System.out.println("Enter surname:");
                String surname=scanner.nextLine();
                bus.cancelBooking(name, surname);
            }
            else if (choice.equals("3")) {
                bus.printAllPassengers();              
            }
            else if (choice.equals("4")) {
                bus.printAllAvaiLableSeatsID();
            }
            else if (choice.equals("5")) {
                bus.printAllSeats();
            }
            else if (choice.equals("6")) {
                System.out.println("Enter name:");
                String name=scanner.nextLine();
                System.out.println("Enter surname:");
                String surname=scanner.nextLine();
                bus.searchPassenger(name, surname);
            }
            else if(choice.equals("7")){
                break;
            }
            else{
                System.out.println("Invalid operation!");
            } 
        }  
    }   
}
