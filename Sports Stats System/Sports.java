
public class Sports {
    private String team;
    private int points;
    private int wins;
    private int loses;
    private int even;
    private int golsfor;
    private int golsagainst;
    private int totalGame;

    public Sports(String team) {
        this.team = team;
        this.points = 0;
        this.wins = 0;
        this.loses = 0;
        this.golsfor=0;
        this.golsagainst=0;
        this.even=0;
        
    }

    public String getTeam() {
        return team;
    }

    public void setTeam(String team) {
        this.team = team;
    }

    public int getPoints() {
        return points;
    }

    public void setPoints(int points) {
        this.points = points;
    }

    public int getWins() {
        return wins;
    }

    public void setWins(int wins) {
        this.wins = wins;
    }

    public int getLoses() {
        return loses;
    }

    public void setLoses(int loses) {
        this.loses = loses;
    }

    public int getGolsfor() {
        return golsfor;
    }

    public void setGolsfor(int golsfor) {
        this.golsfor = golsfor;
    }

    public int getGolsagainst() {
        return golsagainst;
    }

    public void setGolsagainst(int golsagainst) {
        this.golsagainst = golsagainst;
    }

    public int getEven() {
        return even;
    }

    public void setEven(int even) {
        this.even = even;
    }

    public int getTotalGame() {
        return totalGame;
    }

    public void setTotalGame(int totalGame) {
        this.totalGame = totalGame;
    }

    
    
    public void calculatePoint(int score1, int score2){
        totalGame++;
        golsfor+=score1;
        golsagainst+=score2;
        if (score1>score2) {
           wins++; 
        }
        else if(score2>score1){
            loses++;
        }
        else{
            even++;
        }
    }
    public int calculatedifference(){
        return golsfor-golsagainst;
    }
}
