
public class Bus {
    private String plate;
    private int seatCount;
    private Seat[] seat;

    public Bus(String plate, int seatCount) {
        this.plate = plate;
        this.seatCount = seatCount;
        seat=new Seat[seatCount];
    }
    
    public String getPlate() {
        return plate;
    }

    public void setPlate(String plate) {
        this.plate = plate;
    }

    public int getSeatCount() {
        return seatCount;
    }

    public void setSeatCount(int seatCount) {
        this.seatCount = seatCount;
    }

    public Seat[] getSeat() {
        return seat;
    }

    public void setSeat(Seat[] seat) {
        this.seat = seat;
    }
    
    public void bookSeat(Seat s,int seatId){        
            if (seat[seatId-1]==null) {
                seat[seatId-1]=s;
            }
            else if (seat[seatId-1]!=null) {
                System.out.println("The seat has already reserved!");
            }                      
    }
    public void cancelBooking(String name,String surname){
        for (int i = 0; i < seat.length; i++) {
            if (seat[i]!=null) {
                if (seat[i].getName().equals(name) && seat[i].getSurname().equals(surname)) {
                    seat[i]=null;
                    System.out.println("Booking is canceled!");
                }
                else{
                    System.out.println("Passenger not found!");
                }
            }
        }    
    }
    
    public void printAllPassengers(){
        int x=0;
        for (int i = 0; i < seat.length; i++) {
            if (seat[i]!=null) {
                seat[i].DisplayMethod(); 
            }
            else if (seat[i]==null){
               x++;
                if (seat[i]==null && x==42) {
                    System.out.println("No passengers!");
                }
            }
        }
    }
    public  void searchPassenger(String name,String surname){
        for (int i = 0; i < seat.length; i++) {
            if (seat[i]!=null) {
                if (seat[i].getName().equals(name) && seat[i].getSurname().equals(surname)) {
                    System.out.println(seat[i].getName()+" "+seat[i].getSurname()+" "+"("+seat[i].getGender()+")");
                    System.out.println(seat[i].getType()+" "+"Phone:"+seat[i].getCountryCode()+" "+seat[i].getCode()+" "+seat[i].getNumber());                  
                }
                else{
                    System.out.println("Passenger not found!");
                }
            }
        }    
    }
    public void printAllAvaiLableSeatsID(){
        for (int i = 0; i < seat.length; i++) {
            if (seat[i]==null) {
                System.out.println(i+1); 
            }
        }
    }
    public void printAllSeats(){
        for (int i = 0; i < seat.length; i++) {
            if (seat[i]!=null) {
                seat[i].DisplayMethod(); 
            }
            else{
                System.out.println("Seat: "+ (i+1) +" Status: Unreserved");
            }
        }
    }
}
