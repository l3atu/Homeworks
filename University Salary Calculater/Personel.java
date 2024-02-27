
public class Personel {
    private String nameANDsurname;
    private String registration_number;
    private int startOfyear;

    public Personel(String nameANDsurname, String registration_number, int startOfyear) {
        this.nameANDsurname = nameANDsurname;
        this.registration_number = registration_number;
        this.startOfyear = startOfyear;
    }

    public String getNameANDsurname() {
        return nameANDsurname;
    }

    public void setNameANDsurname(String nameANDsurname) {
        this.nameANDsurname = nameANDsurname;
    }

    public String getRegistration_number() {
        return registration_number;
    }

    public void setRegistration_number(String registration_number) {
        this.registration_number = registration_number;
    }

    public int getStartOfyear() {
        return startOfyear;
    }

    public void setStartOfyear(int startOfyear) {
        this.startOfyear = startOfyear;
    }

    
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4){
        int severancePay=(2023-startOfyear)*20*8/10;
        int salary=severancePay;
        return salary;
    }
    
}
