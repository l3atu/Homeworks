import java.text.*;
import java.util.Date;
import java.text.ParseException;
public class Main {
    public static void main(String[] args) throws ParseException  {
        SimpleDateFormat sdformat = new SimpleDateFormat("dd.MM.yyyy");       
        String[] purchaseOrder=Input.readFile(args[0], false, false);
        String[] priceCatalog=Input.readFile(args[1], false, false);
        String[][] purchaseOrderSingle = new String[purchaseOrder.length][purchaseOrder[0].split("").length];
        String[][] priceCatalogSingle = new String[priceCatalog.length][priceCatalog[0].split("").length];
        for (int i = 0; i <purchaseOrder.length; i++) {
            String[] line = purchaseOrder[i].split("\t");
            purchaseOrderSingle[i] = line;
        }
        for (int i = 0; i <priceCatalog.length; i++) {
            String[] line = priceCatalog[i].split("\t");
            priceCatalogSingle[i] = line;
        }    
        for (int i = 0; i < purchaseOrder.length; i++) {
            String memberName=purchaseOrderSingle[i][0];
            String membershipType=purchaseOrderSingle[i][1];
            Date purchaseDate=sdformat.parse(purchaseOrderSingle[i][2]);
            float totalPrice=0;
            Output.writeToFile("Output.txt", "------------Bill for Customer "+(i+1)+"------------", true, true);
            Output.writeToFile("Output.txt", "Customer: "+memberName, true, true);
            Output.writeToFile("Output.txt", "Membership Type: "+membershipType, true, true);
            Output.writeToFile("Output.txt", "Date: "+purchaseOrderSingle[i][2]+"\n", true, true);
            Output.writeToFile("Output.txt", "Items Purchased:", true, true);
            for (int k = 3; k < purchaseOrderSingle[i].length; k+=2) {
                String book=purchaseOrderSingle[i][k];
                Integer bookQuantity=Integer.parseInt(purchaseOrderSingle[i][k+1]); 
                for (int j = 0; j < priceCatalog.length; j++) {
                    String bookName=priceCatalogSingle[j][0];
                    String membership=priceCatalogSingle[j][1];
                    Date startingDate=sdformat.parse(priceCatalogSingle[j][2]);
                    Date endingDate=sdformat.parse(priceCatalogSingle[j][3]);
                    Float price=Float.parseFloat(priceCatalogSingle[j][4]);
                    if(book.equals(bookName) && membershipType.equals(membership)){
                        if (purchaseDate.compareTo(startingDate)>=0 && purchaseDate.compareTo(endingDate)<=0) {
                            float subtotal1=price*bookQuantity;
                            totalPrice+=subtotal1;
                            Output.writeToFile("Output.txt", book+" (Qty: "+bookQuantity+") - "+price+" each", true, true);
                            Output.writeToFile("Output.txt", "(Valid from "+priceCatalogSingle[j][2]+" to "+priceCatalogSingle[j][3]+")", true, true);
                            Output.writeToFile("Output.txt", "Subtotal: "+price*bookQuantity, true, true);
                            
                        }
                    }                         
                }
            }
            Output.writeToFile("Output.txt", "\n", true, true);
            Output.writeToFile("Output.txt", "Total cost: "+totalPrice+"\n", true, true);
        }
    }
}
