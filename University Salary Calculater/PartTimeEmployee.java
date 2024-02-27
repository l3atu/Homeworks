
public class PartTimeEmployee extends Personel{
    
    public PartTimeEmployee(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int salary=0;
        if (hour1<10) {
            salary=salary;
        }
        else if (hour1>20){
            salary+=20*18;
        }else{
            salary+=hour1*18;
        }
        if (hour2<10) {
            salary=salary;
        }
        else if (hour2>20){
            salary+=20*18;
        }else{
            salary+=hour2*18;
        }if (hour3<10) {
            salary=salary;
        }
        else if (hour3>20){
            salary+=20*18;
        }else{
            salary+=hour3*18;
        }if (hour4<10) {
            salary=salary;
        }
        else if (hour4>20){
            salary+=20*18;
        }else{
            salary+=hour4*18;
        }
        int hourOfWork=(hour1+hour2+hour3+hour4)*18;
        return super.calculateSalary(hour1, hour2, hour3, hour4)+salary; 
    }
    
    
    
}
