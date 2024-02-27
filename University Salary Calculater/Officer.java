
public class Officer extends Personel{
  
    public Officer(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int baseSalary=2600;
        int totalFee=0;
        int ssBenefits=2600*65/100;
       
        if ((hour1-40)<10) {
            totalFee+=(hour1-40)*20;
        }
        else{
            totalFee+=10*20;
        }
        if ((hour2-40)<10) {
            totalFee+=(hour2-40)*20;
        }
        else{
            totalFee+=10*20;
        }
        if ((hour3-40)<10) {
            totalFee+=(hour3-40)*20;
        }
        else{
            totalFee+=10*20;
        }
        if ((hour4-40)<10) {
            totalFee+=(hour4-40)*20;
        }
        else{
            totalFee+=10*20;
        }
        return super.calculateSalary(hour1, hour2, hour3, hour4)+baseSalary+totalFee+ssBenefits; 
    }
    
    
}
