
import java.util.List;

public interface StudentDao {

    void add (Student s); 
    Student deleteByID(int id);
    Student  getByID(int id);
    List<Student> getAll();

}
