
import java.util.List;

public interface EnrollmentDao {
    
    void createEnrollment(int enrollmentId, int studentId);
    Enrollment getById(int enrollmentId);
    Enrollment deleteByID(int id);
    List<Enrollment> getAll();
}
