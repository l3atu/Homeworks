
public class AdditionalTasks extends TaskDecorator{

    public AdditionalTasks(Task newtask) {
        super(newtask);
    }

    public String getDescription(){
        return temptask.getDescription()+"AdditionalTasks ";
    }
    public int getfee(){
        return temptask.getfee()+5;
    }
   
    
}
