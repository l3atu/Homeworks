
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class StudentDaoImp implements StudentDao{
    private static final String STUDENT_FILE_NAME ="student.txt";
    private List<Student> studentList;

    public StudentDaoImp() {
        this.studentList = readStudentDataFromFile();
    }

    @Override
    public void add(Student s) {
        studentList.add(s);
        saveStudentDataToFile();
    }

    @Override
    public Student deleteByID(int id) {
        Iterator<Student> iterator = studentList.iterator();

        while (iterator.hasNext()) {
            Student s = iterator.next();
            if (s.getId() == id) {
                iterator.remove(); 
                saveStudentDataToFile();
                return s; 
            }
        }

        return null; 
    }

    @Override
    public Student getByID (int id) {
        for(Student s : studentList){
            if (s.getId()==id){
                return s;
            }
        }
        return null;
    }

    @Override
    public List<Student> getAll() {
        return studentList;
    }
    
    private List<Student> readStudentDataFromFile() {
        List<Student> students = new ArrayList<>();
        String currentDirectory = System.getProperty("user.dir"); 
        String filePath = currentDirectory + "/" + STUDENT_FILE_NAME; 
        try (BufferedReader bufferedReader = new BufferedReader(new FileReader(filePath))) {
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                String[] userData = line.split("\t");
                int id = Integer.parseInt(userData[0]);
                String name = userData[1].split(" ")[0];
                String surname = userData[1].split(" ")[1];
                String address = userData[3];
                String phone = userData[2];
                students.add(new Student(id, name, surname, address, phone));
            }
        } catch (IOException | NumberFormatException e) {
            e.printStackTrace();
        }
        return students;
    }

    private void saveStudentDataToFile() {
        String currentDirectory = System.getProperty("user.dir"); 
        String filePath = currentDirectory + "/" + STUDENT_FILE_NAME;
        
        try (FileWriter fileWriter = new FileWriter(filePath)) {
            for (Student s : studentList) {
                String userData = s.getId() + "\t" + s.getName() + " " + s.getSurname() + "\t" +
                        s.getPhone() + "\t" + s.getAddress();
                fileWriter.write(userData + System.lineSeparator());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
