
public class Phone {
    private String CountryCode;
    private String Number;
    private String Code;
    private String Type;

    public Phone(String CountryCode, String Number, String Code, String Type) {
        this.CountryCode = CountryCode;
        this.Number = Number;
        this.Code = Code;
        this.Type = Type;
    }

    public Phone(String Number, String Code, String Type) {
        this.Number = Number;
        this.Code = Code;
        this.Type = Type;
        this.CountryCode="TR";
    }

    public String getType() {
        return Type;
    }

    public void setType(String Type) {
        this.Type = Type;
    } 

    public String getCountryCode() {
        return CountryCode;
    }

    public void setCountryCode(String CountryCode) {
        this.CountryCode = CountryCode;
    }

    public String getNumber() {
        return Number;
    }

    public void setNumber(String PhoneNumber) {
        this.Number = PhoneNumber;
    }

    public String getCode() {
        return Code;
    }

    public void setCode(String Code) {
        this.Code = Code;
    }
    
    public void DisplayMethod() {
        System.out.println(Type+" "+"Phone:"+CountryCode+" "+Code+" "+Number);
    }
}
