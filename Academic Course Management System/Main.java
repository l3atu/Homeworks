
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Main {
    public static void main(String[] args) {
        StudentDaoImp studentdao= new StudentDaoImp();
        EnrollmentDaoImp enrollmentDao= new EnrollmentDaoImp();
        
        String[] inputCommands=Input.readFile(args[0], true, true);
        
        for (int i = 0; i < inputCommands.length; i++) {
            String command=inputCommands[i].split(" ")[0];
            if (command.equals("AddStudent")) {
                int id=Integer.parseInt(inputCommands[i].split(" ")[1]);
                String name=inputCommands[i].split(" ")[2];
                String surname=inputCommands[i].split(" ")[3];
                String phone=inputCommands[i].split(" ")[4];  
                String address="Address: ";
                for (int j = 5; j < inputCommands[i].split(" ").length; j++) {
                    address+=inputCommands[i].split(" ")[j]+" ";
                }
                Student s = new Student(id, name, surname, address, phone);
                studentdao.add(s);
                Output.writeToFile("output.txt", "Student "+id+" "+name+" added", true, true);
                
            }if (command.equals("RemoveStudent")) {
                int id=Integer.parseInt(inputCommands[i].split(" ")[1]);
                String name=null;
                for (Student student : studentdao.getAll()) {
                    if (student.getId()==id) {
                        name=studentdao.getByID(id).getName();
                    }
                }    
                for (Enrollment enrollment : enrollmentDao.getAll()) {
                    if (id==enrollment.getStudentid()) {
                        enrollmentDao.deleteByID(enrollment.getId());
                        break;
                    }
                }
                studentdao.deleteByID(id);
                Output.writeToFile("output.txt", "Student "+id+" "+name+" removed", true, true);
                
            }else if (command.equals("CreateEnrollment")) {
                int enrollmentID=Integer.parseInt(inputCommands[i].split(" ")[1]);
                int studentID=Integer.parseInt(inputCommands[i].split(" ")[2]);
                enrollmentDao.createEnrollment(enrollmentID, studentID);
                 Output.writeToFile("output.txt", "CourseEnrollment "+enrollmentID+" "+" created", true, true);
                
            }else if (command.equals("AddAssessment")) {
                int enrollmentID=Integer.parseInt(inputCommands[i].split(" ")[1]);
                String assessmentType=inputCommands[i].split(" ")[2];
                List<String> tasks= new ArrayList<>();
                for (int j = 3 ; j < inputCommands[i].split(" ").length; j++) {
                    tasks.add(inputCommands[i].split(" ")[j]);
                }
                if (assessmentType.equals("Essaybased")) {
                    Output.writeToFile("output.txt", "Essaybased assessment added to enrollment "+enrollmentID, true, true);
                    EssayBasedAssessment essay= new EssayBasedAssessment();
                    Task task=essay;
                    for (String task1 : tasks) {
                        if (task1.equals("AdditionalTasks")) {
                            task =new AdditionalTasks(task);
                            
                        }
                        if (task1.equals("Analysis")) {
                            task=new Analysis(task);
                            
                        }
                        if (task1.equals("QuestionSet")) {
                            task =new QuestionSet(task);
                           
                        }
                        if (task1.equals("LiteratureReview")) {
                            task =new LiteratureReview(task);
                            
                        }
                    }
                    enrollmentDao.getById(enrollmentID).addTasks(task);
                    enrollmentDao.saveEnrollmentsToFile();
                   
                }
                    
                if (assessmentType.equals("MultipleChoice")) {
                    Output.writeToFile("output.txt", "MultipleChoice assessment added to enrollment "+enrollmentID, true, true);
                    MultipleChoiceAssessment multi= new MultipleChoiceAssessment();
                    Task task=multi;
                    for (String task1 : tasks) {
                        if (task1.equals("AdditionalTasks")) {
                            task =new AdditionalTasks(task);
                            
                        }
                        if (task1.equals("Analysis")) {
                            task=new Analysis(task);
                            
                        }
                        if (task1.equals("QuestionSet")) {
                            task =new QuestionSet(task);
                           
                        }
                        if (task1.equals("LiteratureReview")) {
                            task =new LiteratureReview(task);
                            
                        }
                    }
                   enrollmentDao.getById(enrollmentID).addTasks(task);
                   enrollmentDao.saveEnrollmentsToFile();
                }
               
            }else if (command.equals("TotalFee")) {
                int enrollmentID=Integer.parseInt(inputCommands[i].split(" ")[1]);
                int total=0;
                Output.writeToFile("output.txt", "TotalFee for enrollment "+enrollmentID, true, true);
                for (Enrollment enrollment : enrollmentDao.getAll()) {
                    if(enrollment.getId()==enrollmentID){
                        for (Task task : enrollment.getTasks()) {
                            Output.writeToFile("output.txt","        "+task.getDescription()+task.getfee()+"$", true, true);
                            total+=task.getfee();
                        }
                    }
                
                }
                 Output.writeToFile("output.txt", "        Total: "+total+"$", true, true);
                
            }else if (command.equals("ListStudents")) {
                Output.writeToFile("output.txt", "Student List:", true, true);
                List<Student> studentList = studentdao.getAll();
                Collections.sort(studentList, Student.NameComparator);
                for (Student student : studentList) {
                Output.writeToFile("output.txt", student.getId()+"\t"+student.getName()+" "+
                        student.getSurname()+"\t"+student.getPhone()+"\t"+student.getAddress(), true, true);
            }
            }
           
        }
        
    }
}
