
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class EnrollmentDaoImp implements EnrollmentDao{
    private static final String ENROLLMENT_FILE_NAME = "courseEnrollment.txt";
    private List<Enrollment> enrollments;

    public EnrollmentDaoImp() {
        this.enrollments = readEnrollmentsFromFile();
        
    }
    
    private Student getStudentById(int Id) {
        StudentDaoImp studentdao = new StudentDaoImp();
        return studentdao.getByID(Id);
        
    }
    
    @Override
    public void createEnrollment(int enrollmentId, int studentId) {
        Student student=getStudentById(studentId);
        Enrollment enrollment = new Enrollment(enrollmentId,studentId);
        enrollments.add(enrollment);
        saveEnrollmentsToFile();
      
    }

    @Override
    public Enrollment getById(int enrollmentId) {
        for (Enrollment e : enrollments) {
            if (e.getId()==enrollmentId) {
                return e;
            }
        }
        return null;
    }

    @Override
    public Enrollment deleteByID(int id) {
        Iterator<Enrollment> iterator = enrollments.iterator();

        while (iterator.hasNext()) {
            Enrollment e = iterator.next();
            if (e.getId() == id) {
                iterator.remove(); 
                saveEnrollmentsToFile();
                
            }
        }

        return null; 
    
    }

    @Override
    public List<Enrollment> getAll() {
        return enrollments;
    }
    
    
    private List<Enrollment> readEnrollmentsFromFile() {
        List<Enrollment> enrollments = new ArrayList<>();
        String currentDirectory = System.getProperty("user.dir"); 
        String filePath = currentDirectory + "/" + ENROLLMENT_FILE_NAME; 

        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath))) {
            String line;
            Enrollment e = new Enrollment(0,0);
            Student student=new Student(0, "x", "x", "x", "x");
            
            while ((line = bufferedReader.readLine()) != null) {    
                String[] IDs = line.split("\t");
                if (line.isEmpty()) {
                    break;
                }
                if (isNumeric(IDs[0]) && isNumeric(IDs[1])) {
                    int enrollmentID = Integer.parseInt(IDs[0]);
                    int studentID = Integer.parseInt(IDs[1]);
                    e= new Enrollment(enrollmentID,studentID);
                    student=getStudentById(studentID);
                    enrollments.add(e); 
                    
                }
                else{               
                    String assessmentType =IDs  [0];
                    String[] tasks=IDs[1].split(" ");
                    if (assessmentType.equals("MultipleChoice")) {
                        MultipleChoiceAssessment multi= new MultipleChoiceAssessment();
                        Task task=multi;
                        for (int i = 0; i < tasks.length; i++) {                                     
                            if (tasks[i].equals("AdditionalTasks")) {
                               task=new AdditionalTasks(task);

                            }
                            if (tasks[i].equals("QuestionSet")) {

                               task=new QuestionSet(task);

                            }
                            if (tasks[i].equals("LiteratureReview")) {

                                task=new LiteratureReview(task);

                            }
                            if (tasks[i].equals("Analysis")) {

                                task=new Analysis(task);

                            } 
                            
                        }
                        e.addTasks(task); 
                    }
                    if (assessmentType.equals("Essaybased")) {
                        EssayBasedAssessment essay=new EssayBasedAssessment();
                        Task task=essay;
                        for (int i = 0; i < tasks.length; i++) {                                     
                            if (tasks[i].equals("AdditionalTasks")) {
                               task=new AdditionalTasks(task);

                            }
                            if (tasks[i].equals("QuestionSet")) {

                               task=new QuestionSet(task);

                            }
                            if (tasks[i].equals("LiteratureReview")) {

                                task=new LiteratureReview(task);

                            }
                            if (tasks[i].equals("Analysis")) {

                               task=new Analysis(task);

                            } 
                           
                        }
                         e.addTasks(task); 
                    }                               
                }
            }
        } catch (IOException | NumberFormatException e) {
            e.printStackTrace();
        }
        return enrollments;
    }

    public void saveEnrollmentsToFile() {
        String currentDirectory = System.getProperty("user.dir"); 
        String filePath = currentDirectory + "/" + ENROLLMENT_FILE_NAME;
        
        try (FileWriter fileWriter = new FileWriter(filePath)) {
            for (Enrollment e : enrollments) {
                String userData = e.getId()+"\t"+e.getStudentid();
                fileWriter.write(userData + System.lineSeparator());
                
                for (Task t : e.getTasks()) {
                    String userData2 = t.getDescription();
                    fileWriter.write(userData2 + System.lineSeparator());
                }
             
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
    private boolean isNumeric(String str) {
        try {
            Integer.parseInt(str);
            return true;
        } catch (NumberFormatException e) {
            return false;
        }
    }
    
}
