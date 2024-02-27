
import java.util.Arrays;


public class Stack {
    private int[] array=new int[100];
    
    
    public void push(int i){
        for (int j = array.length-1; j >= 0; j--) {
            if (array[j]==0) {
                array[j]=i;
                break;
            }
        }
    }
    
    public int top(){
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                return array[i];
            }
        }
        return 0;
    }
    
    public void pop(){
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                array[i]=0;
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
    }
    
    public void print(){
        for (int i = 0; i < array.length; i++) {
            if (array[i]!=0) {
                Output.writeToFile("stackOut.txt", Integer.toString(array[i])+" ", true, false);
            }
        }
        Output.writeToFile("stackOut.txt", "", true, true);
        
    }
    
} 
