
public class Worker extends Personel{
    
    public Worker(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int dayOfWork=20*105;
        int totalFee=0;
       
        if ((hour1-40)<10) {
            totalFee+=(hour1-40)*11;
        }
        else{
            totalFee+=10*11;
        }
        if ((hour2-40)<10) {
            totalFee+=(hour2-40)*11;
        }
        else{
            totalFee+=10*11;
        }
        if ((hour3-40)<10) {
            totalFee+=(hour3-40)*11;
        }
        else{
            totalFee+=10*11;
        }
        if ((hour4-40)<10) {
            totalFee+=(hour4-40)*11;
        }
        else{
            totalFee+=10*11;
        }
        return super.calculateSalary(hour1, hour2, hour3, hour4)+totalFee+dayOfWork; 
    }
    
    
    
}
