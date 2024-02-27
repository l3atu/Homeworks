
import java.util.ArrayList;
import java.util.List;


public class MultipleChoiceAssessment implements Task{
    private List<Task> tasks= new ArrayList<>();

    @Override
    public String getDescription() {
        return "MultipleChoice\t";
    }

    @Override
    public int getfee() {
        return 15;
    }
    
   
    
}
