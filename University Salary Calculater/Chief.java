
public class Chief extends Personel{
    
    public Chief(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int dayOfWork=20*125;
        int totalFee=0;
       
        if ((hour1-40)<8) {
            totalFee+=(hour1-40)*15;
        }
        else{
            totalFee+=8*15;
        }
        if ((hour2-40)<8) {
            totalFee+=(hour2-40)*15;
        }
        else{
            totalFee+=8*15;
        }
        if ((hour3-40)<8) {
            totalFee+=(hour3-40)*15;
        }
        else{
            totalFee+=8*15;
        }
        if ((hour4-40)<8) {
            totalFee+=(hour4-40)*15;
        }
        else{
            totalFee+=8*15;
        }
        return super.calculateSalary(hour1, hour2, hour3, hour4)+totalFee+dayOfWork; 
    }
    
}
