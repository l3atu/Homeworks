
public class Icehockey extends Sports{

    public Icehockey(String team) {
        super(team);
    }

    @Override
    public void calculatePoint(int score1, int score2) {
        if (score1>score2) {
            setPoints(getPoints()+3);
        }
        else if (score1==score2) {
            setPoints(getPoints()+1);
        }
        super.calculatePoint(score1, score2); //To change body of generated methods, choose Tools | Templates.
    }

    @Override
    public int calculatedifference() {
        return super.calculatedifference(); //To change body of generated methods, choose Tools | Templates.
    }
  

   
    
    
}
