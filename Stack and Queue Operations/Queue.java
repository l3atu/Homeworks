
import java.util.Arrays;


public class Queue {
   private int[] array=new int[100];
    
    
    public void push(int i){
        for (int j = array.length-1; j >= 0; j--) {
            if (array[j]==0) {
                array[j]=i;
                break;
            }
        }
    }
    
    public int front(){
        for (int i = array.length-1 ; i >= 0; i--) {
            if (array[i]!=0) {
                return array[i];               
            }
        }
        return 0;
    }
    
    public int rear(){
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                return array[i];
            }
        }
        return 0;
    }
    
    public void poll(){
        for (int i =  array.length-1 ; i >= 0; i--) {
            if (array[i]!=0) {
                array[i]=0;
                break;
            }
        }
        for (int i = array.length-1; i >= 0; i--) {
            array[i]=array[i-1];
            if (array[i-1]==0) {
                break;
            }
        }
    }
    
    public boolean isEmpty(){
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                return false;
            }
        }
        return true;
    }
    
    public int size(){
        int size=0;
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                size++;
            }
        }
        return size;
    }
    
    public int distinctCount(){
        int count=0;
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                boolean isDistinct = true;
                for (int j = 1; j < i; j++) {
                    if (array[j]!=0) {
                        if (array[i] == array[j]) {
                            isDistinct = false;
                            break;
                        }
                    }
                    
                }
                if (isDistinct) {
                    count++;
                }
            }
            
        }
        return count;

    }
    
    public void sort(){
        Arrays.sort(array);
        int length = array.length;
        for (int i = 0; i < length / 2; i++) {
            int temp = array[i];
            array[i] = array[length - i - 1];
            array[length - i - 1] = temp;
        }
    }
    
    public void print(){
        for (int i = array.length-1; i >= 0; i--) {
            if (array[i]!=0) {
                Output.writeToFile("queueOut.txt", Integer.toString(array[i])+" ", true, false);
            }
        }
        Output.writeToFile("queueOut.txt", "", true, true);
        
    }
}
