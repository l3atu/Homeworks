
public class LiteratureReview extends TaskDecorator{

    public LiteratureReview(Task newtask) {
        super(newtask);
    }

    public String getDescription(){
        return temptask.getDescription()+"LiteratureReview ";
    }
    public int getfee(){
        return temptask.getfee()+15;
    }


}
