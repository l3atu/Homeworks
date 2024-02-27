public class Main {
    
    public static void main(String[] args) {
        
        String[] personelFile=Input.readFile(args[0], true, true);
        String[] monitoringFile=Input.readFile(args[1], true, true);
        
        PersonelCreator printer = new PersonelCreator();
        printer.print(personelFile, monitoringFile);
        
    }
}
