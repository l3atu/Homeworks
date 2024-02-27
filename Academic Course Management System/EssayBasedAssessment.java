
import java.util.ArrayList;
import java.util.List;


public class EssayBasedAssessment implements Task{
    private List<Task> tasks= new ArrayList<>();

    @Override
    public String getDescription() {
        return "Essaybased\t";
    }

    @Override
    public int getfee() {
        return 10;
    }

    
  
    
}
