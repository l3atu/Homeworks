
import java.util.ArrayList;
import java.util.List;


public class Enrollment {
    private int id;
    private int studentid;
    private List<Task> tasks= new ArrayList<>();;

    public Enrollment(int id, int studentid) {
        this.id = id;
        this.studentid = studentid;
    }

    public int getStudentid() {
        return studentid;
    }

    public void setStudentid(int studentid) {
        this.studentid = studentid;
    }
    

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public List<Task> getTasks() {
        return tasks;
    }


    public void addTasks(Task task) {
        if (task != null) {
            tasks.add(task);
        } else {
        System.err.println("Error: assessment null.");
    }
    }
    
    
}
