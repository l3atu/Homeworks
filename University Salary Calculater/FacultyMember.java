
public class FacultyMember extends Personel{
    
    public FacultyMember(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int baseSalary=2600;
        int totalFee=0;
        int ssBenefits=2600*135/100;
       
        if ((hour1-40)<=8) {
            totalFee+=(hour1-40)*20;
        }
        else{
            totalFee+=8*20;
        }
        if ((hour2-40)<=8) {
            totalFee+=(hour2-40)*20;
        }
        else{
            totalFee+=8*20;
        }
        if ((hour3-40)<=8) {
            totalFee+=(hour3-40)*20;
        }
        else{
            totalFee+=8*20;
        }
        if ((hour4-40)<=8) {
            totalFee+=(hour4-40)*20;
        }
        else{
            totalFee+=8*20;
        }
        return super.calculateSalary(hour1, hour2, hour3, hour4)+baseSalary+totalFee+ssBenefits;
     
    }
    
    
}
