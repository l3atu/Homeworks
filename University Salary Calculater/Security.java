
public class Security extends Personel{
   
    public Security(String nameANDsurname, String registration_number, int startOfyear) {
        super(nameANDsurname, registration_number, startOfyear);
    }

    @Override
    public int calculateSalary(int hour1, int hour2, int hour3, int hour4) {
        int transMoney=24*5;
        int foodMoney=24*10;
        int salary=0;
        if (hour1<30) {
            salary=salary;
        }
        else if (hour1>54){
            salary+=54*10;
        }else{
            salary+=hour1*10;
        }
        if (hour2<30) {
            salary=salary;
        }
        else if (hour2>54){
            salary+=54*10;
        }else{
            salary+=hour2*10;
        }if (hour3<30) {
            salary=salary;
        }
        else if (hour3>54){
            salary+=54*10;
        }else{
            salary+=hour3*10;
        }if (hour4<30) {
            salary=salary;
        }
        else if (hour4>54){
            salary+=54*10;
        }else{
            salary+=hour4*10;
        }
        int hourOfWork=(hour1+hour2+hour3+hour4)*10;
        return super.calculateSalary(hour1, hour2, hour3, hour4)+transMoney+foodMoney+salary; 
        
    }
   
    
}
