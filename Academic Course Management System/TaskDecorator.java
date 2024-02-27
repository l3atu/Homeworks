
abstract class TaskDecorator implements  Task{
    protected Task temptask;

    public TaskDecorator(Task newtask) {
        temptask = newtask;
    }
    
    public String getDescription(){
        return temptask.getDescription();
    }
    public int getfee(){
        return temptask.getfee();
    }
}
