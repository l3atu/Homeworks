
public class ResearchAssistant extends Personel {
    
    public ResearchAssistant(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int baseSalary=2600;
        int ssBenefits=2600*105/100;
        return super.calculateSalary(hour1, hour2, hour3, hour4)+baseSalary+ssBenefits;
    }
    
   
    
}
