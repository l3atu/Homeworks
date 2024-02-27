
public class SportCenter {
    private String name;
    public PersonalTrainer[] PTs=new PersonalTrainer[100];

    public SportCenter(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
    
    public void addPT(PersonalTrainer pt){
        for (int i = 0; i < PTs.length; i++) {
            if (PTs[i]==null) {
                PTs[i]=pt;
                break;
                
            }
        }
    }
    
    public PersonalTrainer searchPT(String name,String surname){
         for (int i = 0; i < PTs.length; i++) {
            if (PTs[i]!=null && PTs[i].getName().equals(name) && PTs[i].getSurname().equals(surname)) {
                return PTs[i];
            }
        }
        return null;
    }
    
}
