
public class PersonelCreator {
    
    public Personel personalCreate(String nameSurname,String id,int yearofstart,String position){
        
        if (position.equals("FACULTY_MEMBER")) {
            return new FacultyMember(nameSurname, id, yearofstart);
        }
        else if (position.equals("RESEARCH_ASSISTANT")) {
            return new ResearchAssistant(nameSurname, id, yearofstart);
        }
        else if (position.equals("OFFICER")) {
            return new Officer(nameSurname, id, yearofstart);
        }
        else if (position.equals("SECURITY")) {
            return new Security(nameSurname, id, yearofstart);
        }
        else if (position.equals("WORKER")) {
            return new Worker(nameSurname, id, yearofstart);
        }
        else if (position.equals("CHIEF")) {
            return new Chief(nameSurname, id, yearofstart);
        }
        else if (position.equals("PARTTIME_EMPLOYEE")) {
            return new PartTimeEmployee(nameSurname, id, yearofstart);
        }
        else{
            return null;
        }
        
    }
    
    public void print(String[] personelFile, String[] monitoringFile){
        
        for (int i = 0; i < personelFile.length; i++) {
            String nameSurname=personelFile[i].split("\t")[0];
            String name=personelFile[i].split("\t")[0].split(" ")[0];
            String surname=personelFile[i].split("\t")[0].split(" ")[1];
            String regi_number=personelFile[i].split("\t")[1];
            String position=personelFile[i].split("\t")[2];
            int yearOfstart=Integer.parseInt(personelFile[i].split("\t")[3]);
            
            PersonelCreator creator= new PersonelCreator();
            Personel personel= creator.personalCreate(nameSurname,regi_number, yearOfstart, position)
                    ;
            for (int j = 0; j < monitoringFile.length; j++) {
                String registrationNumber=monitoringFile[j].split("\t")[0];
                int hour1=Integer.parseInt(monitoringFile[j].split("\t")[1]);
                int hour2=Integer.parseInt(monitoringFile[j].split("\t")[2]);
                int hour3=Integer.parseInt(monitoringFile[j].split("\t")[3]);
                int hour4=Integer.parseInt(monitoringFile[j].split("\t")[4]);
                
                if (regi_number.equals(registrationNumber)) {
                    Output.writeToFile(regi_number+".txt","Name : "+name+"\n\n"
                    +"Surname : "+surname+"\n\n"
                    +"Registiration Number : "+regi_number+"\n\n"
                    +"Position : "+position+"\n\n"
                    +"Year Of Start : "+yearOfstart+"\n\n"
                    +"Total Salary : "+personel.calculateSalary(hour1, hour2, hour3, hour4)+".00 TL", true, true);
                    break;
                    
                }
            }
        }      
    }     
}
