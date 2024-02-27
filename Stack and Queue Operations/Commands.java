
import java.util.Random;

public class Commands {
       
    public void operations(String[] commands, Queue queue,Stack stack){
        for (int i = 0; i < commands.length; i++) {
            String structure = commands[i].split(" ")[0];
            if (structure.equals("S")) {
                String command = commands[i].split(" ")[1];
            
                if (command.equals("addOrRemove")) {
                    int k = Integer.parseInt(commands[i].split(" ")[2]);
                    if (k > 0) {
                        int[] randomArray = new int[50]; 
                        Random random = new Random();
                        for (int j = 0; j < randomArray.length; j++) {
                            randomArray[j] = random.nextInt(50)+1; 
                        }
                        
                        for (int j = 0; j < k; j++) {
                            int randomIndex=random.nextInt(randomArray.length);
                            int randomNumber=randomArray[randomIndex];
                            stack.push(randomNumber);
                        }
                      
                    }
                    else if (k < 0) {
                        for (int j = 0; j < Math.abs(k); j++) {
                            stack.pop();                           
                        }
                    }
                 
                    Output.writeToFile("stackOut.txt", "After addOrRemove "+k+":", true, true);
                    stack.print();
                    
                }
                if (command.equals("reverse")) {
                    int k = Integer.parseInt(commands[i].split(" ")[2]);
                    Queue tempQueue = new Queue();
                    for (int j = 0; j < k; j++) {
                        int temp=stack.top();
                        stack.pop();
                        tempQueue.push(temp);
                    }
                    for (int j = 0; j < k; j++) {
                        int temp=tempQueue.front();
                        tempQueue.poll();
                        stack.push(temp);
                    }
                    Output.writeToFile("stackOut.txt", "After reverse "+k+":", true, true);
                    stack.print();
                }
                if (command.equals("removeGreater")) {
                    int k = Integer.parseInt(commands[i].split(" ")[2]);
                    Stack tempStack= new Stack();
                    for (int j = 0; j < stack.size(); j++) {
                        int temp= stack.top();
                        stack.pop();
                        if (temp < k) {
                           tempStack.push(temp);
                        }
                        j--;
                    }
                    
                    for (int j = 0; j < tempStack.size(); j++) {
                        int temp=tempStack.top();
                        tempStack.pop();
                        stack.push(temp);
                        j--;
                    }
                    Output.writeToFile("stackOut.txt", "After removeGreater "+k+":", true, true);
                    stack.print();
                    
                }
                if (command.equals("calculateDistance")) {
                    int distance=0;
                    Queue tempQueue = new Queue();
                    for (int j = 0; j < stack.size(); j++) {
                        int temp=stack.top();
                        tempQueue.push(temp);
                        stack.pop();
                        j--;
                    }
                    for (int j = 0; j < tempQueue.size(); j++) {
                        int temp = tempQueue.front();
                        tempQueue.poll();
                        stack.push(temp);
                        tempQueue.push(temp);
                    }
                    for (int j = 0; j < tempQueue.size(); j++) {
                        int first=tempQueue.front();
                        tempQueue.poll();
                        j--;
                        for (int k = 0; k < tempQueue.size(); k++) {
                            int second=tempQueue.front();
                            tempQueue.poll();
                            tempQueue.push(second);
                            distance+=Math.abs(first-second);
                           
                        }
                    }
                    
                    Output.writeToFile("stackOut.txt", "After calculateDistance:", true, true);
                    Output.writeToFile("stackOut.txt", "Total distance="+distance, true, true);
                }
                if (command.equals("distinctElements")) {
                    
                    Output.writeToFile("stackOut.txt", "After distinctElements:", true, true);
                    Output.writeToFile("stackOut.txt", "Total distinct element="+stack.distinctCount(), true, true);
                }
                if (command.equals("sortElements")) {
                    stack.sort();
                    Output.writeToFile("stackOut.txt", "After sortElements:", true, true);
                    stack.print();
                }
               
            }
            else if (structure.equals("Q")) {
                String command = commands[i].split(" ")[1];
            
                if (command.equals("addOrRemove")) {
                    int k = Integer.parseInt(commands[i].split(" ")[2]);
                    if (k > 0) {
                        int[] randomArray = new int[50]; 
                        Random random = new Random();
                        for (int j = 0; j < randomArray.length; j++) {
                            randomArray[j] = random.nextInt(50)+1; 
                        }
                        
                        for (int j = 0; j < k; j++) {
                            int randomIndex=random.nextInt(randomArray.length);
                            int randomNumber=randomArray[randomIndex];
                            queue.push(randomNumber);
                        }
                        
                    }
                    else if (k < 0) {
                        for (int j = 0; j < Math.abs(k); j++) {
                            queue.poll();                           
                        }
                    }
                    Output.writeToFile("queueOut.txt", "After addOrRemove "+k+":", true, true);
                    queue.print();
                }
                if (command.equals("reverse")) {
                    int k = Integer.parseInt(commands[i].split(" ")[2]);
                    Stack tempStack = new Stack();
                    for (int j = 0; j < k; j++) {
                        int temp=queue.front();
                        queue.poll();
                        tempStack.push(temp);
                    }
                    for (int j = 0; j < k; j++) {
                        int temp=tempStack.top();
                        tempStack.pop();
                        queue.push(temp);
                    }
                    for (int j = 0; j < queue.size()-k; j++) {
                        int temp=queue.front();
                        queue.poll();
                        queue.push(temp);
                    }
                    Output.writeToFile("queueOut.txt", "After reverse "+k+":", true, true);
                    queue.print();
                }
                if (command.equals("removeGreater")) {
                    int k = Integer.parseInt(commands[i].split(" ")[2]);
                    Queue tempqQueue= new Queue();
                    for (int j = 0; j < queue.size(); j++) {
                        int temp= queue.front();
                        queue.poll();
                        if (temp < k) {
                           tempqQueue.push(temp);
                        }
                        j--;
                    }
                    
                    for (int j = 0; j < tempqQueue.size(); j++) {
                        int temp=tempqQueue.front();
                        tempqQueue.poll();
                        queue.push(temp);
                        j--;
                    }
                    Output.writeToFile("queueOut.txt", "After removeGreater "+k+":", true, true);
                    queue.print();
                }
                if (command.equals("calculateDistance")) {
                    int distance=0;
                    Queue tempQueue = new Queue();
                    for (int j = 0; j < queue.size(); j++) {
                        int temp=queue.front();
                        tempQueue.push(temp);
                        queue.poll();
                        j--;
                    }
                    for (int j = 0; j < tempQueue.size(); j++) {
                        int temp = tempQueue.front();
                        tempQueue.poll();
                        queue.push(temp);
                        tempQueue.push(temp);
                    }
                    for (int j = 0; j < tempQueue.size(); j++) {
                        int first=tempQueue.front();
                        tempQueue.poll();
                        j--;
                        for (int k = 0; k < tempQueue.size(); k++) {
                            int second=tempQueue.front();
                            tempQueue.poll();
                            tempQueue.push(second);
                            distance+=Math.abs(first-second);
                           
                        }
                    }
                    
                    Output.writeToFile("queueOut.txt", "After calculateDistance:", true, true);
                    Output.writeToFile("queueOut.txt", "Total distance="+distance, true, true);
                    
                }
                if (command.equals("distinctElements")) {
                    Output.writeToFile("queueOut.txt", "After distinctElements:", true, true);
                    Output.writeToFile("queueOut.txt", "Total distinct element="+queue.distinctCount(), true, true);
                }
                if (command.equals("sortElements")) {
                    queue.sort();
                    Output.writeToFile("queueOut.txt", "After sortElements:", true, true);
                    queue.print();
                }
            }          
        }
    }
}
