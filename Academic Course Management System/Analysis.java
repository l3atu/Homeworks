
public class Analysis extends TaskDecorator{
   
    public Analysis(Task newtask) {
        super(newtask);
    }
   
    public String getDescription(){
        return temptask.getDescription()+"Analysis ";
    }
    public int getfee(){
        return temptask.getfee()+10;
    }
}
