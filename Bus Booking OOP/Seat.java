
public class Seat extends Passenger{
    private int seatID;
    private boolean status;
    
    public Seat(int seatID, boolean status, String name, String surname, String gender, String CountryCode, String Number, String Code, String Type) {
        super(name, surname, gender, CountryCode, Number, Code, Type);
        this.seatID = seatID;
        this.status = status;
    }

    public Seat(int seatID, boolean status, String name, String surname, String gender, String Number, String Code, String Type) {
        super(name, surname, gender, Number, Code, Type);
        super.setCountryCode("TR");
        this.seatID = seatID;
        this.status = status;
    }
    
   
    public int getSeatID() {
        return seatID;
    }

    public void setSeatID(int seatID) {
        this.seatID = seatID;
    }

    public boolean isStatus() {
        return status;
    }

    public void setStatus(boolean status) {
        this.status = status;
    }

    @Override
    public void DisplayMethod() {
        if (status==true) {
            System.out.println("Seat: "+seatID+" "+"Status: Reserved");
        }   
        super.DisplayMethod();
    }
   
}
