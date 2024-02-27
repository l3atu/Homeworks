
public class Main {
    public static void main(String[] args) {
      
        String[] commands = Input.readFile(args[0], true, true);
        String[] stackElements = Input.readFile("stack.txt", true, true);
        String[] queueElements = Input.readFile("queue.txt", true, true);

        
        Stack stack=new Stack();
        Queue queue= new Queue();
        Commands process= new Commands();
        
        for (int i = 0; i < stackElements.length; i++) {
            String[] elements=stackElements[i].split(" ");
            for (int j =0; j <  elements.length; j++) {
                stack.push(Integer.parseInt(elements[j]));
            }
        }
        
        for (int i = 0; i < queueElements.length; i++) {
            String[] elements=queueElements[i].split(" ");
            for (int j =0; j <  elements.length; j++) {
                queue.push(Integer.parseInt(elements[j]));
            }
        }
       
        process.operations(commands, queue, stack);
        
    }
}
