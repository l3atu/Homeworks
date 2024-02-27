
import java.util.Arrays;


public class PersonalTrainer extends Person{
    private Member[] members=new Member[100];
    private String sportType;

    public PersonalTrainer(int id, String name, String surname, String sportType) {
        super(id, name, surname);
        this.sportType=sportType;
    }
    
    public Member[] getMembers() {
        return members;
    }

    public void setMembers(Member[] members) {
        this.members = members;
    }

    public String getSportType() {
        return sportType;
    }

    public void setSportType(String sportType) {
        this.sportType = sportType;
    }
    
    public int returnCountofMembers(){
        int count=0;
        for (int i = 0; i < members.length; i++) {
            if (members[i]!=null) {
              count+=1;
            }
        }
        return count;
    }
    
    public void addMember(Member m){
        for (int i = 0; i < members.length; i++) {
            if (members[i]==null) {
                members[i]=m;
                break;
                
            }
        }
    }
    
    public Member returnMember(int memberID){
        for (int i = 0; i < members.length; i++) {
            if (members[i].getId()==memberID) {
                return members[i];
            }
        }
        return null;
    }
    
    public Member ReturnFattestMember(){
        Member fattest = null; 
        double max = Double.MIN_VALUE; 

        for (int i = 0; i < members.length; i++) {
            if (members[i] != null) {
                double weight = members[i].getWeight(); 
                if (weight > max) {
                    max = weight; 
                    fattest = members[i]; 
                }
            }
        }
        return fattest; 
    }
}
