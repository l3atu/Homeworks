
public class Member extends Person{
    private double weight;
    private double height;

    public Member(int id, String name, String surname,double weight, double height) {
        super(id, name, surname);
        this.weight = weight;
        this.height = height;
    }
    
    public double bmi(){
        double bmi=weight/(height*height);
        return bmi();    
    }
    
    public String weightStatus(){
        double bmi=weight/(height*height);
        if (bmi<18.5) {
            return "Thin";
        }
        else if (18.5< bmi && bmi<24.9) {
            return "Normal";
        }
        else if (25<bmi && bmi<29.9) {
            return "Fat";
        }
        else if (bmi>=30) {
            return "Obese";
        }
        return null;
    }

    public double getWeight() {
        return weight;
    }

    public void setWeight(double weight) {
        this.weight = weight;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }
    
    
}
