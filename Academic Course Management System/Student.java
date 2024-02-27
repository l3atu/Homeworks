
import java.util.Comparator;


public class Student {
    private int id;
    private String name;
    private String surname;
    private String address;
    private String phone;

    public Student(int id, String name, String surname, String address, String phone) {
        this.id = id;
        this.name = name;
        this.surname = surname;
        this.address = address;
        this.phone = phone;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getPhone() {
        return phone;
    }

    public void setPhone(String phone) {
        this.phone = phone;
    }

    public static Comparator<Student> NameComparator = new Comparator<Student>() {
        @Override
        public int compare(Student student1, Student student2) {
            return student1.getName().compareTo(student2.getName());
        }
    };
}
