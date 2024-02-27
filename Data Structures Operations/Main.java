
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;



public class Main {
    public static void main(String[] args) {
   
        ArrayList<Contact> arraylist = new ArrayList<Contact>();
        Set<Contact> hashset= new HashSet<Contact>();
        Set<Contact> treeset= new TreeSet<Contact>();
        Set<Contact> treeset2= new TreeSet<Contact>(new LastNameComparator());
        HashMap<String,Contact> hashmap=new HashMap<String,Contact>();
        
        String[] input=Input.readFile(args[0], true, true);
        for (int i = 0; i < input.length; i++) {
            String phone=input[i].split(" ")[0];
            String name=input[i].split(" ")[1];
            String surname=input[i].split(" ")[2];
            String socialSecurity=input[i].split(" ")[3];
            
            Contact user=new Contact(socialSecurity, name, surname, phone);
            arraylist.add(user);
            hashset.add(user);
            treeset.add(user);
            treeset2.add(user);
            hashmap.put(phone, user);
            
        }
        
        for(Contact c :arraylist){
            Output.writeToFile("contactsArrayList.txt", c.toString(), true, true);
        }
        
        Collections.sort(arraylist,new LastNameComparator());
        
        for(Contact c :arraylist){
            Output.writeToFile("contactsArrayListOrderByLastName.txt", c.toString(), true, true);
        }
        
        for(Contact c: hashset){
            Output.writeToFile("contactsHashSet.txt", c.toString(), true, true);
        }
        for(Contact c: treeset){
            Output.writeToFile("contactsTreeSet.txt", c.toString(), true, true);
        }
        
        for(Contact c: treeset2){
            Output.writeToFile("contactsTreeSetOrderByLastName.txt", c.toString(), true, true);
        }
        
        for (Map.Entry<String, Contact> entry : hashmap.entrySet()) {
            String key = entry.getKey();
            Contact value = entry.getValue();
            Output.writeToFile("contactsHashMap.txt", value.toString(), true, true);
        }
}
}
