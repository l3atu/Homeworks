
public class QuestionSet extends TaskDecorator{

    public QuestionSet(Task newtask) {
        super(newtask);
    }
   
    public String getDescription(){
        return temptask.getDescription()+"QuestionSet ";
    }
    public int getfee(){
        return temptask.getfee()+7;
    }
    
}
